#!/usr/bin/env bash
# =============================================================================
# Release Version Bump Tool
#
# Manual release-time script that:
#   1) Looks at first-parent changes since the previous release tag/ref.
#   2) Maps changes to HAL/VSI components via component-level metadata.yaml.
#   3) Uses PR labels (Breaking Change / Major Change / Minor Change / documentation) when available.
#   4) Computes version bumps and optionally updates metadata.yaml.
#
# Default mode is dry-run. Use --apply to write changes.
# =============================================================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
cd "${REPO_ROOT}"


# Logging helpers — defined here so the plan subcommands below can call them.
# ANSI colors — only when stdout is a TTY and NO_COLOR isn't set.
# (Honors the conventional NO_COLOR env var: https://no-color.org/)
if [[ -t 1 && -z "${NO_COLOR:-}" ]]; then
    _C_RESET=$'\033[0m'
    _C_BOLD=$'\033[1m'
    _C_DIM=$'\033[2m'
    _C_RED=$'\033[31m'
    _C_GREEN=$'\033[32m'
    _C_YELLOW=$'\033[33m'
    _C_BLUE=$'\033[34m'
    _C_CYAN=$'\033[36m'
else
    _C_RESET= _C_BOLD= _C_DIM= _C_RED= _C_GREEN= _C_YELLOW= _C_BLUE= _C_CYAN=
fi

log() {
    # Highlight a few common idioms so the right thing draws the eye.
    local line="$*"
    case "$line" in
        '✓'*|'  ✓'*)          line="${_C_GREEN}${line}${_C_RESET}" ;;
        '❌'*|'  ❌'*)        line="${_C_RED}${line}${_C_RESET}" ;;
        '⚠️'*|'  ⚠️'*)        line="${_C_YELLOW}${line}${_C_RESET}" ;;
        'ℹ️'*|'  ℹ️'*)        line="${_C_CYAN}${line}${_C_RESET}" ;;
        'Module'*)            line="${_C_BOLD}${line}${_C_RESET}" ;;
        '------'*)            line="${_C_DIM}${line}${_C_RESET}" ;;
        Apply:*)              line="${_C_BOLD}${line}${_C_RESET}" ;;
        Plan:*)               line="${_C_BOLD}${line}${_C_RESET}" ;;
        Release\ scan\ completed*) line="${_C_GREEN}${line}${_C_RESET}" ;;
    esac
    echo "${line}"
}
phase() { echo "${_C_CYAN}==>${_C_RESET} ${_C_BOLD}$*${_C_RESET}" >&2; }
warn()  { echo "${_C_YELLOW}WARN:${_C_RESET} $*" >&2; }
die()   { echo "${_C_RED}${_C_BOLD}ERROR:${_C_RESET} ${_C_RED}$*${_C_RESET}" >&2; exit 1; }

# Verification-build runner. Defined at top-level so it's in scope for
# both the stage path (DO_WRITES=1) and a pure --apply (DO_WRITES=0).
# ----------------------------------------------------------------------------
# Build cache — skip work that's already been done with the same inputs.
# ----------------------------------------------------------------------------
#
# Persisted at out/.build-cache (gitignored — out/ is). Format, tab-delimited:
#
#   KIND<TAB>KEY<TAB>SHA256<TAB>STATUS
#
# Kinds:
#   module     KEY=<comp>          inputs: <comp>/current/com/**/*.aidl + interface.yaml + hfp-*.yaml
#   build      KEY=<args-joined>   inputs: versions_released.yaml + all referenced snapshot .aidl files
#                                          (or for "all": every */current/*.aidl)
#
# A status of "ok" means the last build with that input hash succeeded.
# Anything else (or absence) = need to re-run.
BUILD_CACHE_FILE="${REPO_ROOT}/out/.build-cache"

build_cache_lookup() {
    local kind="$1" key="$2"
    [[ -f "${BUILD_CACHE_FILE}" ]] || return 1
    # Return the cached SHA + status for kind/key on stdout.
    awk -F'\t' -v k="${kind}" -v key="${key}" '
        $1 == k && $2 == key { print $3"\t"$4; found=1; exit }
        END { exit (found ? 0 : 1) }
    ' "${BUILD_CACHE_FILE}"
}

build_cache_record() {
    local kind="$1" key="$2" sha="$3" status="$4"
    mkdir -p "$(dirname "${BUILD_CACHE_FILE}")"
    # Remove any existing entry for kind/key, then append the new one.
    if [[ -f "${BUILD_CACHE_FILE}" ]]; then
        awk -F'\t' -v k="${kind}" -v key="${key}" '
            !($1 == k && $2 == key) { print }
        ' "${BUILD_CACHE_FILE}" > "${BUILD_CACHE_FILE}.tmp" && \
            mv "${BUILD_CACHE_FILE}.tmp" "${BUILD_CACHE_FILE}"
    fi
    printf '%s\t%s\t%s\t%s\n' "${kind}" "${key}" "${sha}" "${status}" >> "${BUILD_CACHE_FILE}"
}

# SHA of every input file relevant to building a single component from
# current/: AIDL, interface.yaml, hfp-*.yaml. Pure-input hash — doesn't
# depend on the toolchain version (that's a separate concern; if the
# toolchain changes the operator should clear the cache).
build_cache_module_hash() {
    local comp="$1"
    local src_dir="${REPO_ROOT}/${comp}/current"
    [[ -d "${src_dir}" ]] || { echo ""; return; }
    find "${src_dir}" \
        \( -name '*.aidl' -o -name 'interface.yaml' -o -name 'hfp-*.yaml' \) \
        -type f 2>/dev/null \
        | sort \
        | xargs -r sha256sum 2>/dev/null \
        | sha256sum | awk '{print $1}'
}

# SHA for a verification build invocation. Inputs:
#   - The args (so "all" vs "manifest" hash differently)
#   - The relevant source files (every */current/*.aidl for "all";
#     versions_released.yaml + every */<version>/*.aidl for "manifest")
build_cache_build_hash() {
    local args="$*"
    local files
    if [[ "$1" == "manifest" ]]; then
        # versions_released.yaml + every snapshot dir's AIDL
        files="$(find "${REPO_ROOT}" -maxdepth 3 -path '*/[0-9]*/com' -prune -o \
                    -name '*.aidl' -path '*/[0-9]*.*.*/com/*' -print 2>/dev/null | sort)"
        if [[ -f "${REPO_ROOT}/versions_released.yaml" ]]; then
            files="${REPO_ROOT}/versions_released.yaml
${files}"
        fi
    else
        # `all` or single-comp: hash every current/*.aidl
        files="$(find "${REPO_ROOT}" -maxdepth 4 -path '*/current/com/*' -name '*.aidl' \
                    -type f 2>/dev/null | sort)"
    fi
    # Hash the args first, then all file contents.
    {
        echo "args:${args}"
        xargs -r sha256sum <<< "${files}" 2>/dev/null
    } | sha256sum | awk '{print $1}'
}

# Deploy the versioned mkdocs site to gh-pages via the project's
# build_docs.sh wrapper (uses `mike`). Two steps:
#   1. `mike deploy <X.Y.Z> --push`        — publishes this version
#   2. `mike set-default <X.Y.Z> --push`   — marks it as the "latest"
# Both are synchronous (blocking) and push to origin/gh-pages directly.
# Caller passes the release version. Bails (warns, doesn't die) on
# failure — the release artefact commit + tag is already made, so docs
# deploy is recoverable later (operator can rerun by hand).
deploy_versioned_docs() {
    local ver="$1"
    local docs_script="${REPO_ROOT}/docs/build_docs.sh"
    if [[ ! -x "${docs_script}" ]]; then
        warn "Versioned docs deploy: ${docs_script} not found/executable — skipping."
        return 0
    fi
    phase "Deploying versioned docs for ${ver} → gh-pages (mike deploy)"
    log ""
    log "Deploying ${ver} via ./docs/build_docs.sh deploy ${ver}"
    if ! (cd "${REPO_ROOT}" && ./docs/build_docs.sh deploy "${ver}"); then
        warn "mike deploy ${ver} failed."
        warn "  Release commit + tag are already made; you can retry later:"
        warn "    ./docs/build_docs.sh deploy ${ver}"
        warn "    ./docs/build_docs.sh set-default ${ver}"
        return 1
    fi
    phase "Setting ${ver} as default version (mike set-default)"
    log ""
    if ! (cd "${REPO_ROOT}" && ./docs/build_docs.sh set-default "${ver}"); then
        warn "mike set-default ${ver} failed — version is deployed but not marked as latest."
        warn "  Retry with: ./docs/build_docs.sh set-default ${ver}"
        return 1
    fi
    log "✓ Versioned docs deployed and ${ver} set as latest."
    return 0
}

run_verification_build() {
    local label="$1"          # "current cohort" / "released cohort"
    local log_file="$2"
    shift 2
    mkdir -p "$(dirname "${log_file}")"

    # Cache lookup — skip if these exact inputs already built successfully.
    local key="$*"
    local input_sha cached
    input_sha="$(build_cache_build_hash "$@")"
    cached="$(build_cache_lookup "build" "${key}" 2>/dev/null || true)"
    if [[ -n "${cached}" ]]; then
        local cached_sha="${cached%%$'\t'*}"
        local cached_status="${cached##*$'\t'}"
        if [[ "${cached_sha}" == "${input_sha}" && "${cached_status}" == "ok" ]]; then
            log "  Verification build (${label}) SKIPPED — cache hit (inputs unchanged since last success)"
            return 0
        fi
    fi

    phase "Verification build (${label}): ./build_modules.sh $*"
    log ""
    log "Verification build (${label}) — output streamed to ${log_file#${REPO_ROOT}/}"
    if [[ "${VERBOSE:-0}" -eq 1 ]]; then
        if ! (cd "${REPO_ROOT}" && ./build_modules.sh "$@" 2>&1 | tee "${log_file}"); then
            die "Verification build (${label}) failed — see ${log_file}. Aborting release."
        fi
    else
        if ! (cd "${REPO_ROOT}" && ./build_modules.sh "$@" > "${log_file}" 2>&1); then
            warn "Verification build (${label}) failed. Last error lines from ${log_file}:"
            grep -E '^(❌|ERROR|FAIL|error:)' "${log_file}" | head -10 | sed 's/^/    /' >&2 \
                || tail -30 "${log_file}" | sed 's/^/    /' >&2
            die "Verification build (${label}) failed. Aborting release."
        fi
    fi
    log "  Verification build (${label}) OK"
    build_cache_record "build" "${key}" "${input_sha}" "ok"
}

# ----------------------------------------------------------------------------
# Release plan helpers (#578)
# ----------------------------------------------------------------------------
#
# The "plan" is implicit in the working tree: a module is staged when
# its <comp>/<X.Y.Z.W>/ snapshot dir exists on disk AND isn't present
# in the last release tag. `stage <module>` runs the writes that put it
# there; `drop <module>` reverts them. No separate YAML file.
#
# Subcommands:
#   ./release.sh stage <module> [--version X.Y.Z.W]     write snapshot + metadata
#   ./release.sh stage all                              same, for every qualifying module
#   ./release.sh drop  <module>                         revert the writes
#   ./release.sh plan                                   read-only table view
#   ./release.sh check [<module>]                       preview without staging
#   ./release.sh clean (alias: reset)                   full reset — revert all
#                                                        release artefacts, remove
#                                                        untracked snapshot dirs

