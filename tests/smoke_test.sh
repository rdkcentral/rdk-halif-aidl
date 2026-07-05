#!/usr/bin/env bash
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *     http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************
#
# smoke_test.sh - module-local build smoke test.
#
# Exercises the build paths the module-local restructure (#493) +
# versioned-imports work (#538) added, and asserts the produced HAL
# libraries:
#
#   1. ./build_modules.sh all                                          - build every component at current/
#   2. ./build_modules.sh manifest                                     - build the released cohort (versions_released.yaml)
#   3. ./build_modules.sh manifest --file versions_current.yaml        - build the dev cohort (every component at current/)
#   4. ./build_modules.sh <c> --version <v>                            - build a single released snapshot
#   5. ./build_modules.sh <c> --version <v> (deps wiped first)         - standalone snapshot build auto-resolves its dependency closure (#638)
#
# It is run on demand (no CI wiring). Exit status is 0 only if every check
# passes.
#
# Usage:
#   ./tests/smoke_test.sh            Run the full smoke test.
#   ./tests/smoke_test.sh --help
#
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")/.." && pwd)"
cd "${REPO_ROOT}"

if [ "${1:-}" = "--help" ] || [ "${1:-}" = "-h" ]; then
    sed -n '23,34p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
    exit 0
fi

HALIF_LIB_DIR="${REPO_ROOT}/out/target/lib/halif"
PASS=0
FAIL=0

pass() { echo "  PASS  $1"; PASS=$((PASS + 1)); }
fail() { echo "  FAIL  $1"; FAIL=$((FAIL + 1)); }

