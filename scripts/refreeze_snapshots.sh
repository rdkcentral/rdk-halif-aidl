#!/usr/bin/env bash

#/**
# * Copyright 2026 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
# * SPDX-License-Identifier: Apache-2.0
# */

# refreeze_snapshots.sh — retrofit real interface identity into frozen
# snapshots (#633).
#
# Cohort snapshots cut before freeze-time stamping existed report the
# generator defaults (VERSION=1 / HASH="notfrozen"). This tool re-freezes a
# snapshot IN PLACE so its committed bindings carry the real positional
# version int + toolchain contract hash, without changing anything else
# about the frozen artefact:
#
#   changed:   <ver>/include/, <ver>/src/  (regenerated — identity constants
#              only, the generator is deterministic for unchanged AIDL),
#              <ver>/interface.yaml (gains `version: <int>`),
#              <ver>/.hash (the contract hash the generator bakes + verifies)
#   untouched: <ver>/com/ (AIDL), docs/, CMakeLists.txt, hfp-*.yaml,
#              module-root headers — the frozen contract stays byte-frozen.
#
# Method (mirrors scripts/release.sh create_snapshot): the snapshot's own
# sources are staged into the component's current/ slot (current/ is
# backed up and restored), stamped, regenerated via build_modules.sh, and
# only the identity artefacts are copied back into the snapshot.
#
# Usage:
#   ./scripts/refreeze_snapshots.sh all                 # every cohort snapshot
#                                                       # from versions_released.yaml
#   ./scripts/refreeze_snapshots.sh <comp>[/<version>]  # one component (version
#                                                       # defaults to the cohort pin)

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
TOOLCHAIN="${BINDER_TOOLCHAIN_ROOT:-${REPO_ROOT}/build-tools/linux_binder_idl}"
MANIFEST="${REPO_ROOT}/versions_released.yaml"

log()  { echo "$*" >&2; }
die()  { echo "ERROR: $*" >&2; exit 1; }
warn() { echo "WARNING: $*" >&2; }

[[ -x "${TOOLCHAIN}/host/aidl_hash_gen" ]] \
    || die "aidl_hash_gen not found at ${TOOLCHAIN}/host — clone the pinned toolchain (./build_binder.sh)."
[[ -f "${MANIFEST}" ]] || die "versions_released.yaml not found."

# Under `set -e`, any unhandled failure between the current/ swap and the
# restore would otherwise strand the worktree with current/ missing. This
# EXIT trap restores whichever swap is in flight, on every exit path
# (normal, die, or unexpected command failure).
_INFLIGHT_CUR=""
_INFLIGHT_BAK=""
_restore_inflight() {
    if [[ -n "${_INFLIGHT_BAK}" && -d "${_INFLIGHT_BAK}" ]]; then
        rm -rf "${_INFLIGHT_CUR}"
        mv "${_INFLIGHT_BAK}" "${_INFLIGHT_CUR}"
    fi
    _INFLIGHT_CUR=""
    _INFLIGHT_BAK=""
}
trap _restore_inflight EXIT
trap 'exit 130' INT TERM

# Positional 1-2-2-1 encoding over X.Y.Z.W (same contract as
# scripts/release.sh _snapshot_version_int).
version_int() {
    local ver="$1" out="" f i
    [[ "${ver}" =~ ^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+$ ]] || { echo ""; return 0; }
    local widths=(1 2 2 1) fields
    IFS='.' read -ra fields <<< "${ver}"
    for i in 0 1 2 3; do
        f="$((10#${fields[i]}))"
        (( f < 10 ** widths[i] )) || { echo ""; return 0; }
        out+=$(printf "%0${widths[i]}d" "${f}")
    done
    echo "$((10#${out}))"
}

set_interface_version() {
    python3 - "$1" "$2" <<'PYEOF'
import sys, re
path, n = sys.argv[1], sys.argv[2]
s = open(path).read()
if re.search(r'^\s*version:\s*\d+\s*$', s, re.M):
    s = re.sub(r'(^\s*version:\s*)\d+(\s*)$', r'\g<1>' + n + r'\2', s, count=1, flags=re.M)
else:
    s = re.sub(r'(\n\s*name:[^\n]*\n)', r'\1  version: ' + n + '\n', s, count=1)
open(path, 'w').write(s)
PYEOF
}