# Full release-state reset: undoes whatever a partial-or-complete
# default ./release.sh run wrote into the worktree, plus clears the
# plan. Targeted (not `git checkout -- .`) — only touches the files
# the release pipeline owns:
#   - per-component metadata.yaml
#   - versions_released.yaml
#   - mkdocs.yml
#   - CHANGELOG.md
#   - docs/releases/<release>.md  (removed if untracked)
#   - <comp>/<version>/  snapshot dirs that aren't tracked in git
# Operator's unrelated worktree edits are left alone.
plan_clean() {
    log "Resetting release state..."

    # 1. Tracked release artefacts — unstage + restore worktree.
    local touched=()
    while IFS= read -r f; do
        [[ -z "${f}" ]] || touched+=("${f}")
    done < <(
        git -C "${REPO_ROOT}" diff --cached --name-only \
            -- '*/metadata.yaml' versions_released.yaml mkdocs.yml CHANGELOG.md RAG_STATUS_REPORT.md 2>/dev/null
        git -C "${REPO_ROOT}" diff --name-only \
            -- '*/metadata.yaml' versions_released.yaml mkdocs.yml CHANGELOG.md RAG_STATUS_REPORT.md 2>/dev/null
    )
    if [[ ${#touched[@]} -gt 0 ]]; then
        mapfile -t touched < <(printf '%s\n' "${touched[@]}" | sort -u)
        for f in "${touched[@]}"; do
            git -C "${REPO_ROOT}" restore --staged --worktree -- "${f}" 2>/dev/null \
                || git -C "${REPO_ROOT}" checkout -- "${f}" 2>/dev/null || true
        done
        log "  Reverted ${#touched[@]} tracked release-artefact file(s)."
    fi

    # 2a. Tracked-snapshot worktree changes — revert any unstaged or
    # staged modifications inside <comp>/<X.Y.Z[.W]>/ dirs. Snapshots
    # are supposed to be immutable; if files inside one have been
    # modified (or deleted) since their commit, `clean` undoes that.
    # Catches the case where a prior test run regenerated the snapshot
    # contents in place.
    local restored=0
    while IFS= read -r f; do
        [[ -n "${f}" ]] || continue
        git -C "${REPO_ROOT}" restore --staged --worktree -- "${f}" 2>/dev/null || true
        restored=$((restored + 1))
    done < <(
        git -C "${REPO_ROOT}" status --short \
            | awk '{print $NF}' \
            | grep -E '^[a-z][a-z0-9_]*/[0-9]+(\.[0-9]+){2,3}/' \
            || true
    )
    [[ ${restored} -gt 0 ]] && log "  Restored ${restored} modified file(s) inside tracked snapshot dir(s)."

    # 2b. Untracked snapshot directories — <comp>/<X.Y.Z[.W]>/ that
    # aren't in git's index. Tracked released snapshots stay.
    local removed=0
    while IFS= read -r -d '' d; do
        local rel="${d#${REPO_ROOT}/}"
        # Verify the dir name looks like a version (defence in depth).
        local ver="${rel##*/}"
        [[ "${ver}" =~ ^[0-9]+(\.[0-9]+){2,3}$ ]] || continue
        # Skip if anything inside is tracked.
        if [[ -n "$(git -C "${REPO_ROOT}" ls-files -- "${rel}" 2>/dev/null | head -1)" ]]; then
            continue
        fi
        rm -rf "${d}"
        removed=$((removed + 1))
    done < <(find "${REPO_ROOT}" -maxdepth 2 -mindepth 2 -type d \
                -regex '.*/[a-z][a-z0-9_]*/[0-9][0-9.]*' -print0 2>/dev/null)
    [[ ${removed} -gt 0 ]] && log "  Removed ${removed} untracked snapshot dir(s)."

    # 3. Untracked release-notes files (we never overwrite pre-existing
    # ones; safe to delete any docs/releases/X.Y.Z.md not in git).
    local removed_notes=0
    while IFS= read -r -d '' nf; do
        local rel="${nf#${REPO_ROOT}/}"
        if [[ -z "$(git -C "${REPO_ROOT}" ls-files -- "${rel}" 2>/dev/null)" ]]; then
            rm -f "${nf}"
            removed_notes=$((removed_notes + 1))
        fi
    done < <(find "${REPO_ROOT}/docs/releases" -maxdepth 1 -type f -name '[0-9]*.md' -print0 2>/dev/null)
    [[ ${removed_notes} -gt 0 ]] && log "  Removed ${removed_notes} untracked docs/releases/X.Y.Z.md file(s)."

    # 4. Wipe the gh API cache so a fresh run re-pulls PR labels in case
    # any were changed since the last run. (commit→PR mappings are
    # immutable, but labels can be re-applied.)
    if [[ -f "${REPO_ROOT}/out/.gh-cache" ]]; then
        rm -f "${REPO_ROOT}/out/.gh-cache"
        log "  Cleared gh API cache (out/.gh-cache)."
    fi

    log "✓ Release state reset. Worktree is back to the pre-release-attempt state."
}

# Per-module drop — reverts everything `stage <module>` wrote:
#   * removes the staged <comp>/<NEXT_VERSION>/ snapshot dir (only if
#     not present in the baseline release tag — never touches tracked
#     released snapshots)
#   * restores <comp>/metadata.yaml to its pre-staged version
#   * restores versions_released.yaml's <comp>: entry to what it was
#   * restores any mkdocs.yml nav entries we added
# Leaves unrelated working-tree edits alone.
plan_remove() {
    local comp="$1"
    [[ -n "${comp}" ]] || die "drop: missing <module> argument."
    [[ -f "${REPO_ROOT}/${comp}/metadata.yaml" ]] \
        || die "drop: ${comp}/metadata.yaml not found — no such component."

    local baseline removed=0
    baseline="$(git -C "${REPO_ROOT}" describe --tags --abbrev=0 2>/dev/null || true)"

    # Identify the staged version dir (one not present in baseline tag).
    local ver_dir ver
    for ver_dir in "${REPO_ROOT}/${comp}"/*/; do
        [[ -d "${ver_dir}" ]] || continue
        ver="${ver_dir%/}"
        ver="${ver##*/}"
        [[ "${ver}" =~ ^[0-9]+(\.[0-9]+){2,3}$ ]] || continue
        if [[ -n "${baseline}" ]]; then
            if [[ -n "$(git -C "${REPO_ROOT}" ls-tree -d --name-only "${baseline}" "${comp}/${ver}" 2>/dev/null)" ]]; then
                continue   # tracked released — leave it alone
            fi
        fi
        # Untracked / staged — remove it.
        git -C "${REPO_ROOT}" reset HEAD -- "${comp}/${ver}/" >/dev/null 2>&1 || true
        rm -rf "${ver_dir}"
        removed=1
    done

    # Restore metadata.yaml + versions_released.yaml + mkdocs.yml for this
    # component (only — leaves other modules' staged state intact).
    git -C "${REPO_ROOT}" restore --staged --worktree -- \
        "${comp}/metadata.yaml" versions_released.yaml mkdocs.yml 2>/dev/null || true

    if [[ "${removed}" -eq 1 ]]; then
        log "✓ ${comp} unstaged: snapshot dir + metadata.yaml + manifest entries reverted."
    else
        log "ℹ️  ${comp} was not staged — nothing to revert."
    fi
}

# (Plan is now scanned from the worktree by plan_load above.)
# Populates: PLAN_COMPONENTS (assoc: comp -> "" or explicit version),
#            PLAN_RELEASE_VERSION (top-level release_version: or empty).
# Discover what's already staged by scanning the working tree, not by
# reading a YAML file. A module is "staged" if a <comp>/<X.Y.Z.W>/
# snapshot dir exists on disk that isn't present in the baseline (last
# release tag). That captures everything `stage <module>` has written —
# the snapshot dir, metadata.yaml bump, manifest updates — without a
# separate persistence file.
declare -A PLAN_COMPONENTS=()
PLAN_RELEASE_VERSION=""
plan_load() {
    PLAN_COMPONENTS=()
    PLAN_RELEASE_VERSION=""
    local baseline
    baseline="$(git -C "${REPO_ROOT}" describe --tags --abbrev=0 2>/dev/null || true)"
    local comp_dir comp ver_dir ver
    for comp_dir in "${REPO_ROOT}"/*/current; do
        [[ -d "${comp_dir}" ]] || continue
        comp="${comp_dir%/current}"
        comp="${comp#${REPO_ROOT}/}"
        # Scan version-shaped subdirs of this component.
        for ver_dir in "${REPO_ROOT}/${comp}"/*/; do
            [[ -d "${ver_dir}" ]] || continue
            ver="${ver_dir%/}"
            ver="${ver##*/}"
            [[ "${ver}" =~ ^[0-9]+(\.[0-9]+){2,3}$ ]] || continue
            # In baseline? then it\'s already released, not staged.
            if [[ -n "${baseline}" ]]; then
                if [[ -n "$(git -C "${REPO_ROOT}" ls-tree -d --name-only "${baseline}" "${comp}/${ver}" 2>/dev/null)" ]]; then
                    continue
                fi
            fi
            # Staged. (One staged version per component is the model — if
            # somehow there are multiple, we record the highest.)
            PLAN_COMPONENTS[$comp]=""
        done
    done
}

# Subcommand dispatch — must run BEFORE the standard arg parser sees
# anything. The subcommands edit the plan file and exit; they don't
# trigger a release run.
case "${1:-}" in
    stage)
        shift
        _add_comp="${1:-}"
        # `./release.sh stage all` is the bulk path — sets ACCEPT_ALL
        # and falls through to the main pipeline, which detects every
        # qualifying module and stages them in one go. Skipped + zero-
        # bump modules are excluded automatically.
        if [[ "${_add_comp}" == "all" ]]; then
            shift
            ACCEPT_ALL=1
            # `stage all` must ALSO run the writes — ACCEPT_ALL alone only
            # flips the in-memory Planned flag during the per-component
            # loop; without STAGE_AND_WRITE=1, DO_WRITES stays 0 and the
            # snapshot/metadata pipeline never fires.
            STAGE_AND_WRITE=1
            # No more positional args expected; any --flags fall through.
        else
            _add_ver=""
            shift || true
            while [[ $# -gt 0 ]]; do
                case "$1" in
                    --version) [[ $# -ge 2 ]] || die "--version requires a value"
                               _add_ver="$2"; shift 2 ;;
                    *) die "stage: unknown option $1" ;;
                esac
            done
            # Validate the module exists.
            [[ -n "${_add_comp}" ]] || die "stage: missing <module> argument. Usage: ./release.sh stage <module> [--version X.Y.Z.W]"
            [[ -f "${REPO_ROOT}/${_add_comp}/metadata.yaml" ]] \
                || die "stage: ${_add_comp}/metadata.yaml not found — no such component."
            # Push onto the write-pipeline queue + record any version pin.
            STAGE_AND_WRITE_MODULES+=("${_add_comp}")
            STAGE_AND_WRITE=1
            [[ -n "${_add_ver}" ]] && PIN_VERSIONS[${_add_comp}]="${_add_ver}"
            # Fall through to the standard pipeline; it processes the queue.
        fi
        ;;
    drop)
        shift
        plan_remove "${1:-}"
        exit 0
        ;;
    plan)
        # `plan` is now a synonym for the bare-script table view.
        ;;
    clean|reset)
        plan_clean
        exit 0
        ;;
    check)
        # `check` shows what's changed and the would-be bump per module —
        # bypasses the release_plan gate so the operator can see ALL
        # detected changes before deciding what to `module`. Optional
        # positional arg restricts to one module:
        #   ./release.sh check               (all touched modules)
        #   ./release.sh check bootreason    (just bootreason)
        shift
        CHECK_MODE=1
        DRY_RUN=1
        # Consume the optional positional module name. Anything starting
        # with -- is a flag for the main parser, not the module name.
        if [[ $# -gt 0 && "${1:0:2}" != "--" ]]; then
            CHECK_MODULE="$1"
            shift
        fi
        # Fall through into the standard arg parser for any --flags.
        ;;
    "")
        # No subcommand — fall through to default plan/check view.
        ;;
    -*)
        # Starts with a flag — fall through to standard arg parser.
        ;;
    *)
        # Positional module name(s): one or more module names move from
        # "not planned" to "planned" AND run the per-module write pipeline
        # (steps 1-5: regen, snapshot, metadata, versions_released.yaml,
        # mkdocs.yml, docs/releases/<X>.md skeleton, CHANGELOG.md section).
        # No branch / no tag — those are deferred to a final `--apply`.
        #
        #   ./release.sh bootreason             stage + write bootreason
        #   ./release.sh bootreason common      stage + write both
        #
        # Anything that looks like a flag (-prefixed) falls through.
        STAGE_AND_WRITE_MODULES=()
        while [[ $# -gt 0 && "${1:0:1}" != "-" ]]; do
            _m="$1"
            if [[ ! -f "${REPO_ROOT}/${_m}/metadata.yaml" ]]; then
                die "Unknown subcommand or module: ${_m}
  Subcommands: stage | drop | plan | check | clean | reset
  Or a known module name (e.g. ./release.sh bootreason)."
            fi
            STAGE_AND_WRITE_MODULES+=("${_m}")
            shift
        done
        # Fall through into the arg parser + main pipeline. DO_WRITES is
        # forced on; --apply will turn DO_BRANCH on too.
        STAGE_AND_WRITE=1
        ;;
esac

# Defaults for arg parser. Use ${VAR:-0} so the subcommand fall-throughs
# above can pre-set flags without us stomping them here.
CHECK_MODE="${CHECK_MODE:-0}"
CHECK_MODULE="${CHECK_MODULE:-}"
STAGE_AND_WRITE="${STAGE_AND_WRITE:-0}"

APPLY="${APPLY:-0}"
COMMIT="${COMMIT:-0}"
DRY_RUN="${DRY_RUN:-0}"
SINCE_REF="${SINCE_REF:-}"
NO_GH="${NO_GH:-0}"
ACCEPT_ALL="${ACCEPT_ALL:-0}"
declare -A PIN_VERSIONS=()
VERBOSE=0

usage() {
    cat <<'EOF'
Release Version Bump Tool

Subcommands (manage what's staged for the next release):
  ./release.sh stage <module> [--version X.Y.Z.W]     stage module (auto-bump unless --version pinned)
  ./release.sh drop   <module>                         unstage module
  ./release.sh plan                                    show current plan
  ./release.sh check  [<module>]                       preview detected changes for ALL touched
                                                       modules (or one specific module) without
                                                       staging. Read-only.
  ./release.sh clean | reset                           full reset — revert all release artefacts
                                                       (metadata.yaml, versions_released.yaml,
                                                       mkdocs.yml, CHANGELOG.md), remove untracked
                                                       <comp>/<version>/ snapshot dirs and
                                                       docs/releases/X.Y.Z.md, and wipe the plan.
                                                       Use after --apply or to abort a half-done run.

Release run (no subcommand):
  ./scripts/release.sh [--dry-run] [--apply] [--since <ref>]
                       [--release-version X.Y.Z]
                       [--no-gh] [--no-snapshot] [--no-mkdocs]
                       [--no-build] [--verbose]

  Only components staged in the worktree are processed. The detector
  computes the bump level from PR labels since the base ref; an explicit
  --version pin from the plan overrides that.

Modes:
  default       PLAN view (read-only). Reads the staged state from the worktree, runs the
                detector for the staged modules, prints the per-module
                Current → Next bump table plus the change reasoning.
                Writes NOTHING. The output ends with the exact --apply
                command to run when the plan is right.

  --apply       Execute the staged plan: regenerate bindings, create
                <module>/<version>/ snapshots, update metadata.yaml,
                versions_released.yaml, mkdocs.yml, generate
                docs/releases/X.Y.Z.md skeleton, prepend the CHANGELOG.md
                section, run both verification builds, then create the
                release/X.Y.Z branch + X.Y.Z tag. Operator pushes
                manually after review.

  --dry-run     Alias of the default — same read-only view. Kept for
                operators who reach for the explicit flag out of habit.

Options:
  --since <ref>          Base reference to diff from (default: nearest
                         reachable tag).
  --release-version X.Y.Z
                         Repo-level release version (e.g. "0.21.0").
                         Auto-detected from the last release tag by
                         bumping the minor segment if omitted. Override
                         only needed for point releases (0.20.0 -> 0.20.1).
  --no-gh                Disable GitHub label lookup; use local heuristics
                         only.
  --no-snapshot          Skip creating <module>/<version>/ frozen snapshots
                         (regenerate-then-copy step). Testing only — a
                         real release MUST snapshot.
  --no-mkdocs            Skip updating mkdocs.yml.
  --no-build             Skip the verification build (./build_modules.sh
                         all). Testing only — a real release MUST build.
  --verbose              Print extra diagnostics.
  --help                 Show this help.

Behavior (#545 change-class labels):
  - "Breaking Change" label   => generation bump (0.g.m.p -> 0.(g+1).0.0)
  - "Major Change"    label   => minor bump (0.g.m.p -> 0.g.(m+1).0)
  - "Minor Change"    label   => patch bump (0.g.m.p -> 0.g.m.(p+1))
  - "documentation"   label   => patch bump (docs-only; equivalent to Minor Change
                                 from a release-bump perspective)
  - no relevant label         => minor bump (default), unless docs-only heuristic
                                 says patch

Per bumped component the script:
  1. ./build_modules.sh <component>        # regenerate current/include + current/src
  2. cp -r <component>/current/ <component>/<NEXT_VERSION>/
  3. git add <component>/<NEXT_VERSION>/
  4. sed -i version: in <component>/metadata.yaml

Once per release the script:
  5. Update versions_released.yaml components: map entries
  6. Insert mkdocs.yml nav entries for each <component>/<version>/
  7. Generate docs/releases/<release>.md skeleton (if absent)
  8. Prepend CHANGELOG.md section for <release>
  9. Audit docs + build configs for version-shaped strings (review only)
 10. ./build_modules.sh all                # build current cohort
 11. ./build_modules.sh manifest           # build released cohort via
                                            # versions_released.yaml

With --apply, additionally:
 12. git checkout -b release/<release>
 13. git commit  (with --commit)
 14. git push origin release/<release>  (with --commit)

The tag is NOT created by this script. `git flow release finish
<release>` creates the tag on main when it merges the release branch
in. This script stops at the pushed release branch.

No-op when no component changed:
  If no metadata.yaml moves, the script writes nothing, creates no
  snapshot, leaves mkdocs.yml unchanged, and does not create a release
  branch. Exit clean.

Notes:
  - Script is intended for manual release-time usage (not CI).
  - Default WRITES files locally (regen + snapshot + metadata + manifests +
    docs + build). Use --dry-run for a pure preview.
EOF
}

# (log/phase/warn/die now defined above the plan helpers, near the top.)

RELEASE_VERSION=""
NO_SNAPSHOT=0
NO_MKDOCS=0
NO_BUILD=0

while [[ $# -gt 0 ]]; do
    case "$1" in
        --since)
            [[ $# -ge 2 ]] || die "--since requires a value"
            SINCE_REF="$2"
            shift 2
            ;;
        --apply)
            APPLY=1
            shift
            ;;
        --commit)
            COMMIT=1
            shift
            ;;
        --dry-run)
            DRY_RUN=1
            shift
            ;;
        --release-version)
            [[ $# -ge 2 ]] || die "--release-version requires a value (e.g. 0.21.0)"
            RELEASE_VERSION="$2"
            shift 2
            ;;
        --no-gh)
            NO_GH=1
            shift
            ;;
        --no-snapshot)
            NO_SNAPSHOT=1
            shift
            ;;
        --no-mkdocs)
            NO_MKDOCS=1
            shift
            ;;
        --no-build)
            NO_BUILD=1
            shift
            ;;
        --verbose|-v)
            VERBOSE=1
            shift
            ;;
        --help|-h)
            usage
            exit 0
            ;;
        *)
            die "Unknown argument: $1"
            ;;
    esac