# Number of components expected at current/ (one interface.yaml each).
EXPECTED_CURRENT=$(ls -d ./*/current/interface.yaml 2>/dev/null | wc -l)

count_libs() {  # count_libs <glob>
    find "${HALIF_LIB_DIR}" -name "$1" -type f 2>/dev/null | wc -l
}

echo "========================================="
echo "  RDK HAL AIDL - build smoke test"
echo "  repo:     ${REPO_ROOT}"
echo "  expected: ${EXPECTED_CURRENT} current components"
echo "========================================="

#######################################################################
# 1. build_modules.sh all
#######################################################################
echo ""
# Wipe the staging directory before phase 1 so leftover .so files from a
# previous build don't inflate the lib counts. `--clean` clears the build
# tree but not the staged output.
rm -rf "${HALIF_LIB_DIR}"
echo "[1/5] ./build_modules.sh all --clean"
if ./build_modules.sh all --clean > /tmp/smoke_all.log 2>&1; then
    n=$(count_libs 'lib*-vcurrent-cpp.so')
    if [ "${n}" -eq "${EXPECTED_CURRENT}" ]; then
        pass "all: ${n} lib*-vcurrent-cpp.so built"
    else
        fail "all: expected ${EXPECTED_CURRENT} libraries, found ${n}"
    fi

    # Source-only invariant (#566): generated *.h/*.cpp for current/ are
    # toolchain-emitted on every build into the source tree, but they
    # are .gitignored and MUST NOT be tracked in git. Any file showing
    # up in `git ls-files` under */current/{include,src} is a regression
    # — either the .gitignore was bypassed (`git add -f`) or a new
    # generator output landed outside of .gitignore's reach.
    tracked=$(git -C "${REPO_ROOT}" ls-files '*/current/include/*' '*/current/src/*' 2>/dev/null | wc -l)
    if [ "${tracked}" -eq 0 ]; then
        pass "source-only: no files tracked under */current/{include,src} (generated bindings live only in working tree + frozen <version>/)"
    else
        fail "source-only: ${tracked} files tracked under */current/{include,src} — generated bindings must not be committed in current/ (see #566)"
        git -C "${REPO_ROOT}" ls-files '*/current/include/*' '*/current/src/*' | head -10 | sed 's/^/        /'
        echo "        → 'git rm --cached -r */current/include */current/src' and recommit." >&2
    fi
else
    fail "all: build_modules.sh exited non-zero (see /tmp/smoke_all.log)"
    tail -15 /tmp/smoke_all.log | sed 's/^/        /'
fi

#######################################################################
# 2. build_modules.sh manifest          (versions_released.yaml - released cohort)
#
# Default-file mode. Pins every component to its latest released snapshot;
# the produced libs follow the `lib<comp>-v<X.Y.Z.W>-cpp.so` shape. A
# component pinned to `current` in the manifest (e.g. a brand-new module
# with no snapshot yet) falls through and stays at `-vcurrent-cpp`.
#######################################################################
echo ""
echo "[2/5] ./build_modules.sh manifest      (versions_released.yaml)"
# Count via the *same* awk regex `build_modules.sh manifest` uses, so a
# manifest-format regression that the parser silently drops (e.g.
# aligned `name  : version` with spaces before the colon) shows up
# immediately as an unexpectedly-low EXPECTED_RELEASED.
EXPECTED_RELEASED=$(awk '/^components:/ {inmap=1; next}
                        inmap && /^[^[:space:]#]/ {inmap=0}
                        inmap && /^[[:space:]]+[A-Za-z0-9_]+:/ {n++}
                        END {print n+0}' "${REPO_ROOT}/versions_released.yaml")
# Sanity check: the released cohort should cover every component the dev
# tree has. If the parser drops most lines, EXPECTED_RELEASED falls below
# EXPECTED_CURRENT and we surface it before the build phase.
if [ "${EXPECTED_RELEASED}" -lt "${EXPECTED_CURRENT}" ]; then
    fail "manifest (released): parsed ${EXPECTED_RELEASED} entries from versions_released.yaml, expected >= ${EXPECTED_CURRENT} — likely a manifest-format regression"
fi
if ./build_modules.sh manifest > /tmp/smoke_manifest_released.log 2>&1; then
    # Count ONLY versioned snapshot libs (`-v<X.Y.Z.W>-cpp.so`) — phase 2
    # exists specifically to validate the released cohort produces those.
    # Phase 1's `-vcurrent-cpp.so` libs are excluded from the count so a
    # silent regression here can't be masked by phase 1's leftover libs.
    # Components pinned to `current` in the manifest (e.g. new modules
    # with no snapshot yet) are excluded from both the count and the
    # EXPECTED_VERSIONED expectation below.
    EXPECTED_VERSIONED=$(awk '/^components:/ {inmap=1; next}
                              inmap && /^[^[:space:]#]/ {inmap=0}
                              inmap && /^[[:space:]]+[A-Za-z0-9_]+:[[:space:]]+[0-9]/ {n++}
                              END {print n+0}' "${REPO_ROOT}/versions_released.yaml")
    n=$(count_libs 'lib*-v[0-9]*-cpp.so')
    if [ "${n}" -ge "${EXPECTED_VERSIONED}" ]; then
        pass "manifest (released): ${n} lib*-v<X.Y.Z.W>-cpp.so built (>= ${EXPECTED_VERSIONED} versioned-pin entries expected)"
    else
        fail "manifest (released): expected >= ${EXPECTED_VERSIONED} versioned snapshot libraries, found ${n}"
    fi
else
    fail "manifest (released): build_modules.sh exited non-zero (see /tmp/smoke_manifest_released.log)"
    tail -15 /tmp/smoke_manifest_released.log | sed 's/^/        /'
fi

#######################################################################
# 3. build_modules.sh manifest --file versions_current.yaml  (dev cohort)
#
# Explicit-file mode. Every component pinned to its `current/` sibling —
# the in-development cohort devs work against day-to-day.
#######################################################################
echo ""
echo "[3/5] ./build_modules.sh manifest --file versions_current.yaml  (dev)"
if ./build_modules.sh manifest --file versions_current.yaml > /tmp/smoke_manifest_current.log 2>&1; then
    n=$(count_libs 'lib*-vcurrent-cpp.so')
    if [ "${n}" -eq "${EXPECTED_CURRENT}" ]; then
        pass "manifest (current): ${n} lib*-vcurrent-cpp.so built"
    else
        fail "manifest (current): expected ${EXPECTED_CURRENT} libraries, found ${n}"
    fi
else
    fail "manifest (current): build_modules.sh exited non-zero (see /tmp/smoke_manifest_current.log)"
    tail -15 /tmp/smoke_manifest_current.log | sed 's/^/        /'
fi

#######################################################################
# 4. Per-version snapshot build
#
# Pick the first released snapshot directory present in the repo and build
# it. (Released via ./release.sh; the snapshots are committed.)
#######################################################################
echo ""
echo "[4/5] per-version snapshot build"
SNAP=""
for d in */[0-9]*.[0-9]*.[0-9]*.[0-9]*/CMakeLists.txt; do
    [ -f "${d}" ] || continue
    SNAP="${d%/CMakeLists.txt}"
    break
done

if [ -z "${SNAP}" ]; then
    fail "snapshot: no released <component>/<version>/ directory found - run ./release.sh"
else
    comp="${SNAP%%/*}"
    ver="${SNAP#*/}"
    echo "       building snapshot ${comp} ${ver}"
    if ./build_modules.sh "${comp}" --version "${ver}" --clean > /tmp/smoke_snapshot.log 2>&1; then
        so="${HALIF_LIB_DIR}/lib${comp}-v${ver}-cpp.so"
        if [ -f "${so}" ]; then
            pass "snapshot: lib${comp}-v${ver}-cpp.so built"
        else
            fail "snapshot: expected ${so} not found"
        fi
    else
        fail "snapshot: build_modules.sh exited non-zero (see /tmp/smoke_snapshot.log)"
        tail -15 /tmp/smoke_snapshot.log | sed 's/^/        /'
    fi
fi

#######################################################################
# 5. Standalone snapshot build with its dependency closure wiped (#638)
#
# Steps 1-4 leave out/build/include + out/target fully populated, so a
# per-version snapshot build never proves it can stand up its own
# dependencies. Here we pick a released snapshot that HAS dependencies,
# wipe those dependencies' staged headers + libraries, then build ONLY
# that snapshot and assert it auto-resolves and rebuilds the closure
# (the exact failure mode of #638: missing com/rdk/hal/PropertyValue.h).
#######################################################################
echo ""
echo "[5/5] standalone snapshot build resolves its dependency closure (#638)"
# Find the first released snapshot whose CMakeLists declares HAL deps.
DEPSNAP=""
for d in */[0-9]*.[0-9]*.[0-9]*.[0-9]*/CMakeLists.txt; do
    [ -f "${d}" ] || continue
    grep -qE 'HALIF_INCLUDE_DIR\}/[a-z][a-z0-9_]*/[0-9][0-9.]*/include' "${d}" || continue
    DEPSNAP="${d%/CMakeLists.txt}"
    break
done

if [ -z "${DEPSNAP}" ]; then
    pass "dep-closure: no released snapshot with dependencies found — nothing to exercise"
else
    dcomp="${DEPSNAP%%/*}"
    dver="${DEPSNAP#*/}"
    dcmake="${DEPSNAP}/CMakeLists.txt"
    # Immediate dependencies declared by the snapshot's CMakeLists.
    mapfile -t DEPS < <(grep -oE 'HALIF_INCLUDE_DIR\}/[a-z][a-z0-9_]*/[0-9][0-9.]*/include' "${dcmake}" \
        | sed -E 's#HALIF_INCLUDE_DIR\}/([^/]+)/([^/]+)/include#\1 \2#' | sort -u)
    echo "       target ${dcomp}/${dver}; wiping ${#DEPS[@]} dependency(ies): ${DEPS[*]}"

    # Wipe the target + each dependency's staged headers, libraries and build
    # dirs so the build genuinely starts from an unstaged state.
    rm -rf "build/${dcomp}-${dver}" "build/${dcomp}/${dver}"
    rm -f  "${HALIF_LIB_DIR}/lib${dcomp}-v${dver}-cpp.so"
    rm -rf "${REPO_ROOT}/out/build/include/${dcomp}/${dver}"
    for pair in "${DEPS[@]}"; do
        set -- ${pair}; dep="$1"; depver="$2"
        rm -f  "${HALIF_LIB_DIR}/lib${dep}-v${depver}-cpp.so"
        rm -rf "${REPO_ROOT}/out/build/include/${dep}/${depver}"
        rm -rf "build/${dep}-${depver}" "build/${dep}/${depver}"
    done

    if ./build_modules.sh "${dcomp}" --version "${dver}" > /tmp/smoke_depclosure.log 2>&1; then
        missing=0
        # The target and every wiped dependency lib must be back.
        for pair in "${dcomp} ${dver}" "${DEPS[@]}"; do
            set -- ${pair}; c="$1"; v="$2"
            [ -f "${HALIF_LIB_DIR}/lib${c}-v${v}-cpp.so" ] || { fail "dep-closure: lib${c}-v${v}-cpp.so not rebuilt"; missing=1; }
        done
        # Each dependency's headers must have been re-staged (the #638 symptom).
        for pair in "${DEPS[@]}"; do
            set -- ${pair}; dep="$1"; depver="$2"
            [ -d "${REPO_ROOT}/out/build/include/${dep}/${depver}/include" ] || { fail "dep-closure: ${dep}/${depver} headers not staged"; missing=1; }
        done
        [ "${missing}" -eq 0 ] && pass "dep-closure: ${dcomp}/${dver} auto-resolved and rebuilt ${#DEPS[@]} dependency(ies) from a wiped state"
    else
        fail "dep-closure: build_modules.sh exited non-zero (see /tmp/smoke_depclosure.log)"
        tail -15 /tmp/smoke_depclosure.log | sed 's/^/        /'
    fi
fi

#######################################################################
# Summary
#######################################################################
echo ""
echo "========================================="
echo "  smoke test: ${PASS} passed, ${FAIL} failed"
echo "========================================="
[ "${FAIL}" -eq 0 ] && exit 0 || exit 1