refreeze_one() {
    local comp="$1" ver="$2"
    local snap="${REPO_ROOT}/${comp}/${ver}"
    local cur="${REPO_ROOT}/${comp}/current"
    local bak="${REPO_ROOT}/${comp}/.current.refreeze-bak"

    [[ -d "${snap}" ]] || { warn "[${comp}] ${ver}/ not found — skipped."; return 1; }
    [[ -f "${snap}/interface.yaml" ]] || { warn "[${comp}] ${ver}/ has no interface.yaml — skipped."; return 1; }
    [[ -d "${cur}" ]] || { warn "[${comp}] no current/ — placeholder component, skipped."; return 1; }

    local vint
    vint="$(version_int "${ver}")"
    [[ -n "${vint}" ]] || { warn "[${comp}] ${ver} not encodable (X.Y.Z.W, widths 1-2-2-1) — skipped."; return 1; }

    [[ -d "${bak}" ]] && die "[${comp}] stale ${bak} exists — resolve before re-running."

    restore_current() {
        rm -rf "${cur}"
        mv "${bak}" "${cur}"
        _INFLIGHT_CUR=""
        _INFLIGHT_BAK=""
    }

    mv "${cur}" "${bak}"
    _INFLIGHT_CUR="${cur}"
    _INFLIGHT_BAK="${bak}"
    mkdir "${cur}"

    # Stage the snapshot's own sources into the current/ slot. Skip the
    # regenerated trees and the snapshot's cohort-patched CMakeLists —
    # generation runs with current/'s own (vcurrent) CMakeLists so
    # dependency lib names and include paths resolve in the dev build.
    # NOTE: this function is invoked in an `if` condition, which suppresses
    # errexit for its whole body — every critical command below must carry
    # its own failure handling.
    local entry name
    for entry in "${snap}"/* "${snap}"/.hash; do
        [[ -e "${entry}" ]] || continue
        name="$(basename "${entry}")"
        case "${name}" in
            include|src|CMakeLists.txt|.hash) continue ;;
        esac
        if ! cp -r "${entry}" "${cur}/"; then
            restore_current
            warn "[${comp}] failed to stage ${name} into current/ — skipped."
            return 1
        fi
    done
    if ! cp "${bak}/CMakeLists.txt" "${cur}/CMakeLists.txt"; then
        restore_current
        warn "[${comp}] failed to stage CMakeLists.txt — skipped."
        return 1
    fi

    # Stamp: contract hash over the snapshot's AIDL (label must be
    # 'latest-version' — anything else fails the generator's integrity
    # check), then the positional version int into interface.yaml.
    if ! "${TOOLCHAIN}/host/aidl_hash_gen" "${cur}" "latest-version" "${cur}/.hash"; then
        restore_current
        warn "[${comp}] contract-hash generation failed — skipped."
        return 1
    fi
    if ! set_interface_version "${cur}/interface.yaml" "${vint}"; then
        restore_current
        warn "[${comp}] version stamping failed — skipped."
        return 1
    fi

    # Regenerate bindings with the identity baked in.
    local build_log="${REPO_ROOT}/out/refreeze-${comp//\//_}-${ver}.log"
    mkdir -p "$(dirname "${build_log}")"
    if ! (cd "${REPO_ROOT}" && ./build_modules.sh "${comp}" >"${build_log}" 2>&1); then
        restore_current
        warn "[${comp}] build failed — see ${build_log#${REPO_ROOT}/}; snapshot untouched."
        return 1
    fi

    # Copy back ONLY the identity artefacts. A failure here has already
    # removed the snapshot's old bindings — tell the operator how to
    # recover rather than leaving a silently half-written snapshot.
    rm -rf "${snap}/include" "${snap}/src"
    if ! cp -r "${cur}/include" "${cur}/src" "${snap}/" \
        || ! cp "${cur}/interface.yaml" "${snap}/interface.yaml" \
        || ! cp "${cur}/.hash" "${snap}/.hash"; then
        restore_current
        warn "[${comp}] copy-back into ${ver}/ failed — snapshot is incomplete; recover with: git checkout -- ${comp}/${ver}/"
        return 1
    fi

    # Re-stage hand-authored module-root headers into the snapshot's
    # include/ tree (same contract as release.sh create_snapshot, #623).
    local hdr
    for hdr in "${snap}"/*.h; do
        [[ -e "${hdr}" ]] || continue
        if ! cp "${hdr}" "${snap}/include/"; then
            restore_current
            warn "[${comp}] failed to re-stage $(basename "${hdr}") into ${ver}/include/ — recover with: git checkout -- ${comp}/${ver}/"
            return 1
        fi
    done

    restore_current
    (cd "${REPO_ROOT}" && git add "${comp}/${ver}/")
    log "[${comp}] ${ver}/ refrozen: VERSION=${vint} HASH=$(head -c12 "${snap}/.hash")…"
    return 0
}

targets=()
if [[ $# -eq 0 || "${1:-}" == "--help" || "${1:-}" == "-h" ]]; then
    sed -n '/^# Usage:/,/^$/p' "$0" | sed 's/^# \{0,1\}//'
    exit 0
elif [[ "$1" == "all" ]]; then
    while IFS=': ' read -r comp ver; do
        [[ -n "${comp}" && -n "${ver}" ]] && targets+=("${comp}:${ver}")
    done < <(awk '/^components:/{f=1; next} f && /^  [a-z]/{gsub(":",""); print $1": "$2} f && /^[^ ]/{f=0}' "${MANIFEST}")
else
    for arg in "$@"; do
        comp="${arg%%/*}"
        ver="${arg#*/}"
        if [[ "${ver}" == "${comp}" ]]; then
            ver="$(awk -v k="${comp}:" '$1==k{print $2; exit}' "${MANIFEST}")"
            [[ -n "${ver}" ]] || die "${comp} not in versions_released.yaml — pass <comp>/<version> explicitly."
        fi
        targets+=("${comp}:${ver}")
    done
fi

ok=0; failed=0
for t in "${targets[@]}"; do
    if refreeze_one "${t%%:*}" "${t#*:}"; then
        ok=$((ok + 1))
    else
        failed=$((failed + 1))
    fi
done

log ""
log "Refreeze complete: ${ok} snapshot(s) stamped, ${failed} skipped/failed."
[[ "${failed}" -eq 0 ]] || exit 1