done

[[ "${DRY_RUN}" -eq 1 && "${APPLY}" -eq 1 ]] && die "--dry-run and --apply are mutually exclusive"

# Two modes consumed by the rest of the script:
#   DO_WRITES   1 -> regen/snapshot/metadata/manifests/docs writes (per-module)
#   DO_BRANCH   1 -> create release branch + commit (once per release; tag is made by git-flow release finish on main)
# Mapping:
#   bare ./release.sh              read-only plan/check view (DO_WRITES=0, DO_BRANCH=0)
#   ./release.sh <module>...       writes for staged modules (DO_WRITES=1, DO_BRANCH=0)
#   ./release.sh --apply           branch + commit + tag only (DO_WRITES=0, DO_BRANCH=1).
#                                  Writes are expected to be done already by
#                                  prior `./release.sh <module>` invocations.
DO_WRITES=0
DO_BRANCH=0
if [[ "${STAGE_AND_WRITE}" -eq 1 ]]; then
    DO_WRITES=1
fi
if [[ "${APPLY}" -eq 1 ]]; then
    DO_BRANCH=1
fi

# Standalone `--commit`: commit + tag whatever is staged in the index.
# Useful after `./release.sh --apply` left the release branch with staged
# release artefacts and the operator has reviewed `git diff --cached`.
# Bypasses the detector entirely — just runs the git commands.
if [[ "${COMMIT}" -eq 1 && "${APPLY}" -ne 1 ]]; then
    # Auto-detect release version from the last release tag if not pinned.
    if [[ -z "${RELEASE_VERSION}" ]]; then
        last_tag="$(git -C "${REPO_ROOT}" describe --tags --abbrev=0 2>/dev/null || true)"
        if [[ "${last_tag}" =~ ^([0-9]+)\.([0-9]+)\.([0-9]+)$ ]]; then
            maj="${BASH_REMATCH[1]}"
            min="${BASH_REMATCH[2]}"
            RELEASE_VERSION="${maj}.$((min + 1)).0"
        else
            die "--commit needs --release-version X.Y.Z (no prior release tag to auto-detect from)."
        fi
    fi
    branch="$(git -C "${REPO_ROOT}" rev-parse --abbrev-ref HEAD)"
    if [[ ! "${branch}" =~ ^release/ ]]; then
        warn "Current branch is '${branch}', not a release branch."
        warn "  --commit is normally run on a release/X.Y.Z branch created by --apply."
    fi

    # Idempotency: --apply already did all the regen / snapshot / writes.
    # --commit's job is just commit + push + mike deploy. If there's
    # nothing staged AND HEAD already has a release commit AND the branch
    # is already pushed, skip straight to mike deploy (idempotent re-run).
    if (cd "${REPO_ROOT}" && git diff --cached --quiet); then
        if (cd "${REPO_ROOT}" && git log -1 --pretty=%B 2>/dev/null) | \
                grep -qE "^chore\(release\): cut ${RELEASE_VERSION//./\\.}\b"; then
            log "Release commit for ${RELEASE_VERSION} already on HEAD — skipping commit."
            if ! (cd "${REPO_ROOT}" && \
                    git rev-parse --verify --quiet "origin/${branch}" >/dev/null) || \
               [[ "$(cd "${REPO_ROOT}" && git rev-parse HEAD)" != \
                  "$(cd "${REPO_ROOT}" && git rev-parse "origin/${branch}" 2>/dev/null)" ]]; then
                phase "Pushing release branch to origin"
                log ""
                if ! (cd "${REPO_ROOT}" && git push origin "${branch}"); then
                    die "git push origin ${branch} failed."
                fi
                log "✓ Pushed ${branch} to origin."
            else
                log "Branch ${branch} already up-to-date on origin — skipping push."
            fi
        else
            die "--commit: nothing staged in the index and HEAD has no ${RELEASE_VERSION} release commit. Use ./release.sh --apply first."
        fi
    else
        log "Committing staged release artefacts on ${branch}..."
        (cd "${REPO_ROOT}" && \
            git commit -m "chore(release): cut ${RELEASE_VERSION} — frozen snapshots + mkdocs nav") || \
            die "git commit failed."
        log ""
        log "✓ Committed ${RELEASE_VERSION} release artefacts on ${branch}."

        # Push the release branch — no tag. The tag is made by
        # `git flow release finish` on main when the release branch
        # merges in, not on the release branch itself.
        phase "Pushing release branch to origin"
        log ""
        if ! (cd "${REPO_ROOT}" && git push origin "${branch}"); then
            die "git push origin ${branch} failed."
        fi
        log "✓ Pushed ${branch} to origin."
    fi
    log ""

    # Versioned docs deploy. deploy_versioned_docs runs mike deploy and
    # then (only on success) mike set-default — sequential, blocking,
    # so set-default sees the just-deployed version. mike treats the
    # version as a string; no git tag required.
    deploy_versioned_docs "${RELEASE_VERSION}"
    log ""
    log "Next step (git-flow):"
    log "    git flow release finish ${RELEASE_VERSION}"
    log "  (merges ${branch} → main, tags ${RELEASE_VERSION} on main, merges back to develop)"
    exit 0
fi

phase "Resolving base reference..."
if [[ -z "${SINCE_REF}" ]]; then
    if ! SINCE_REF="$(git describe --tags --abbrev=0 2>/dev/null)"; then
        SINCE_REF="$(git rev-list --max-parents=0 HEAD | tail -n 1)"
        warn "No tags found; using first commit as base: ${SINCE_REF}"
    fi
fi
phase "    Base: ${SINCE_REF}"

git rev-parse --verify "${SINCE_REF}^{commit}" >/dev/null 2>&1 || die "Invalid --since ref: ${SINCE_REF}"

phase "Walking first-parent commits in ${SINCE_REF}..HEAD..."
mapfile -t FP_COMMITS < <(git rev-list --first-parent --reverse "${SINCE_REF}..HEAD")
if [[ ${#FP_COMMITS[@]} -eq 0 ]]; then
    phase "    0 commits — nothing to release"
    log "No first-parent commits found in ${SINCE_REF}..HEAD. Nothing to release."
    exit 0
fi
phase "    ${#FP_COMMITS[@]} commit(s) to analyze"

phase "Scanning component metadata files..."
mapfile -t COMPONENTS < <(
    find . -name "metadata.yaml" -not -path "./docs/*" -not -path "./scripts/*" -printf '%h\n' \
        | sed 's|^\./||' \
        | awk '{print length($0) " " $0}' \
        | sort -rn \
        | cut -d' ' -f2-
)

[[ ${#COMPONENTS[@]} -gt 0 ]] || die "No component metadata files found"
phase "    ${#COMPONENTS[@]} component(s) found"

component_from_path() {
    local path="$1"
    local comp
    for comp in "${COMPONENTS[@]}"; do
        if [[ "$path" == "$comp" || "$path" == "$comp/"* ]]; then
            printf '%s\n' "$comp"
            return 0
        fi
    done
    return 1
}

is_doc_like_path() {
    local path="$1"
    case "$path" in
        docs/*|*/docs/*|*.md|*.rst|*.txt|*/README|*/README.*|*/CHANGELOG|*/CHANGELOG.*|*/metadata.yaml|*/hfp-*.yaml)
            return 0
            ;;
        *)
            return 1
            ;;
    esac
}

GH_REPO=""
if [[ "${NO_GH}" -eq 0 ]]; then
    REMOTE_URL="$(git config --get remote.origin.url || true)"
    if [[ "${REMOTE_URL}" =~ github.com[:/]([^/]+)/([^/.]+)(\.git)?$ ]]; then
        GH_REPO="${BASH_REMATCH[1]}/${BASH_REMATCH[2]}"
    fi
fi

ENABLE_GH_LABELS=0
if [[ "${NO_GH}" -eq 0 ]] && command -v gh >/dev/null 2>&1 && [[ -n "${GH_REPO}" ]]; then
    if gh auth status -h github.com >/dev/null 2>&1; then
        ENABLE_GH_LABELS=1
    else
        warn "gh is installed but not authenticated; falling back to heuristics"
    fi
elif [[ "${NO_GH}" -eq 0 ]]; then
    warn "GitHub labels unavailable (missing gh or non-GitHub origin); using heuristics"
fi

if [[ "${ENABLE_GH_LABELS}" -eq 1 ]]; then
    phase "GitHub PR-label lookup: enabled (${GH_REPO})"
else
    phase "GitHub PR-label lookup: disabled (using local heuristics)"
fi

declare -A PR_LABEL_CACHE=()
declare -A COMMIT_PR_CACHE=()
declare -A COMP_TOUCHED=()
declare -A COMP_BREAKING=()
declare -A COMP_NON_DOC=()
declare -A COMP_DOC=()
declare -A COMP_REASONS=()
declare -A COMP_FILES=()

# Persistent gh-API cache: commit→PR and PR→labels lookups survive
# across invocations. SHAs and PR numbers are immutable so the cache
# never goes stale. Labels CAN change (re-labelled PRs), so we treat
# label entries as soft cache and refresh ad hoc — but commit-to-PR
# pairs are forever once recorded.
#
# File: out/.gh-cache  (gitignored — out/ already is)
# Format, tab-delimited:
#   c<TAB>SHA<TAB>PR_NUMBER          (PR_NUMBER may be empty)
#   l<TAB>PR_NUMBER<TAB>LABEL1|LABEL2|LABEL3
# Labels are joined with `|` (which can't appear in label names).
GH_CACHE_FILE="${REPO_ROOT}/out/.gh-cache"

gh_cache_load() {
    [[ -f "${GH_CACHE_FILE}" ]] || return 0
    local kind key value
    while IFS=$'\t' read -r kind key value; do
        case "${kind}" in
            c)  COMMIT_PR_CACHE[$key]="${value}" ;;
            l)  # Restore newlines from |-encoded labels
                PR_LABEL_CACHE[$key]="${value//|/$'\n'}"
                ;;
        esac
    done < "${GH_CACHE_FILE}"
}

gh_cache_append() {
    local kind="$1" key="$2" value="$3"
    mkdir -p "$(dirname "${GH_CACHE_FILE}")"
    printf '%s\t%s\t%s\n' "${kind}" "${key}" "${value}" >> "${GH_CACHE_FILE}"
}

gh_cache_load

get_pr_for_commit() {
    local sha="$1"
    local subject="$2"

    if [[ -n "${COMMIT_PR_CACHE[$sha]+x}" ]]; then
        printf '%s\n' "${COMMIT_PR_CACHE[$sha]}"
        return 0
    fi

    local pr=""
    if [[ "${subject}" =~ ^Merge\ pull\ request\ \#([0-9]+) ]]; then
        pr="${BASH_REMATCH[1]}"
    elif [[ "${subject}" =~ \(#([0-9]+)\)$ ]]; then
        pr="${BASH_REMATCH[1]}"
    elif [[ "${ENABLE_GH_LABELS}" -eq 1 ]]; then
        pr="$(gh api "repos/${GH_REPO}/commits/${sha}/pulls" --jq '.[0].number' 2>/dev/null || true)"
        if ! [[ "${pr}" =~ ^[0-9]+$ ]]; then
            pr=""
        fi
    fi

    COMMIT_PR_CACHE[$sha]="${pr}"
    gh_cache_append "c" "${sha}" "${pr}"
    printf '%s\n' "${pr}"
}

get_pr_labels() {
    local pr="$1"
    if [[ -n "${PR_LABEL_CACHE[$pr]+x}" ]]; then
        printf '%s\n' "${PR_LABEL_CACHE[$pr]}"
        return 0
    fi

    local labels=""
    if [[ "${ENABLE_GH_LABELS}" -eq 1 ]]; then
        labels="$(gh api "repos/${GH_REPO}/pulls/${pr}" --jq '.labels[].name' 2>/dev/null || true)"
    fi

    PR_LABEL_CACHE[$pr]="${labels}"
    # Encode newlines as | for disk storage.
    gh_cache_append "l" "${pr}" "${labels//$'\n'/|}"
    printf '%s\n' "${labels}"
}

phase "Analyzing ${#FP_COMMITS[@]} commit(s) for component impact..."
_commit_idx=0
_commit_total=${#FP_COMMITS[@]}
for sha in "${FP_COMMITS[@]}"; do
    _commit_idx=$((_commit_idx + 1))
    subject="$(git show -s --format=%s "${sha}")"
    # one-line per-commit progress: counter, short sha, truncated subject.
    # Keeps the user oriented during the GH api stretch.
    _subj_short="${subject:0:72}"
    [[ "${#subject}" -gt 72 ]] && _subj_short="${_subj_short}..."
    phase "    [${_commit_idx}/${_commit_total}] ${sha:0:8} ${_subj_short}"
    parent="$(git rev-parse "${sha}^1" 2>/dev/null || true)"
    [[ -n "${parent}" ]] || continue

    mapfile -t changed_files < <(git diff --name-only "${parent}" "${sha}")
    [[ ${#changed_files[@]} -gt 0 ]] || continue

    pr_number="$(get_pr_for_commit "${sha}" "${subject}")"
    labels=""
    if [[ -n "${pr_number}" ]]; then
        labels="$(get_pr_labels "${pr_number}")"
    fi

    # Change-class labels (#545). The legacy lowercase forms are still
    # accepted for backwards compatibility while in-flight PRs migrate.
    has_breaking_label=0
    has_major_label=0
    has_minor_label=0
    while IFS= read -r lbl; do
        [[ -n "${lbl}" ]] || continue
        case "${lbl}" in
            "Breaking Change"|"breaking-change")   has_breaking_label=1 ;;
            "Major Change")                         has_major_label=1 ;;
            "Minor Change"|"documentation")         has_minor_label=1 ;;
        esac
    done <<< "${labels}"

    declare -A COMMIT_COMP_TOUCHED=()
    declare -A COMMIT_COMP_DOCS_ONLY=()

    for file in "${changed_files[@]}"; do
        comp="$(component_from_path "${file}" || true)"
        [[ -n "${comp}" ]] || continue

        COMP_TOUCHED[$comp]=1
        COMMIT_COMP_TOUCHED[$comp]=1
        COMP_FILES[$comp]="${COMP_FILES[$comp]:-}${file}"$'\n'

        if [[ -z "${COMMIT_COMP_DOCS_ONLY[$comp]+x}" ]]; then
            COMMIT_COMP_DOCS_ONLY[$comp]=1
        fi
        if ! is_doc_like_path "${file}"; then
            COMMIT_COMP_DOCS_ONLY[$comp]=0
        fi
    done

    for comp in "${!COMMIT_COMP_TOUCHED[@]}"; do
        reason_prefix="commit ${sha:0:8}"
        [[ -n "${pr_number}" ]] && reason_prefix="PR #${pr_number} (${sha:0:8})"

        # Order matters: highest severity wins if multiple change-class
        # labels are (accidentally) present on a single PR. Breaking >
        # Major > Minor (a Major+Minor combo resolves to Major, not Minor).
        if [[ "${has_breaking_label}" -eq 1 ]]; then
            COMP_BREAKING[$comp]=1
            COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}${reason_prefix}: Breaking Change label"$'\n'
        elif [[ "${has_major_label}" -eq 1 ]]; then
            COMP_NON_DOC[$comp]=1
            COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}${reason_prefix}: Major Change label"$'\n'
        elif [[ "${has_minor_label}" -eq 1 ]]; then
            COMP_DOC[$comp]=1
            COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}${reason_prefix}: Minor Change label"$'\n'
        elif [[ "${COMMIT_COMP_DOCS_ONLY[$comp]}" -eq 1 ]]; then
            COMP_DOC[$comp]=1
            COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}${reason_prefix}: docs-only heuristic"$'\n'
        else
            COMP_NON_DOC[$comp]=1
            COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}${reason_prefix}: default minor (no relevant label)"$'\n'
        fi
    done
done

if [[ ${#COMP_TOUCHED[@]} -eq 0 ]]; then
    log "No component-level changes found in ${SINCE_REF}..HEAD."
    exit 0
fi

# ----------------------------------------------------------------------------
# Release plan gate
# ----------------------------------------------------------------------------
#
# The release runs over components STAGED in the worktree — not over
# every component the detector found changes in. This is deliberate: the
# operator decides per-component whether a change is release-worthy this
# cycle. Use `./release.sh stage <module>` to stage a component, and
# `./release.sh plan` to view what's queued.

plan_load
# Merge anything `stage <module>` or positional `./release.sh <module>`
# pushed onto STAGE_AND_WRITE_MODULES into PLAN_COMPONENTS so the per-
# component loop processes them. Without this, those modules would
# never reach the write loop — the loop iterates PLAN_COMPONENTS.
for _m in "${STAGE_AND_WRITE_MODULES[@]:-}"; do
    [[ -n "${_m}" ]] || continue
    PLAN_COMPONENTS[$_m]=""
done
# Snapshot the ACTUAL plan-file contents now, BEFORE check mode or the
# read-only fallback synthesise PLAN_COMPONENTS with every touched
# module. The "Planned" table column queries ACTUAL_PLAN — a module
# shows `yes` only if it was really staged via `./release.sh <m>`.
declare -A ACTUAL_PLAN=()
for _c in "${!PLAN_COMPONENTS[@]}"; do
    ACTUAL_PLAN[$_c]="${PLAN_COMPONENTS[$_c]}"
done

# Pure read-only view (no writes, no branch, no check subcommand): show
# the global picture — every touched module with the Planned column
# flagging what's staged. The operator uses this to decide what to add
# next via `./release.sh <module>`.
if [[ "${DO_WRITES}" -eq 0 && "${DO_BRANCH}" -eq 0 && "${CHECK_MODE}" -eq 0 ]]; then
    PLAN_COMPONENTS=()
    for comp in "${!COMP_TOUCHED[@]}"; do
        PLAN_COMPONENTS[$comp]=""
    done
fi

# `check` mode bypasses the plan: surfaces all touched components (or just
# one if a module name was passed) so the operator can preview what would
# happen before deciding what to stage.
if [[ "${CHECK_MODE}" -eq 1 ]]; then
    phase "Check mode — bypassing release_plan gate"
    if [[ -n "${CHECK_MODULE}" ]]; then
        [[ -f "${REPO_ROOT}/${CHECK_MODULE}/metadata.yaml" ]] \
            || die "check: ${CHECK_MODULE}/metadata.yaml not found — no such component."
        for comp in "${!COMP_TOUCHED[@]}"; do
            if [[ "${comp}" != "${CHECK_MODULE}" ]]; then
                unset 'COMP_TOUCHED[$comp]' \
                      'COMP_BREAKING[$comp]' 'COMP_NON_DOC[$comp]' 'COMP_DOC[$comp]'
            fi
        done
        # If the requested module had no detected change, inject it so
        # the table still renders with a "no changes" note.
        if [[ -z "${COMP_TOUCHED[$CHECK_MODULE]:-}" ]]; then
            COMP_TOUCHED[$CHECK_MODULE]=1
            COMP_REASONS[$CHECK_MODULE]="check: no commits affecting ${CHECK_MODULE}/current/ in ${SINCE_REF}..HEAD"$'\n'
        fi
    fi
    # Synthesize PLAN_COMPONENTS so the rest of the pipeline runs without
    # actually requiring an explicit plan.
    PLAN_COMPONENTS=()
    for comp in "${!COMP_TOUCHED[@]}"; do
        PLAN_COMPONENTS[$comp]=""
    done
elif [[ ${#PLAN_COMPONENTS[@]} -eq 0 && "${STAGE_AND_WRITE}" -ne 1 && "${ACCEPT_ALL}" -ne 1 ]]; then
    # Nothing staged on the filesystem, no stage/positional request, no
    # accept-all. If --apply was asked for, error — there's literally
    # nothing to release. Otherwise show the read-only table view of
    # detected changes so the operator can decide what to stage.
    if [[ "${DO_BRANCH}" -eq 1 ]]; then
        log ""
        log "❌ --apply requested but nothing is staged."
        log ""
        log "  Stage modules first:"
        log "    ./release.sh stage <module>     (or: ./release.sh <module>)"
        log "    ./release.sh stage all          (stage every qualifying module)"
        log "  Then apply:"
        log "    ./release.sh --apply --release-version ${RELEASE_VERSION}"
        exit 1
    fi
    # Fall through to read-only table view (no writes happen).
    PLAN_COMPONENTS=()
    for comp in "${!COMP_TOUCHED[@]}"; do
        PLAN_COMPONENTS[$comp]=""
    done
fi

# Inject planned components even if the detector didn't see direct
# changes (operator may have other reasons — re-cut, version pin, etc.).
# Then either drop the rest (when this is a targeted single-module write)
# or keep them all (read-only display + `stage all`).
PLAN_EXTRA=()
PLAN_DROPPED=()
for comp in "${!PLAN_COMPONENTS[@]}"; do
    if [[ -z "${COMP_TOUCHED[$comp]:-}" ]]; then
        COMP_TOUCHED[$comp]=1
        COMP_NON_DOC[$comp]=1
        COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}plan: manually staged via ./release.sh stage ${comp}"$'\n'
        PLAN_EXTRA+=("${comp}")
    fi
done

# Drop touched-but-not-planned ONLY when this is a targeted write
# (single-module stage). For read-only views and for `stage all`, the
# table should show every touched module so the operator sees the full
# picture — the per-component loop's ACCEPT_ALL branch then decides
# which ones to actually write.
_should_filter=0
if [[ "${DO_WRITES}" -eq 1 && "${ACCEPT_ALL}" -ne 1 && "${STAGE_AND_WRITE}" -eq 1 ]]; then
    # Targeted single-module-stage call (`stage <m>` / positional <m>),
    # not `stage all`. Filter to only what's planned.
    _should_filter=1
fi
if [[ "${_should_filter}" -eq 1 ]]; then
    phase "Targeted stage — filtering to ${#PLAN_COMPONENTS[@]} planned component(s)..."
    declare -A KEEP=()
    for comp in "${!PLAN_COMPONENTS[@]}"; do
        KEEP[$comp]=1
    done
    for comp in "${!COMP_TOUCHED[@]}"; do
        if [[ -z "${KEEP[$comp]:-}" ]]; then
            unset 'COMP_TOUCHED[$comp]' \
                  'COMP_BREAKING[$comp]' 'COMP_NON_DOC[$comp]' 'COMP_DOC[$comp]'
            PLAN_DROPPED+=("${comp}")
        fi
    done
fi

if [[ ${#PLAN_DROPPED[@]} -gt 0 ]] || [[ ${#PLAN_EXTRA[@]} -gt 0 ]]; then
    log ""
    log "ℹ️  Release plan vs detected changes:"
    if [[ ${#PLAN_DROPPED[@]} -gt 0 ]]; then
        log "    Detected changes but NOT in plan (excluded from this release):"
        for c in $(printf '%s\n' "${PLAN_DROPPED[@]}" | sort); do
            log "      - ${c}"
        done
    fi
    if [[ ${#PLAN_EXTRA[@]} -gt 0 ]]; then
        log "    In plan but no detected changes (manually staged — will release anyway):"
        for c in $(printf '%s\n' "${PLAN_EXTRA[@]}" | sort); do
            log "      - ${c}"
        done
    fi
fi

# ----------------------------------------------------------------------------
# Transitive bump propagation (subsume rule)
# ----------------------------------------------------------------------------
#
# When component X bumps, every component that imports X must also bump at
# AT LEAST the same level — its compiled binary is now linked against a
# different version of X, and the cohort manifest needs that pin updated.
# This walks each component's current/interface.yaml `imports:` list and
# propagates the highest reachable bump level upward via fixed-point
# iteration. Bump precedence: Breaking > Major (non-doc) > Minor/Patch (doc).

phase "Propagating transitive bumps via interface.yaml imports..."

declare -A COMP_IMPORTS=()       # comp -> "dep1 dep2 ..." (just names, no @version)
declare -A COMP_TRANSITIVE=()    # comp -> 1 (this comp's bump came from a dep, not direct)

while IFS= read -r iface; do
    _comp_for_iface="${iface#./}"
    _comp_for_iface="${_comp_for_iface%/current/interface.yaml}"
    # Parse the imports: block. Strip the @version suffix; we only care
    # about the dep name for graph traversal — version is resolved by
    # versions_released.yaml at build time.
    deps="$(awk '
        /^  imports:/      { inblock=1; next }
        inblock && /^  [^ ]/ { inblock=0 }
        inblock && /^    - / {
            sub(/^    - /, "");
            sub(/@.*/, "");
            print
        }' "${iface}" 2>/dev/null | tr "\n" " ")"
    COMP_IMPORTS[$_comp_for_iface]="${deps}"
done < <(find . -maxdepth 3 -path '*/current/interface.yaml' -print)

# Fixed-point: keep walking until no new bumps land. Worst-case O(N*depth).
_iter=0
_changed=1
while [[ "${_changed}" -eq 1 ]]; do
    _changed=0
    _iter=$((_iter + 1))
    for comp in "${!COMP_IMPORTS[@]}"; do
        # Plan gate dropped this component — don't reintroduce it via
        # subsume. The operator explicitly chose not to release it; if a
        # dependency bump should force its release, they'll re-stage it.
        [[ -n "${COMP_TOUCHED[$comp]:-}" ]] || continue
        deps="${COMP_IMPORTS[$comp]}"
        for dep in ${deps}; do
            # Apply subsume: dep at level L → comp at min(level >= L).
            # Breaking > NON_DOC (Major) > DOC (Minor/Patch).
            if [[ "${COMP_BREAKING[$dep]:-0}" -eq 1 && "${COMP_BREAKING[$comp]:-0}" -ne 1 ]]; then
                COMP_BREAKING[$comp]=1
                unset 'COMP_NON_DOC[$comp]' 'COMP_DOC[$comp]' 2>/dev/null || true
                COMP_TOUCHED[$comp]=1
                COMP_TRANSITIVE[$comp]=1
                COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}subsume: ${dep} bumped Breaking → propagating Breaking"$'\n'
                _changed=1
            elif [[ "${COMP_NON_DOC[$dep]:-0}" -eq 1 && "${COMP_BREAKING[$comp]:-0}" -ne 1 && "${COMP_NON_DOC[$comp]:-0}" -ne 1 ]]; then
                COMP_NON_DOC[$comp]=1
                unset 'COMP_DOC[$comp]' 2>/dev/null || true
                COMP_TOUCHED[$comp]=1
                COMP_TRANSITIVE[$comp]=1
                COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}subsume: ${dep} bumped Major → propagating Major"$'\n'
                _changed=1
            elif [[ "${COMP_DOC[$dep]:-0}" -eq 1 && "${COMP_BREAKING[$comp]:-0}" -ne 1 && "${COMP_NON_DOC[$comp]:-0}" -ne 1 && "${COMP_DOC[$comp]:-0}" -ne 1 ]]; then
                COMP_DOC[$comp]=1
                COMP_TOUCHED[$comp]=1
                COMP_TRANSITIVE[$comp]=1
                COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}subsume: ${dep} bumped Minor/Patch → propagating Minor/Patch"$'\n'
                _changed=1
            fi
        done
    done
    [[ "${_iter}" -gt 20 ]] && break  # safety net; real graphs are shallow
done

# Diagnostic block: list every component that bumped purely transitively
# so the operator sees WHY a "quiet" component is suddenly on the list.
if [[ ${#COMP_TRANSITIVE[@]} -gt 0 ]]; then
    phase "Transitive bumps applied (subsume rule)"
fi

compute_next_versions() {
    local current_version="$1"
    local bump="$2"

    NEXT_VERSION="${current_version}"
    NEXT_NOTE=""

    if [[ "${bump}" == "none" ]]; then
        NEXT_NOTE="no bump"
        return 0
    fi

    if [[ "${current_version}" =~ ^0\.([0-9]+)\.([0-9]+)\.([0-9]+)$ ]]; then
        local gen="${BASH_REMATCH[1]}"
        local minor="${BASH_REMATCH[2]}"
        local patch="${BASH_REMATCH[3]}"

        if [[ "${bump}" == "generation" ]]; then
            gen=$((gen + 1))
            minor=0
            patch=0
        elif [[ "${bump}" == "minor" ]]; then
            minor=$((minor + 1))
            patch=0
        elif [[ "${bump}" == "patch" ]]; then
            patch=$((patch + 1))
        fi

        NEXT_VERSION="0.${gen}.${minor}.${patch}"
        return 0
    fi

    if [[ "${current_version}" =~ ^[0-9]+$ ]]; then
        if [[ "${bump}" == "generation" ]]; then
            NEXT_NOTE="breaking change on frozen interface: create new component instead"
            return 0
        fi
        if [[ "${bump}" == "minor" ]]; then
            NEXT_VERSION="$((current_version + 1))"
        else
            NEXT_NOTE="docs-only change on frozen interface: version unchanged"
        fi
        return 0
    fi

    NEXT_NOTE="unsupported version format"
}

update_metadata() {
    local file="$1"
    local new_version="$2"

    sed -i -E "s/^version:.*/version: ${new_version}/" "${file}"
}

# ----------------------------------------------------------------------------
# Snapshot creation (#513)
# ----------------------------------------------------------------------------
#
# Per the cohort-locked snapshot model, a release tags each bumped
# component's `current/` state into an immutable `<module>/<version>/`
# directory. Because `current/include/` and `current/src/` are gitignored
# (#566/#567), the snapshot creation MUST regenerate the bindings first
# so they're captured into the frozen tree.
#
# Sequence per component:
#   1. ./build_modules.sh <component>   # regenerate current/include + current/src
#   2. cp -r <component>/current/ <component>/<version>/
#   3. git add <component>/<version>/   # snapshot now contains bindings
#
# Frozen `<version>/` includes everything from `current/`: AIDL,
# generated include/src, docs, CMakeLists, interface.yaml, hfp-*.yaml.

# A component is considered "buildable" if it has a current/interface.yaml.
# Components without one (broadcast, ffv, r4ce, …) are incubating — they
# carry a metadata.yaml declaring intent but their AIDL isn't yet wired
# into the build (see metadata.yaml `notes.status_detail`). The release
# script excludes them: no bump, no snapshot, no build. They re-enter the
# release flow as soon as interface.yaml is added.
is_buildable_component() {
    local comp="$1"
    [[ -f "${REPO_ROOT}/${comp}/current/interface.yaml" ]]
}

create_snapshot() {
    local comp="$1"
    local version="$2"
    local snapshot_dir="${REPO_ROOT}/${comp}/${version}"

    # Placeholder-component guard (#517): components like ffv, r4ce, and
    # vsi/abstractfilesystem ship as metadata-only stubs — they have a
    # `metadata.yaml` declaring intent, but no `current/` directory, no
    # AIDL, no docs, no build wiring. Skip them with a friendly note; the
    # version bump in `metadata.yaml` still records the cycle.
    if [[ ! -d "${REPO_ROOT}/${comp}/current" ]]; then
        log "  [${comp}] no current/ directory — placeholder component (see #517); skipping snapshot."
        return 0
    fi

    # Verbose mode dumps full per-step progress; default mode buffers
    # and prints one summary line per module at the end (✓ or ✗).
    local refresh_marker=""
    if [[ -d "${snapshot_dir}" ]]; then
        [[ "${VERBOSE}" -eq 1 ]] && log "  [${comp}] refreshing existing ${version}/ snapshot (rm -rf + re-create)"
        rm -rf "${snapshot_dir}" || {
            warn "Failed to remove existing ${comp}/${version}/ — manual cleanup needed."
            return 1
        }
        refresh_marker=" (refreshed)"
    fi

    [[ "${VERBOSE}" -eq 1 ]] && log "  [${comp}] regenerating bindings via build_modules.sh..."
    local build_log="${REPO_ROOT}/out/release-snapshot-${comp//\//_}.log"
    mkdir -p "$(dirname "${build_log}")"
    if [[ "${VERBOSE}" -eq 1 ]]; then
        if ! (cd "${REPO_ROOT}" && ./build_modules.sh "${comp}" 2>&1 | tee "${build_log}"); then
            warn "Failed to regenerate ${comp} bindings — see ${build_log}."
            return 1
        fi
    else
        if ! (cd "${REPO_ROOT}" && ./build_modules.sh "${comp}" >"${build_log}" 2>&1); then
            log "  [${comp}] → ${version}/  ${_C_RED}✗ build failed${_C_RESET} (see ${build_log#${REPO_ROOT}/})"
            grep -E '^(❌|ERROR|FAIL)' "${build_log}" | head -3 | sed 's/^/    /' >&2 \
                || tail -10 "${build_log}" | sed 's/^/    /' >&2
            return 1
        fi
    fi

    [[ "${VERBOSE}" -eq 1 ]] && log "  [${comp}] copying current/ to ${version}/"
    if ! cp -r "${REPO_ROOT}/${comp}/current" "${snapshot_dir}"; then
        warn "cp failed for ${comp}/${version}/."
        return 1
    fi

    # Patch the copied CMakeLists.txt so the snapshot links + installs
    # with cohort-pinned versioned names. The `current/CMakeLists.txt`
    # template uses `<comp>-vcurrent-cpp` for its own LIB_NAME and for
    # inter-module link/include dep paths (`<dep>-vcurrent-cpp`,
    # `<dep>/current/include`). Left unpatched, the snapshot build
    # produces lib<comp>-vcurrent-cpp.so + links against
    # lib<dep>-vcurrent-cpp.so, and the released-cohort verification
    # step fails with "Snapshot library not found".
    #
    # Rewrite three things using the cohort versions read from
    # versions_released.yaml (the post-bump file just written by
    # update_versions_released):
    #   1. own LIB_NAME: <comp>-vcurrent-cpp → <comp>-v${version}-cpp
    #   2. dep link names: <dep>-vcurrent-cpp → <dep>-v${cohort}-cpp
    #   3. dep include paths: <dep>/current/include → <dep>/${cohort}/include
    local snapshot_cmake="${snapshot_dir}/CMakeLists.txt"
    if [[ -f "${snapshot_cmake}" ]] && grep -q "vcurrent-cpp\|current/include" "${snapshot_cmake}"; then
        # Own LIB_NAME first (no cohort lookup needed)
        sed -i "s/${comp}-vcurrent-cpp/${comp}-v${version}-cpp/g" "${snapshot_cmake}" || {
            warn "Failed to patch own LIB_NAME in ${comp}/${version}/CMakeLists.txt."
            return 1
        }
        # Dep names + include paths — read each <dep>-vcurrent-cpp occurrence
        # (own module already replaced above) and resolve to its cohort version
        # in versions_released.yaml. Then do the same for include paths.
        local versions_yaml="${REPO_ROOT}/versions_released.yaml"
        if [[ -f "${versions_yaml}" ]]; then
            local dep dep_ver
            while read -r dep; do
                [[ -z "${dep}" ]] && continue
                dep_ver="$(awk -v k="${dep}:" '$1==k{print $2; exit}' "${versions_yaml}")"
                if [[ -n "${dep_ver}" ]]; then
                    sed -i "s/${dep}-vcurrent-cpp/${dep}-v${dep_ver}-cpp/g" "${snapshot_cmake}"
                    sed -i "s|HALIF_INCLUDE_DIR}/${dep}/current/|HALIF_INCLUDE_DIR}/${dep}/${dep_ver}/|g" "${snapshot_cmake}"
                else
                    warn "  [${comp}/${version}] dep '${dep}' not in versions_released.yaml; left as -vcurrent-cpp (build will fail at verification)."
                fi
            done < <(grep -oE '[a-z][a-z0-9_]*-vcurrent-cpp' "${snapshot_cmake}" | grep -oE '^[a-z][a-z0-9_]*' | sort -u)
        else
            warn "  [${comp}/${version}] versions_released.yaml missing; dep links left as -vcurrent-cpp."
        fi
    fi

    # Stage the snapshot. No -f needed: .gitignore scopes the binding
    # rules to */current/include/ and */current/src/ only — files under
    # <module>/<version>/ are outside that scope and stage cleanly with
    # a plain `git add`. Using -f here would risk staging unrelated
    # ignored artefacts if any ever leak into the snapshot tree.
    (cd "${REPO_ROOT}" && git add "${comp}/${version}/") || {
        warn "git add failed for ${comp}/${version}/."
        return 1
    }

    # One summary line per module — visible by default. Verbose output
    # already showed every step above.
    if [[ "${VERBOSE}" -ne 1 ]]; then
        log "  [${comp}] → ${version}/  ${_C_GREEN}✓${_C_RESET}${refresh_marker}"
    fi
    return 0
}

# ----------------------------------------------------------------------------
# mkdocs.yml update (#513)
# ----------------------------------------------------------------------------
#
# Add an entry for the new component release into mkdocs.yml so the
# released doc set is reachable from the built site. Idempotent — skips
# entries that already exist.

update_mkdocs_for_release() {
    local comp="$1"
    local version="$2"
    local mkdocs="${REPO_ROOT}/mkdocs.yml"

    # Placeholder-component guard (#517): components without a current/
    # directory have no docs to add a nav entry for. Skip silently — the
    # metadata.yaml bump already recorded the cycle in create_snapshot().
    if [[ ! -d "${REPO_ROOT}/${comp}/current" ]]; then
        log "  [${comp}] no current/ directory — placeholder component (see #517); skipping mkdocs entry."
        return 0
    fi


    if [[ ! -f "${mkdocs}" ]]; then
        warn "mkdocs.yml not found — skipping mkdocs update."
        return 1
    fi

    local entry="'!include ${comp}/${version}/mkdocs.yml'"
    if grep -qF "${entry}" "${mkdocs}"; then
        log "  [${comp}] mkdocs.yml already contains ${version} entry"
        return 0
    fi

    # If a `current` !include exists for this component, append a sibling
    # versioned entry immediately after it, preserving the existing human
    # label (e.g. "Audio Decoder") rather than inventing a comp@version
    # label. We extract the label from the matching current line and
    # construct a "<label> X.Y.Z.W:" prefix for the new entry. Python
    # for the edit so YAML indentation stays exact byte-for-byte.
    local current_entry="'!include ${comp}/current/mkdocs.yml'"
    if ! grep -qF "${current_entry}" "${mkdocs}"; then
        warn "  [${comp}] no current/ mkdocs entry found; manual mkdocs.yml edit required"
        return 1
    fi

    if ! python3 - "${mkdocs}" "${comp}" "${version}" "${current_entry}" "${entry}" <<'PYEOF'; then
import io, re, sys
mkdocs_path, comp, version, current_entry, new_entry = sys.argv[1:6]
with open(mkdocs_path) as f:
    lines = f.readlines()

# Locate the line containing the current entry. Capture the leading
# indent ("    - ") and the label preceding the `:` so we can reuse it
# for the versioned sibling.
target_idx = None
indent = ""
label = ""
for i, line in enumerate(lines):
    if current_entry in line:
        target_idx = i
        m = re.match(r"^(\s*-\s+)(.*?):\s*'!include", line)
        if not m:
            sys.stderr.write(f"could not parse mkdocs label for {comp}\n")
            sys.exit(1)
        indent = m.group(1)
        label = m.group(2)
        break

if target_idx is None:
    sys.stderr.write(f"current entry not found in mkdocs.yml: {current_entry}\n")
    sys.exit(1)

new_line = f"{indent}{label} {version}: {new_entry}\n"
lines.insert(target_idx + 1, new_line)
with open(mkdocs_path, "w") as f:
    f.writelines(lines)
sys.exit(0)
PYEOF
        warn "  [${comp}] python mkdocs edit failed; manual mkdocs.yml edit required"
        return 1
    fi
    log "  [${comp}] added mkdocs.yml entry: ${version}"
    return 0
}

# ----------------------------------------------------------------------------
# Release branch (#513)
#
# Creates / reuses release/<version> and stages all generated artefacts.
# Does NOT create a git tag — `git flow release finish <version>` creates
# the tag on main when the release branch merges in.
# ----------------------------------------------------------------------------

create_release_branch() {
    local release_version="$1"
    local branch="release/${release_version}"

    # Tag existence is not a failure condition: this script never creates
    # the tag. `git flow release finish` does. If the tag exists already
    # (e.g. the operator already finished a prior cycle), warn — don't die.
    if git -C "${REPO_ROOT}" rev-parse --verify "refs/tags/${release_version}" >/dev/null 2>&1; then
        warn "Tag ${release_version} already exists. (Tag is created by 'git flow release finish' on main, not by this script.)"
    fi

    if git -C "${REPO_ROOT}" rev-parse --verify "refs/heads/${branch}" >/dev/null 2>&1; then
        log "Branch ${branch} already exists locally — checking it out."
        # -q: don't dump the M/A file list. Operator can use --verbose
        # to see it if they need the diff summary at checkout time.
        if [[ "${VERBOSE:-0}" -eq 1 ]]; then
            (cd "${REPO_ROOT}" && git checkout "${branch}") || die "Failed to checkout existing ${branch}"
        else
            (cd "${REPO_ROOT}" && git checkout -q "${branch}") || die "Failed to checkout existing ${branch}"
        fi
    else
        log "Creating release branch ${branch}"
        if [[ "${VERBOSE:-0}" -eq 1 ]]; then
            (cd "${REPO_ROOT}" && git checkout -b "${branch}") || die "Failed to create ${branch}"
        else
            (cd "${REPO_ROOT}" && git checkout -q -b "${branch}") || die "Failed to create ${branch}"
        fi
    fi

    # Stage all release artefacts on the release branch — but DO NOT
    # commit unless --commit was passed. Operator reviews with
    # `git diff --cached` and commits manually (or re-runs with --commit
    # to let release.sh commit + tag in one go).
    #
    # Never `git add -A` — only release-owned files, so an unrelated
    # worktree edit doesn't accidentally land in the release commit.
    for entry in "${BUMPED_COMPONENTS[@]}"; do
        local _comp="${entry%%:*}"
        (cd "${REPO_ROOT}" && git add "${_comp}/metadata.yaml") || \
            die "git add ${_comp}/metadata.yaml failed."
    done
    local rel_notes_file="docs/releases/${release_version}.md"
    for _f in mkdocs.yml versions_released.yaml CHANGELOG.md RAG_STATUS_REPORT.md "${rel_notes_file}"; do
        if [[ -f "${REPO_ROOT}/${_f}" ]]; then
            (cd "${REPO_ROOT}" && git add -- "${_f}") || \
                die "git add ${_f} failed."
        fi
    done

    # Belt-and-braces: pick up any other tracked-file modifications the
    # script's writes touched but the explicit list above missed.
    (cd "${REPO_ROOT}" && git add -u) || true
    # Also pick up any docs/releases/<X.Y.Z>.md that's been hand-edited
    # and is now untracked.
    if [[ -f "${REPO_ROOT}/docs/releases/${release_version}.md" ]]; then
        (cd "${REPO_ROOT}" && git add -- "docs/releases/${release_version}.md") || true
    fi
    # Pick up any UNTRACKED snapshot dirs that should be released this
    # cycle — <comp>/<X.Y.Z.W>/ dirs that aren't in the baseline tag
    # AND aren't already tracked. Catches the case where `stage` created
    # the dirs (and git-added them) but they got unstaged before --apply
    # ran, leaving them untracked. Filtered by version-shape regex so
    # unrelated junk dirs can't sneak in.
    local baseline
    baseline="$(git -C "${REPO_ROOT}" describe --tags --abbrev=0 2>/dev/null || true)"
    while IFS= read -r -d '' _vd; do
        local _rel="${_vd#${REPO_ROOT}/}"
        local _ver="${_rel##*/}"
        [[ "${_ver}" =~ ^[0-9]+(\.[0-9]+){2,3}$ ]] || continue
        # Skip if already tracked.
        if [[ -n "$(git -C "${REPO_ROOT}" ls-files -- "${_rel}" 2>/dev/null | head -1)" ]]; then
            continue
        fi
        # Skip if it's in the baseline release tag (shouldn't happen for
        # untracked dirs, but defence in depth).
        if [[ -n "${baseline}" ]] && \
           [[ -n "$(git -C "${REPO_ROOT}" ls-tree -d --name-only "${baseline}" "${_rel}" 2>/dev/null)" ]]; then
            continue
        fi
        (cd "${REPO_ROOT}" && git add -- "${_rel}/") || \
            warn "git add ${_rel}/ failed"
    done < <(find "${REPO_ROOT}" -maxdepth 2 -mindepth 2 -type d \
                -regex '.*/[a-z][a-z0-9_]*/[0-9][0-9.]*' -print0 2>/dev/null)

    if [[ "${COMMIT}" -eq 1 ]]; then
        # Idempotent: if nothing's staged and HEAD already has the
        # release commit, skip the commit step (re-run after a prior
        # --apply --commit). Otherwise commit normally.
        if (cd "${REPO_ROOT}" && git diff --cached --quiet) && \
           (cd "${REPO_ROOT}" && git log -1 --pretty=%B 2>/dev/null) | \
                grep -qE "^chore\(release\): cut ${release_version//./\\.}\b"; then
            log "Release commit for ${release_version} already on HEAD — skipping commit."
        else
            log "Committing release artefacts to ${branch}"
            (cd "${REPO_ROOT}" && \
                git commit -m "chore(release): cut ${release_version} — frozen snapshots + mkdocs nav") || \
                die "Failed to commit release artefacts."
            log ""
            log "✓ Release branch ${branch} committed."
        fi

        # Push the release branch — no tag. The tag is made by
        # `git flow release finish` on main when the release branch
        # merges in, not on the release branch itself.
        phase "Pushing release branch to origin"
        log ""
        if ! (cd "${REPO_ROOT}" && git push origin "${branch}"); then
            die "git push origin ${branch} failed."
        fi
        log "✓ Pushed ${branch} to origin."
        log ""

        # mike deploy + set-default (sequential, blocking). mike treats
        # the version as a string; no git tag required.
        deploy_versioned_docs "${release_version}"
        log ""
        log "Next step (git-flow):"
        log "    git flow release finish ${release_version}"
        log "  (merges ${branch} → main, tags ${release_version} on main, merges back to develop)"
    else
        log ""
        log "Release branch ${branch} created with all release artefacts staged."
        log "Nothing committed (no --commit flag). Review with:"
        log "    git status"
        log "    git diff --cached"
        log ""
        log "When ready:"
        log "    ./release.sh --apply --release-version ${release_version} --commit"
        log "  or commit manually:"
        log "    git commit -m 'chore(release): cut ${release_version}'"
        log "    git push origin ${branch}"
        log ""
        log "After --commit (or manual push), finish via git-flow:"
        log "    git flow release finish ${release_version}"
        log "  (tags ${release_version} on main and merges back to develop)"
    fi
}

# Auto-detect next release version from (in order of precedence):
#   1. --release-version pin from the caller
#   2. Current branch name when on release/X.Y.Z (honours the operator
#      having already cut the release branch; avoids the stale-tag
#      footgun where a leftover X.Y.Z tag from an aborted prior cycle
#      makes the next-minor bump suggest X.(Y+1).0 instead of X.Y.Z)
#   3. Bump the minor segment of the last release tag (0.20.0 → 0.21.0).
# Point releases (0.20.0 → 0.20.1) require --release-version.
auto_detect_release_version() {
    [[ -n "${RELEASE_VERSION}" ]] && return 0
    local current_branch
    current_branch="$(git -C "${REPO_ROOT}" rev-parse --abbrev-ref HEAD 2>/dev/null || true)"
    if [[ "${current_branch}" =~ ^release/([0-9]+\.[0-9]+\.[0-9]+)$ ]]; then
        RELEASE_VERSION="${BASH_REMATCH[1]}"
        RELEASE_VERSION_AUTO=1
        return 0
    fi
    local last_tag
    last_tag="$(git -C "${REPO_ROOT}" describe --tags --abbrev=0 2>/dev/null || true)"
    if [[ "${last_tag}" =~ ^([0-9]+)\.([0-9]+)\.([0-9]+)$ ]]; then
        local maj="${BASH_REMATCH[1]}"
        local min="${BASH_REMATCH[2]}"
        RELEASE_VERSION="${maj}.$((min + 1)).0"
        RELEASE_VERSION_AUTO=1
    fi
}
RELEASE_VERSION_AUTO=0
auto_detect_release_version

# ----------------------------------------------------------------------------
# versions_released.yaml updater
# ----------------------------------------------------------------------------
#
# Rewrites the `components:` map so each bumped component points at its
# newly-released version. New components (not previously listed) are
# appended in alphabetic order. Lines outside the components: block are
# preserved verbatim.

update_versions_released() {
    local manifest="${REPO_ROOT}/versions_released.yaml"
    if [[ ! -f "${manifest}" ]]; then
        warn "versions_released.yaml not found — skipping manifest update."
        return 1
    fi
    if [[ ${#BUMPED_COMPONENTS[@]} -eq 0 ]]; then
        return 0
    fi
    python3 - "${manifest}" "${BUMPED_COMPONENTS[@]}" <<'PYEOF' || return 1
import re, sys
manifest_path = sys.argv[1]
bumps = dict(arg.split(":", 1) for arg in sys.argv[2:])

with open(manifest_path) as f:
    lines = f.readlines()

# Locate `components:` block.
start = None
for i, line in enumerate(lines):
    if re.match(r'^components:\s*$', line):
        start = i + 1
        break
if start is None:
    sys.stderr.write("versions_released.yaml: missing 'components:' block\n")
    sys.exit(1)

end = len(lines)
for i in range(start, len(lines)):
    line = lines[i]
    if line.strip() == "":
        continue
    if not (line.startswith("  ") or line.startswith("\t")):
        end = i
        break

# Parse existing entries, preserve leading comments / blank lines.
entry_re = re.compile(r'^(\s+)([A-Za-z][\w/]*):\s*(\S+)\s*$')
existing = {}
for i in range(start, end):
    m = entry_re.match(lines[i])
    if m:
        existing[m.group(2)] = (m.group(1), i)

# Strip any stale "<comp>: current" entries — versions_released.yaml is
# the released-cohort manifest, so by definition no component should pin
# to `current`. The default: current fallback already covers components
# that haven't released yet. A `<comp>: current` entry is leftover
# placeholder state from before the component's first release.
stale_current = [
    (comp, idx) for comp, (indent, idx) in existing.items()
    if lines[idx].rstrip().endswith(": current")
]
# Remove from highest idx down so earlier indices stay valid.
for comp, idx in sorted(stale_current, key=lambda t: -t[1]):
    del lines[idx]
    del existing[comp]
    end -= 1
    # Shift subsequent indices in `existing` down by 1.
    existing = {
        c: (i, (j - 1 if j > idx else j))
        for c, (i, j) in existing.items()
    }

# Apply bumps to existing entries; collect components new to the map.
new_components = []
for comp, version in bumps.items():
    if comp in existing:
        indent, idx = existing[comp]
        lines[idx] = f"{indent}{comp}: {version}\n"
    else:
        new_components.append((comp, version))

# Append new components alphabetically just before the end of the block.
if new_components:
    indent = "  "
    for _, (i, _) in existing.items():
        pass
    for i in range(start, end):
        m = entry_re.match(lines[i])
        if m:
            indent = m.group(1)
            break
    insertion = [f"{indent}{c}: {v}\n" for c, v in sorted(new_components)]
    lines[end:end] = insertion

with open(manifest_path, "w") as f:
    f.writelines(lines)
PYEOF
}

# ----------------------------------------------------------------------------
# Release notes skeleton generator
# ----------------------------------------------------------------------------
#
# Drops a docs/releases/<release>.md skeleton listing the bumped components.
# Idempotent: if the file already exists it's left untouched (the operator
# may have hand-written prose already).

generate_release_notes_skeleton() {
    local release_version="$1"
    local notes_dir="${REPO_ROOT}/docs/releases"
    local notes_file="${notes_dir}/${release_version}.md"
    mkdir -p "${notes_dir}"
    if [[ -f "${notes_file}" ]]; then
        log "  Release notes already exist: docs/releases/${release_version}.md (preserving)"
        return 0
    fi
    {
        echo "# RDK HALIF AIDL ${release_version} Release Notes"
        echo ""
        echo "Release date: TBD"
        echo ""
        echo "Base comparison: \`${SINCE_REF}...${release_version}\`"
        echo ""
        echo "## Headline"
        echo ""
        echo "<!-- One paragraph: what's the headline change for this cohort? -->"
        echo ""
        echo "## Component bumps"
        echo ""
        for entry in "${BUMPED_COMPONENTS[@]}"; do
            local comp="${entry%%:*}"
            local version="${entry##*:}"
            echo "- \`${comp}\` → ${version}"
        done
        echo ""
        echo "## Highlights"
        echo ""
        echo "<!-- Hand-edit the prose. Use the git log on the release branch as source material:"
        echo "        git log --first-parent --pretty='- %s' ${SINCE_REF}..HEAD"
        echo "-->"
        echo ""
        echo "## Upgrade Guide"
        echo ""
        echo "<!-- Hand-edit. -->"
    } > "${notes_file}"
    log "  Generated skeleton: docs/releases/${release_version}.md"
}

# ----------------------------------------------------------------------------
# CHANGELOG.md regenerator (#580)
# ----------------------------------------------------------------------------
#
# Prepends a new "#### [X.Y.Z](compare-url)" section to CHANGELOG.md
# containing every first-parent commit since SINCE_REF. Subject lines
# are formatted to match the existing auto-changelog style. The PR
# reference is extracted from the trailing "(#NNN)" pattern in the
# commit subject.
#
# Idempotent: if a section for this release_version is already present,
# the function leaves the file untouched (the operator may have hand-
# edited the prose).

regenerate_changelog() {
    local release_version="$1"
    local changelog="${REPO_ROOT}/CHANGELOG.md"
    if [[ ! -f "${changelog}" ]]; then
        warn "CHANGELOG.md not found — skipping."
        return 0
    fi

    if grep -qF "[${release_version}]" "${changelog}"; then
        log "  CHANGELOG.md already has a section for ${release_version} — preserving."
        return 0
    fi

    local gh_owner_repo="${GH_REPO:-rdkcentral/rdk-halif-aidl}"
    local compare_url="https://github.com/${gh_owner_repo}/compare/${SINCE_REF}...${release_version}"

    # Build the new section in a tempfile to keep the python prepend logic
    # simple.
    local tmp_section
    tmp_section="$(mktemp)"
    {
        echo ""
        echo "#### [${release_version}](${compare_url})"
        echo ""
        local _pr_regex='\(#([0-9]+)\)[[:space:]]*$'
        git -C "${REPO_ROOT}" log --first-parent --pretty='%s' "${SINCE_REF}..HEAD" \
            | grep -vE '^Merge (branch|tag|pull request)' \
            | while IFS= read -r subject; do
                pr=""
                if [[ "${subject}" =~ $_pr_regex ]]; then
                    pr="${BASH_REMATCH[1]}"
                fi
                if [[ -n "${pr}" ]]; then
                    echo "- ${subject} [\`#${pr}\`](https://github.com/${gh_owner_repo}/pull/${pr})"
                else
                    echo "- ${subject}"
                fi
            done
    } > "${tmp_section}"

    # Prepend the new section after the existing intro lines (before the
    # first "####" entry, or at the end of the file if no entries exist).
    python3 - "${changelog}" "${tmp_section}" <<'PYEOF' || { rm -f "${tmp_section}"; return 1; }
import sys
changelog_path, section_path = sys.argv[1:3]
with open(changelog_path) as f:
    existing = f.read()
with open(section_path) as f:
    new_section = f.read()
# Insert the new section before the first `#### ` heading. If none exists,
# append to end (intro-only file).
idx = existing.find("\n#### ")
if idx == -1:
    out = existing.rstrip() + "\n" + new_section
else:
    out = existing[:idx + 1] + new_section + existing[idx + 1:]
with open(changelog_path, "w") as f:
    f.write(out)
PYEOF
    rm -f "${tmp_section}"
    log "  CHANGELOG.md: prepended ${release_version} section"
}

# ----------------------------------------------------------------------------
# Doc + build-config version-ref audit (#581 / #582)
# ----------------------------------------------------------------------------
#
# Surfaces every version-shaped string ("0.X.Y.Z") found in:
#   - <comp>/current/docs/*.md           (#581)
#   - <comp>/current/CMakeLists.txt      (#582)
#   - <comp>/current/interface.yaml      (#582)
#   - <comp>/current/hfp-*.yaml          (#582)
#   - <comp>/current/mkdocs.yml          (#582)
#
# These are NOT auto-rewritten — most are intentional historical /
# migration / changelog refs that would be corrupted by a blind sed.
# Instead, the audit prints each hit so the operator can review.

audit_version_refs() {
    local hits=0
    local found=()
    local file
    while IFS= read -r -d '' file; do
        local matches
        matches="$(grep -nE '\b0\.[0-9]+\.[0-9]+\.[0-9]+\b' "${file}" 2>/dev/null || true)"
        [[ -z "${matches}" ]] || found+=("${file}|${matches}")
    done < <(find "${REPO_ROOT}" -maxdepth 4 -type f \
        \( -path '*/current/docs/*.md' \
        -o -name CMakeLists.txt -path '*/current/*' \
        -o -name interface.yaml  -path '*/current/*' \
        -o -name 'hfp-*.yaml'    -path '*/current/*' \
        -o -name mkdocs.yml      -path '*/current/*' \) -print0)

    [[ ${#found[@]} -eq 0 ]] && return 0

    log ""
    log "ℹ️  Version-ref audit (review only — not auto-rewritten):"
    log "    These files mention version-shaped strings (0.X.Y.Z). Most are intentional"
    log "    (changelog tables, migration notes, CEC physical addresses). Skim before"
    log "    --apply to confirm none need a manual update."
    log ""
    for entry in "${found[@]}"; do
        local f="${entry%%|*}"
        local rest="${entry#*|}"
        log "    ${f#${REPO_ROOT}/}:"
        while IFS= read -r line; do
            [[ -n "${line}" ]] && log "        ${line}"
        done <<< "${rest}"
    done
}

MODE="PLAN (read-only — what the staged plan would do)"
[[ "${APPLY}"   -eq 1 ]] && MODE="APPLY (writes + release branch; tag made by git-flow release finish)"
[[ "${DRY_RUN}" -eq 1 ]] && MODE="DRY-RUN (preview only — same as bare ./release.sh)"
[[ "${CHECK_MODE}" -eq 1 ]] && MODE="CHECK (detected-changes preview, bypasses plan)"

phase "Computing per-component version bumps..."
log ""
log "Release version scan"
log "  Mode: ${MODE}"
log "  Base ref: ${SINCE_REF}"
log "  Range: ${SINCE_REF}..HEAD"
if [[ -n "${RELEASE_VERSION}" ]]; then
    if [[ "${RELEASE_VERSION_AUTO}" -eq 1 ]]; then
        log "  Release version: ${RELEASE_VERSION} (auto-detected; override with --release-version)"
    else
        log "  Release version: ${RELEASE_VERSION}"
    fi
fi
if [[ "${ENABLE_GH_LABELS}" -eq 1 ]]; then
    log "  Labels: GitHub PR labels enabled (${GH_REPO})"
else
    log "  Labels: heuristic only"
fi
log ""

# Map internal bump tokens to operator-readable change classes.
bump_label() {
    case "$1" in
        generation) echo "Breaking" ;;
        minor)      echo "Major" ;;
        patch)      echo "Minor" ;;
        pinned)     echo "Pinned" ;;
        none)       echo "-" ;;
        *)          echo "$1" ;;
    esac
}

# Buffer table rows — printed at the END of the report (after all
# diagnostic blocks) so the final-decision table is the last thing
# the operator sees.
TABLE_ROWS=()
TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-16s %-8s %s" "Module" "Current" "Next" "Bump" "Planned" "Status")")
TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-16s %-8s %s" "------" "-------" "----" "----" "-------" "------")")

changed_count=0
error_count=0
BUMPED_COMPONENTS=()
declare -A METADATA_DRIFT=()  # comp -> "metadata_says|discovered_truth"

# Auto-discover the "real" current released version of a component.
# Uses the LAST RELEASE TAG (not HEAD) as the baseline — phantom
# snapshots committed to develop without being part of a tagged
# release (e.g. firmwareupdate/0.2.0.0/ added by a "chore" commit
# after the flash rename, never in 0.20.0) don't count as released.
# Picks the highest version present at that tag by `sort -V`.
discover_current_version() {
    local comp="$1"
    local baseline
    baseline="$(git describe --tags --abbrev=0 2>/dev/null || true)"
    [[ -n "${baseline}" ]] || return 0   # no tags → no released baseline
    git ls-tree -d --name-only "${baseline}" "${comp}/" 2>/dev/null \
        | awk -F/ '{print $NF}' \
        | grep -E '^[0-9]+(\.[0-9]+){2,3}$' \
        | sort -V \
        | tail -1 || true
}

# When a component has no released baseline (new since last tag), check
# whether the operator has pre-staged a snapshot under <comp>/<version>/
# in HEAD (committed via a "chore" or release-prep PR). If yes, use
# that as the initial-release version. If no, seed at 0.1.0.0.
discover_pre_staged_version() {
    local comp="$1"
    git ls-tree -d --name-only HEAD "${comp}/" 2>/dev/null \
        | awk -F/ '{print $NF}' \
        | grep -E '^[0-9]+(\.[0-9]+){2,3}$' \
        | sort -V \
        | tail -1 || true
}

# Aggregate SHA256 of every .aidl file under a directory tree, sorted by
# path. Two trees with identical AIDL contents produce the same hash;
# any add/remove/modify changes the hash. Returns empty string if the
# directory doesn't exist or has no .aidl files.
compute_aidl_hash_for_dir() {
    local dir="$1"
    [[ -d "${dir}" ]] || { echo ""; return 0; }
    local h
    h="$(find "${dir}" -name '*.aidl' -type f 2>/dev/null \
        | sort \
        | while IFS= read -r f; do
            printf '%s:%s\n' "${f#${dir}/}" "$(sha256sum "${f}" 2>/dev/null | awk '{print $1}')"
          done \
        | sha256sum 2>/dev/null | awk '{print $1}')"
    [[ "${h}" == "$(echo -n "" | sha256sum | awk '{print $1}')" ]] && h=""
    echo "${h}"
}

# Compare a module's current/ AIDL hash against the highest tracked
# snapshot. Echoes one of: "unchanged" / "CHANGED" / "new" / "missing".
aidl_hash_status() {
    local comp="$1"
    local latest
    latest="$(discover_current_version "${comp}")"
    if [[ -z "${latest}" ]]; then
        echo "new"      # never released; no baseline to compare against
        return 0
    fi
    local cur_hash snap_hash
    cur_hash="$(compute_aidl_hash_for_dir "${REPO_ROOT}/${comp}/current")"
    snap_hash="$(compute_aidl_hash_for_dir "${REPO_ROOT}/${comp}/${latest}")"
    if [[ -z "${cur_hash}" || -z "${snap_hash}" ]]; then
        echo "missing"  # one side has no .aidl files
        return 0
    fi
    if [[ "${cur_hash}" == "${snap_hash}" ]]; then
        echo "unchanged"
    else
        echo "CHANGED"
    fi
}

mapfile -t TOUCHED_COMPONENTS < <(printf '%s\n' "${!COMP_TOUCHED[@]}" | sort)
declare -A SKIPPED_NOT_BUILDABLE=()
for comp in "${TOUCHED_COMPONENTS[@]}"; do
    meta="${REPO_ROOT}/${comp}/metadata.yaml"
    if [[ ! -f "${meta}" ]]; then
        TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-16s %-8s %s" "${comp}" "-" "-" "-" "no" "metadata missing")")
        error_count=$((error_count + 1))
        continue
    fi

    # Non-buildable components (no current/interface.yaml — broadcast,
    # ffv, r4ce, …) get a one-line "skipped" row and are excluded from
    # bumping/snapshotting. They re-enter as soon as interface.yaml is
    # added. Reason text is sourced from metadata.yaml notes.status_detail
    # when present, so the operator sees WHY without spelunking.
    if ! is_buildable_component "${comp}"; then
        reason="$(awk '
            /^notes:/ {in_notes=1; next}
            in_notes && /^[^ ]/ {in_notes=0}
            in_notes && /^[[:space:]]+status_detail:/ {
                sub(/^[[:space:]]+status_detail:[[:space:]]*/, "");
                gsub(/^"|"$/, "");
                print; exit
            }' "${meta}" 2>/dev/null)"
        TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-16s %-8s %s" "${comp}" "-" "-" "skipped" "no" "not buildable")")
        SKIPPED_NOT_BUILDABLE[$comp]="${reason:-no current/interface.yaml}"
        continue
    fi

    metadata_version="$(awk -F': *' '$1=="version"{print $2; exit}' "${meta}")"

    # Source of truth: the highest tracked <comp>/<version>/ in git. If
    # nothing is tracked yet (component added since last release), seed
    # the first release at 0.1.0.0 and treat this as the initial cut —
    # no further bump (the very act of creating 0.1.0.0/ IS the release).
    current_version="$(discover_current_version "${comp}")"
    is_initial=0
    if [[ -z "${current_version}" ]]; then
        is_initial=1
        # Pre-staged snapshot in HEAD (e.g. firmwareupdate/0.2.0.0/
        # added via a chore commit) IS the operator's intent for the
        # initial release version. Use it. Otherwise default to 0.1.0.0.
        current_version="$(discover_pre_staged_version "${comp}")"
        [[ -n "${current_version}" ]] || current_version="0.1.0.0"
    fi

    # (Drift detection happens after compute_next_versions below — we
    # compare metadata.yaml against the computed NEXT_VERSION, not
    # against tracked-latest. metadata.yaml is *supposed* to be pre-
    # bumped to the upcoming version by PR authors; that's not drift.)

    bump="none"
    if [[ "${COMP_BREAKING[$comp]:-0}" -eq 1 ]]; then
        bump="generation"
    elif [[ "${COMP_NON_DOC[$comp]:-0}" -eq 1 ]]; then
        bump="minor"
    elif [[ "${COMP_DOC[$comp]:-0}" -eq 1 ]]; then
        bump="patch"
    fi

    if [[ "${is_initial}" -eq 1 ]]; then
        # Initial release of a new component — the seed (0.1.0.0) IS the
        # release. Suppress any label-driven bump so we don't ship a
        # brand-new component already at 0.2.0.0.
        bump="none"
    fi

    # AIDL-hash gate: the cohort versioning is about INTERFACE STABILITY.
    # If the .aidl files in current/ hash byte-identical to the latest
    # tracked snapshot, the binary interface hasn't moved — no bump is
    # warranted, regardless of what PR labels said. Catches the case
    # where a Breaking-Change PR (e.g. a build-infrastructure change like
    # #567 gitignoring */current/include) touched non-interface files
    # under a component, falsely flagging it Breaking.
    _hash_for_bump="$(aidl_hash_status "${comp}")"
    if [[ "${_hash_for_bump}" == "unchanged" && "${bump}" != "none" && "${is_initial}" -ne 1 ]]; then
        COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}gate: AIDL hash unchanged — interface byte-identical to ${current_version}, label-derived bump (${bump}) suppressed"$'\n'
        bump="none"
        # Drop the label flags so the transitive subsume pass doesn't
        # use them to re-promote downstream importers.
        unset 'COMP_BREAKING[$comp]' 'COMP_NON_DOC[$comp]' 'COMP_DOC[$comp]' 2>/dev/null || true
    fi

    compute_next_versions "${current_version}" "${bump}"

    # Explicit version pin from `stage <module> --version X.Y.Z.W` wins
    # over the label-derived auto-bump. PIN_VERSIONS lives in-memory
    # only — once the stage call's writes complete, the pinned version
    # is recorded in the snapshot dir + metadata.yaml.
    if [[ -n "${PIN_VERSIONS[$comp]:-}" ]]; then
        NEXT_VERSION="${PIN_VERSIONS[$comp]}"
        bump="pinned"
        COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}stage: explicit --version ${NEXT_VERSION}"$'\n'
    fi

    # Drift detection: metadata.yaml is *supposed* to be pre-bumped by
    # PR authors to the planned next version. If it matches the
    # detector's NEXT_VERSION, no drift — that's the healthy state.
    # Real drift = metadata.yaml says X but detector computes Y for the
    # next release. Surface that case so the operator sees the
    # mismatch before it's silently healed (overwritten) at apply time.
    if [[ -n "${metadata_version}" && "${metadata_version}" != "${NEXT_VERSION}" ]]; then
        METADATA_DRIFT[$comp]="${metadata_version}|${NEXT_VERSION}"
    fi

    status="ok"
    if [[ "${NEXT_NOTE}" == "breaking change on frozen interface: create new component instead" ]]; then
        status="manual action required"
        error_count=$((error_count + 1))
    elif [[ "${NEXT_NOTE}" == "unsupported version format" ]]; then
        status="unsupported version format"
        error_count=$((error_count + 1))
    fi

    # For an initial release, NEXT_VERSION == current_version but we
    # DO want to ship the snapshot — override changed-detection so the
    # 0.1.0.0/ dir actually gets created.
    if [[ "${is_initial}" -eq 1 ]]; then
        status="initial release"
    fi

    # Decide qualification for `--accept-all` BEFORE building the table
    # row, so the Planned column reflects the auto-staged state.
    _qualifies_for_staging=0
    if [[ "${is_initial}" -eq 1 && "${status}" == "initial release" ]]; then
        _qualifies_for_staging=1
    elif [[ "${current_version}" != "${NEXT_VERSION}" && "${status}" == "ok" ]]; then
        _qualifies_for_staging=1
    fi
    if [[ "${ACCEPT_ALL}" -eq 1 && "${_qualifies_for_staging}" -eq 1 \
          && -z "${ACTUAL_PLAN[$comp]+x}" ]]; then
        ACTUAL_PLAN[$comp]=""
    fi

    _planned="no"
    [[ -n "${ACTUAL_PLAN[$comp]+x}" ]] && _planned="yes"

    # Initial release IS the bump — surface it in the Bump column rather
    # than leaving Bump="-" with Status="initial release" (redundant).
    _bump_display="$(bump_label "${bump}")"
    _status_display="${status}"
    if [[ "${is_initial}" -eq 1 && "${status}" == "initial release" ]]; then
        _bump_display="initial release"
        _status_display="ok"
    fi

    TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-16s %-8s %s" \
        "${comp}" "${current_version}" "${NEXT_VERSION}" \
        "${_bump_display}" "${_planned}" "${_status_display}")")

    # Verbose detail: enabled only by --verbose. Keeps the default view a
    # compact one-line-per-module table; `--verbose` shows AIDL hash status,
    # the per-commit/PR derivation, and the file list.
    if [[ "${VERBOSE}" -eq 1 ]]; then
        # AIDL hash status — did the .aidl contents actually change since
        # the latest released snapshot? Catches "silent drift": current/
        # changed but no PR label was applied, so the auto-bump came out
        # as `none` despite the interface having moved.
        _hash_status="$(aidl_hash_status "${comp}")"
        case "${_hash_status}" in
            unchanged) echo "    AIDL hash: unchanged since ${current_version}" ;;
            CHANGED)
                echo "    AIDL hash: CHANGED since ${current_version} — interface contents differ"
                if [[ "${bump}" == "none" && "${is_initial}" -ne 1 ]]; then
                    echo "             ⚠️  No PR label triggered a bump but AIDL changed —"
                    echo "                operator should review whether a bump is needed."
                fi
                ;;
            new)       echo "    AIDL hash: (new module — no prior snapshot to compare)" ;;
            missing)   echo "    AIDL hash: (n/a — placeholder component, no .aidl files)" ;;
        esac
        # Reasons (commit/PR → bump-level derivation, plus subsume/plan).
        if [[ -n "${COMP_REASONS[$comp]:-}" ]]; then
            echo "    Why this bump:"
            while IFS= read -r line; do
                [[ -n "${line}" ]] && echo "      - ${line}"
            done <<< "${COMP_REASONS[$comp]:-}"
        fi
        # File summary — count + first 5 paths.
        if [[ -n "${COMP_FILES[$comp]:-}" ]]; then
            _file_count=$(printf '%s' "${COMP_FILES[$comp]}" | grep -c .)
            echo "    Files touched (${_file_count}):"
            printf '%s' "${COMP_FILES[$comp]}" | sort -u | head -5 | sed 's/^/      /'
            if [[ "${_file_count}" -gt 5 ]]; then
                echo "      ... ($((_file_count - 5)) more)"
            fi
        fi
        echo ""
    fi

    needs_snapshot=0
    if [[ "${is_initial}" -eq 1 && "${status}" == "initial release" ]]; then
        needs_snapshot=1
    elif [[ "${current_version}" != "${NEXT_VERSION}" && "${status}" == "ok" ]]; then
        needs_snapshot=1
    fi

    if [[ "${needs_snapshot}" -eq 1 ]]; then
        # Record this component as bumped so the snapshot / mkdocs /
        # release-tag steps and the dry-run preview block can iterate
        # them. metadata.yaml is NOT written here — that happens in the
        # snapshot loop below, AFTER the snapshot succeeds, so a partial
        # release abort doesn't leave behind "metadata says X but no X/
        # snapshot exists" state.
        BUMPED_COMPONENTS+=("${comp}:${NEXT_VERSION}")
        changed_count=$((changed_count + 1))
    fi
done

# Surface metadata.yaml drift — but only for modules that AREN'T about
# to be staged this run. Modules in BUMPED_COMPONENTS will have their
# metadata.yaml rewritten by update_metadata in the write loop below;
# warning about them here would be misleading ("disagrees" → about to
# be fixed). Read-only invocations still show every drift case.
declare -A _staged_now=()
for entry in "${BUMPED_COMPONENTS[@]}"; do
    _staged_now[${entry%%:*}]=1
done
_unstaged_drift=()
for comp in $(printf '%s\n' "${!METADATA_DRIFT[@]}" | sort); do
    [[ -n "${_staged_now[$comp]:-}" ]] && continue
    _unstaged_drift+=("${comp}")
done
if [[ ${#_unstaged_drift[@]} -gt 0 ]]; then
    log ""
    log "⚠️  metadata.yaml disagrees with the computed Next version for some modules"
    log "    (these are NOT in the current stage set — staging them will fix the drift):"
    log ""
    for comp in "${_unstaged_drift[@]}"; do
        v="${METADATA_DRIFT[$comp]}"
        log "    ${comp}: metadata.yaml=${v%|*}   detector Next=${v#*|}"
    done
fi

# Non-buildable components — broadcast, ffv, r4ce — have no
# current/interface.yaml so the build can't snapshot them. Surface them
# with the metadata.yaml status_detail reason so the operator sees WHY
# they're skipped, not just that they are.
if [[ ${#SKIPPED_NOT_BUILDABLE[@]} -gt 0 ]]; then
    log ""
    log "ℹ️  Skipped (not yet integrated into the build — no current/interface.yaml):"
    for comp in $(printf '%s\n' "${!SKIPPED_NOT_BUILDABLE[@]}" | sort); do
        log "    ${comp}: ${SKIPPED_NOT_BUILDABLE[$comp]}"
    done
    log ""
    log "    These re-enter the release flow as soon as their interface.yaml is added."
fi

# Transitive-bump diagnostic. Components that didn't have any direct PR-label
# change but are bumping because a dependency bumped — surface them here so
# the operator sees the cascade reasoning at a glance.
if [[ ${#COMP_TRANSITIVE[@]} -gt 0 ]]; then
    log ""
    log "ℹ️  Transitive bumps (subsume rule — dependent components inherit the highest dep bump):"
    for comp in $(printf '%s\n' "${!COMP_TRANSITIVE[@]}" | sort); do
        # The subsume: line in COMP_REASONS captures which dep caused which level.
        sub_lines="$(printf '%s' "${COMP_REASONS[$comp]:-}" | grep '^subsume:' | head -3)"
        log "    ${comp}:"
        while IFS= read -r r; do
            [[ -n "${r}" ]] && log "        ${r}"
        done <<< "${sub_lines}"
    done
fi

# ----------------------------------------------------------------------------
# Stale-snapshot detection
# ----------------------------------------------------------------------------
#
# A component's <module>/<version>/ directory should be either (a) tracked
# in git (a released snapshot) or (b) the next version about to be created
# by this run. Anything else is leftover from a previous half-run or from
# the retired per-component release tool — surface it so the operator can
# clean up before --apply.

declare -A NEXT_VERSION_BY_COMP=()
for entry in "${BUMPED_COMPONENTS[@]}"; do
    NEXT_VERSION_BY_COMP["${entry%%:*}"]="${entry##*:}"
done

stale_snapshots=()
for comp in "${TOUCHED_COMPONENTS[@]}"; do
    [[ -d "${REPO_ROOT}/${comp}" ]] || continue
    while IFS= read -r -d '' versioned_dir; do
        version="${versioned_dir##*/}"
        # Skip current/ and non-version dirs (e.g. docs/).
        [[ "${version}" =~ ^[0-9]+(\.[0-9]+)*$ ]] || continue
        # Tracked snapshots are fine. A snapshot doesn't carry a
        # metadata.yaml at the version-dir level (metadata lives at the
        # component root), so test by asking git whether anything at all
        # is tracked under <comp>/<version>/.
        if [[ -n "$(git ls-files -- "${comp}/${version}/" 2>/dev/null | head -1)" ]]; then
            continue
        fi
        # Untracked but matches the about-to-be-created next version: fine,
        # it'll be created (and the existing-dir check inside
        # create_snapshot() will catch a stale one with mismatched contents).
        if [[ "${NEXT_VERSION_BY_COMP[$comp]:-}" == "${version}" ]]; then
            continue
        fi
        stale_snapshots+=("${comp}/${version}")
    done < <(find "${REPO_ROOT}/${comp}" -maxdepth 1 -mindepth 1 -type d -print0)
done

if [[ ${#stale_snapshots[@]} -gt 0 ]]; then
    log ""
    log "⚠️  Stale snapshot directories detected (untracked, not the next-to-be-created version):"
    for snap in "${stale_snapshots[@]}"; do
        log "    ${snap}/"
    done
    log ""
    log "    These look like leftovers from a previous half-run or the retired"
    log "    per-component release tool. Remove them before --apply, e.g.:"
    log ""
    for snap in "${stale_snapshots[@]}"; do
        log "        rm -rf ${snap}/"
    done
fi

# ----------------------------------------------------------------------------
# Dry-run preview (--dry-run only)
# ----------------------------------------------------------------------------

if [[ "${DRY_RUN}" -eq 1 && ${#BUMPED_COMPONENTS[@]} -gt 0 ]]; then
    log ""
    log "Pipeline preview — what default ./release.sh would do:"
    log ""
    log "  For each bumped component (in order):"
    for entry in "${BUMPED_COMPONENTS[@]}"; do
        comp="${entry%%:*}"
        version="${entry##*:}"
        if [[ ! -d "${REPO_ROOT}/${comp}/current" ]]; then
            log "    ${comp} ${version}: placeholder component (no current/) — metadata.yaml bump only, no snapshot"
            continue
        fi
        log "    ${comp} ${version}:"
        log "        1. ./build_modules.sh ${comp}     (regenerate current/include + current/src)"
        log "        2. cp -r ${comp}/current/  ${comp}/${version}/"
        log "        3. git add ${comp}/${version}/"
        log "        4. sed -i version: in ${comp}/metadata.yaml -> ${version}"
    done
    log ""
    log "  Then once per release:"
    log "    5. Update versions_released.yaml components: map"
    log "    6. Insert mkdocs.yml nav entries for the ${#BUMPED_COMPONENTS[@]} new <module>/<version>/ doc sets"
    log "    7. Generate docs/releases/${RELEASE_VERSION}.md release-notes skeleton (if absent)"
    log "    8. Prepend a new ${RELEASE_VERSION} section to CHANGELOG.md"
    log "    9. Audit docs + build configs for version-shaped strings (review only)"
    log "   10. ./build_modules.sh all                 (build current cohort)"
    log "   11. ./build_modules.sh manifest            (build released cohort via versions_released.yaml)"
    log ""
    log "  With --apply, additionally:"
    log "   12. git checkout -b release/${RELEASE_VERSION}"
    log "  With --apply --commit, additionally:"
    log "   13. git commit  release artefacts (snapshots + manifests + nav + notes + CHANGELOG)"
    log "   14. git push origin release/${RELEASE_VERSION}"
    log "   15. mike deploy ${RELEASE_VERSION} --push  &&  mike set-default ${RELEASE_VERSION} --push"
    log ""
    log "  The tag is created by 'git flow release finish ${RELEASE_VERSION}' on main,"
    log "  not by this script."
fi

# ----------------------------------------------------------------------------
# Stage pipeline (default + --apply)
# ----------------------------------------------------------------------------
#
# Default mode (DO_WRITES=1, DO_BRANCH=0): regenerate, snapshot, update
# metadata.yaml + versions_released.yaml + mkdocs.yml + release-notes
# skeleton, run a verification build. Leaves changes in the working tree
# for review via `git diff --cached`.
#
# --apply (DO_WRITES=1, DO_BRANCH=1): all of the above PLUS create
# release/X.Y.Z branch, commit, tag.

if [[ "${DO_WRITES}" -eq 1 && "${changed_count}" -gt 0 ]]; then
    if [[ -x "${REPO_ROOT}/scripts/generate_rag_report.sh" ]]; then
        "${REPO_ROOT}/scripts/generate_rag_report.sh" >/dev/null || warn "Failed to regenerate RAG_STATUS_REPORT.md"
    fi

    if [[ -z "${RELEASE_VERSION}" ]]; then
        die "no --release-version, and auto-detect found no prior release tag to derive from. Provide e.g. --release-version 0.21.0"
    fi

    # 1. Frozen snapshots — regen-during-freeze, copy current/ → <version>/, git add.
    if [[ "${NO_SNAPSHOT}" -eq 1 ]]; then
        log ""
        log "Snapshot creation: SKIPPED (--no-snapshot)"
    else
        phase "Creating frozen snapshots (${changed_count} component(s))..."
        log ""
        log "Creating frozen snapshots for ${changed_count} bumped component(s):"
        snapshot_fail=0
        snapshot_failed_names=()
        for entry in "${BUMPED_COMPONENTS[@]}"; do
            comp="${entry%%:*}"
            version="${entry##*:}"
            if create_snapshot "${comp}" "${version}"; then
                # metadata.yaml is bumped only AFTER the snapshot has
                # been successfully created and staged. Any per-component
                # failure leaves metadata.yaml untouched, preserving the
                # invariant: every metadata.yaml `version:` corresponds
                # to a snapshot dir that actually exists.
                update_metadata "${REPO_ROOT}/${comp}/metadata.yaml" "${version}"
            else
                snapshot_fail=$((snapshot_fail + 1))
                snapshot_failed_names+=("${comp}")
            fi
        done
        if [[ "${snapshot_fail}" -gt 0 ]]; then
            log ""
            log "❌ Snapshot creation failed for ${snapshot_fail} component(s):"
            for failed in "${snapshot_failed_names[@]}"; do
                log "    ${failed}  (build log: out/release-snapshot-${failed//\//_}.log)"
            done
            log ""
            log "    If a failing component isn't ready for release yet, mark it"
            log "    incubating by removing its current/interface.yaml — the release"
            log "    script then skips it cleanly. Otherwise inspect the build logs"
            log "    above and fix the underlying issue."
            die "Aborting release: ${snapshot_fail} snapshot(s) failed (${snapshot_failed_names[*]})."
        fi
    fi

    # 2. versions_released.yaml — the released-cohort build manifest.
    phase "Updating versions_released.yaml..."
    log ""
    log "Updating versions_released.yaml for ${changed_count} bumped component(s)..."
    if ! update_versions_released; then
        die "versions_released.yaml update failed. Aborting release."
    fi
    (cd "${REPO_ROOT}" && git add versions_released.yaml) \
        || warn "git add versions_released.yaml failed (file may be untracked)"

    # 3. mkdocs.yml entries.
    if [[ "${NO_MKDOCS}" -eq 1 ]]; then
        log ""
        log "mkdocs.yml update: SKIPPED (--no-mkdocs)"
    else
        phase "Updating mkdocs.yml..."
        log ""
        log "Updating mkdocs.yml for ${changed_count} bumped component(s):"
        mkdocs_fail=0
        for entry in "${BUMPED_COMPONENTS[@]}"; do
            comp="${entry%%:*}"
            version="${entry##*:}"
            if ! update_mkdocs_for_release "${comp}" "${version}"; then
                mkdocs_fail=$((mkdocs_fail + 1))
            fi
        done
        if [[ "${mkdocs_fail}" -gt 0 ]]; then
            die "${mkdocs_fail} mkdocs.yml update(s) failed. Aborting release (re-run with --no-mkdocs to bypass for testing)."
        fi
    fi

    # Stage the bumped metadata.yaml files so `git status` / `git diff --cached`
    # shows the operator the full release diff for review before --apply.
    for entry in "${BUMPED_COMPONENTS[@]}"; do
        _bm_comp="${entry%%:*}"
        (cd "${REPO_ROOT}" && git add "${_bm_comp}/metadata.yaml") \
            || warn "git add ${_bm_comp}/metadata.yaml failed"
    done

    # 4. Release-notes skeleton.
    phase "Generating release-notes skeleton..."
    log ""
    generate_release_notes_skeleton "${RELEASE_VERSION}"
    (cd "${REPO_ROOT}" && git add "docs/releases/${RELEASE_VERSION}.md") 2>/dev/null || true

    # 5. CHANGELOG.md — prepend a new section for this release (#580).
    phase "Regenerating CHANGELOG.md section for ${RELEASE_VERSION}..."
    log ""
    regenerate_changelog "${RELEASE_VERSION}"
    (cd "${REPO_ROOT}" && git add CHANGELOG.md) 2>/dev/null || true

    # 6. Version-ref audit across docs + build configs (#581 / #582).
    # Informational only — surfaces strings that look like versions so
    # the operator can manually review before --apply.
    phase "Auditing docs + build configs for version refs..."
    audit_version_refs

    # 7. Verification builds. Two passes so each catches a different class
    # of failure before --apply locks the release in:
    #   (a) ./build_modules.sh all
    #       Builds every component from its current/ tree. Proves the
    #       in-development source compiles before we freeze it. Catches
    #       broken AIDL in current/ that snapshot creation copied as-is.
    #   (b) ./build_modules.sh manifest
    #       Reads versions_released.yaml (which the script just rewrote)
    #       and builds every component at its newly-pinned snapshot
    #       version. Proves the freshly-cut <comp>/<version>/ snapshots
    #       are reachable, intact, and produce valid build artefacts —
    #       i.e. the manifest update and the snapshots agree.
    # Either failure aborts the release before the branch/tag is created.
    # After all per-module writes land (single `stage <m>` or `stage all`),
    # run the manifest verification build — compiles every component at
    # its versions_released.yaml pin, so the operator sees IMMEDIATELY if
    # the staged snapshot breaks cross-component compatibility (videosink
    # 0.2.0.0 expects common 0.2.0.0 etc.). The current-cohort build is
    # deferred to --apply (it's slower and catches a different failure
    # mode — broken in-development tree, which CI also catches).
    if [[ "${NO_BUILD}" -eq 1 ]]; then
        log ""
        log "Manifest verification: SKIPPED (--no-build)"
    else
        run_verification_build \
            "released cohort via versions_released.yaml" \
            "${REPO_ROOT}/out/release-build-released.log" \
            manifest
    fi
fi

# Branch + commit + tag — runs only with --apply.
if [[ "${DO_BRANCH}" -eq 1 ]]; then
    if [[ "${changed_count}" -eq 0 ]]; then
        die "--apply requested but nothing is staged for release. Use ./release.sh stage <module> first."
    fi
    # Manifest verification: re-run only if writes didn't happen this
    # invocation (operator ran --apply cold on a pre-staged worktree).
    # When writes happened, stage already ran it at the end. The current
    # cohort verification is intentionally NOT re-run here — if `stage`
    # succeeded, every per-module build_modules.sh <comp> compile passed
    # AND the manifest build at end-of-stage validated the released
    # cohort. A full current-cohort rebuild at --apply time catches
    # nothing new but costs minutes.
    if [[ "${NO_BUILD}" -ne 1 && "${DO_WRITES}" -ne 1 ]]; then
        run_verification_build \
            "released cohort via versions_released.yaml" \
            "${REPO_ROOT}/out/release-build-released.log" \
            manifest
    fi
    phase "Creating release branch and tag ${RELEASE_VERSION}..."
    log ""
    create_release_branch "${RELEASE_VERSION}"
fi

# Print the buffered table NOW — after all diagnostic blocks above,
# so the final-decision view is the last thing the operator reads.
log ""
for _row in "${TABLE_ROWS[@]}"; do
    log "${_row}"
done

# Count modules by Planned state for the summary line below.
_planned_count=${#ACTUAL_PLAN[@]}
_qualifying_count=0
for _comp in "${BUMPED_COMPONENTS[@]}"; do
    _qualifying_count=$((_qualifying_count + 1))
done
_total_touched=${#COMP_TOUCHED[@]}

log ""
if [[ "${DO_BRANCH}" -eq 1 ]]; then
    if [[ "${COMMIT}" -eq 1 ]]; then
        log "Release ${RELEASE_VERSION} applied: ${_planned_count} module(s) — branch + commit + push complete."
        log "Tag will be created on main by: git flow release finish ${RELEASE_VERSION}"
    else
        log "Release ${RELEASE_VERSION} staged on branch: ${_planned_count} module(s) — release artefacts in the index, no commit yet."
        log "Review with \`git diff --cached\`, then: ./release.sh --commit"
    fi
elif [[ "${CHECK_MODE}" -eq 1 ]]; then
    log "Stage modules with: ./release.sh <module>     Apply with: ./release.sh --apply --release-version ${RELEASE_VERSION}"
elif [[ "${_planned_count}" -eq 0 ]]; then
    log "Plan: 0 / ${_qualifying_count} qualifying module(s) staged (of ${_total_touched} touched)."
    log "Stage with: ./release.sh stage <module>   or   ./release.sh stage all"
else
    log "Plan: ${_planned_count} / ${_qualifying_count} qualifying module(s) staged (of ${_total_touched} touched)."
    if [[ "${error_count}" -gt 0 ]]; then
        log "⚠️  ${error_count} module(s) need manual action above before applying."
    fi
    log "Apply: ./release.sh --apply --release-version ${RELEASE_VERSION}    |    Reset: ./release.sh clean"
fi

if [[ "${error_count}" -gt 0 ]]; then
    log "Completed with ${error_count} item(s) requiring manual action."
    exit 2
fi

log "Release scan completed successfully."
