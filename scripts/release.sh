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

RELEASE_PLAN_FILE="${REPO_ROOT}/release_plan.yaml"

# Logging helpers — defined here so the plan subcommands below can call them.
log()   { echo "$*"; }
phase() { echo "==> $*" >&2; }
warn()  { echo "WARN: $*" >&2; }
die()   { echo "ERROR: $*" >&2; exit 1; }

# ----------------------------------------------------------------------------
# Release plan helpers (#578)
# ----------------------------------------------------------------------------
#
# release_plan.yaml is the source of truth for "what gets released this
# cycle". The detector + bumper run ONLY against the components listed
# in the plan — auto-detection of all-changes is intentionally not the
# default, because the operator decides per-component whether a change
# in current/ is release-worthy this cycle.
#
# Subcommands:
#   ./release.sh module <module> [--version X.Y.Z.W]     stage module
#   ./release.sh drop   <module>                         unstage module
#   ./release.sh plan                                    show current plan
#   ./release.sh check  [<module>]                       preview detected changes
#   ./release.sh clean  (alias: reset)                   full reset — revert
#                                                        all release artefacts,
#                                                        remove untracked snapshot
#                                                        dirs, and wipe the plan

plan_init_if_missing() {
    if [[ ! -f "${RELEASE_PLAN_FILE}" ]]; then
        cat > "${RELEASE_PLAN_FILE}" <<'EOF'
# release_plan.yaml — components flagged for the next release.
#
# Manage via:
#   ./release.sh module <module> [--version X.Y.Z.W]     stage (auto-bump if --version omitted)
#   ./release.sh drop   <module>                         unstage
#   ./release.sh plan                                    show
#   ./release.sh check  [<module>]                       preview detected changes
#   ./release.sh clean | reset                           full reset after --apply or to abort
#
# Each entry under `components:` is `<name>: <version-or-tilde>`.
# Use `~` (null) to let the detector pick the bump level from PR labels
# and the changes touching <module>/current/ since the last release tag.
# Use an explicit version (e.g. `0.3.0.0`) to override the auto-bump.

release_version: ~
components: {}
EOF
    fi
}

plan_show() {
    plan_init_if_missing
    cat "${RELEASE_PLAN_FILE}"
}

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

    # 2. Untracked snapshot directories — <comp>/<X.Y.Z[.W]>/ that
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

    # 4. Wipe the release plan.
    rm -f "${RELEASE_PLAN_FILE}"
    plan_init_if_missing
    log "  Cleared release_plan.yaml"

    log "✓ Release state reset. Worktree is back to the pre-release-attempt state."
}

plan_add() {
    local comp="$1"
    local pin="${2:-}"  # explicit version or empty for auto

    [[ -n "${comp}" ]] || die "module: missing <module> argument. Usage: ./release.sh module <module> [--version X.Y.Z.W]"
    [[ -f "${REPO_ROOT}/${comp}/metadata.yaml" ]] \
        || die "release: ${comp}/metadata.yaml not found — no such component."

    plan_init_if_missing
    python3 - "${RELEASE_PLAN_FILE}" "${comp}" "${pin}" <<'PYEOF' || die "plan: failed to update release_plan.yaml"
import re, sys
path, comp, pin = sys.argv[1:4]
value = pin if pin else "~"
with open(path) as f:
    lines = f.readlines()

# Find `components:` line.
comp_idx = None
for i, line in enumerate(lines):
    if re.match(r'^components:\s*(\{\s*\}\s*)?$', line):
        comp_idx = i
        break
if comp_idx is None:
    sys.stderr.write("release_plan.yaml: missing 'components:' block\n")
    sys.exit(1)

# Normalize: replace `components: {}` with `components:` + child block
if re.match(r'^components:\s*\{\s*\}\s*$', lines[comp_idx]):
    lines[comp_idx] = "components:\n"

# Find end of components block (next top-level key or EOF).
end = len(lines)
for i in range(comp_idx + 1, len(lines)):
    if lines[i].strip() == "":
        continue
    if not (lines[i].startswith("  ") or lines[i].startswith("\t")):
        end = i
        break

# Existing entry? rewrite.
entry_re = re.compile(r'^(\s+)([A-Za-z][\w/]*):\s*(\S+)\s*$')
for i in range(comp_idx + 1, end):
    m = entry_re.match(lines[i])
    if m and m.group(2) == comp:
        lines[i] = f"{m.group(1)}{comp}: {value}\n"
        with open(path, "w") as f:
            f.writelines(lines)
        sys.exit(0)

# Otherwise insert alphabetically.
indent = "  "
insert_at = end
for i in range(comp_idx + 1, end):
    m = entry_re.match(lines[i])
    if m:
        indent = m.group(1)
        if m.group(2) > comp:
            insert_at = i
            break
lines[insert_at:insert_at] = [f"{indent}{comp}: {value}\n"]
with open(path, "w") as f:
    f.writelines(lines)
PYEOF
    if [[ -n "${pin}" ]]; then
        log "✓ ${comp} flagged for release at explicit version ${pin}."
    else
        log "✓ ${comp} flagged for release (next version will be auto-computed from PR labels)."
    fi
}

plan_remove() {
    local comp="$1"
    [[ -n "${comp}" ]] || die "drop: missing <module> argument."
    [[ -f "${RELEASE_PLAN_FILE}" ]] || { log "No plan file — nothing to remove."; return 0; }
    python3 - "${RELEASE_PLAN_FILE}" "${comp}" <<'PYEOF' || die "plan: failed to update release_plan.yaml"
import re, sys
path, comp = sys.argv[1:3]
with open(path) as f:
    lines = f.readlines()
out = []
removed = False
entry_re = re.compile(r'^\s+([A-Za-z][\w/]*):\s*(\S+)\s*$')
for line in lines:
    m = entry_re.match(line)
    if m and m.group(1) == comp:
        removed = True
        continue
    out.append(line)
with open(path, "w") as f:
    f.writelines(out)
sys.exit(0 if removed else 0)
PYEOF
    log "✓ ${comp} removed from release plan."
}

# Parse release_plan.yaml into bash arrays for the main pipeline.
# Populates: PLAN_COMPONENTS (assoc: comp -> "" or explicit version),
#            PLAN_RELEASE_VERSION (top-level release_version: or empty).
declare -A PLAN_COMPONENTS=()
PLAN_RELEASE_VERSION=""
plan_load() {
    [[ -f "${RELEASE_PLAN_FILE}" ]] || return 0
    while IFS=$'\t' read -r key value; do
        case "${key}" in
            release_version) PLAN_RELEASE_VERSION="${value}" ;;
            *)               PLAN_COMPONENTS[$key]="${value}" ;;
        esac
    done < <(python3 - "${RELEASE_PLAN_FILE}" <<'PYEOF'
import re, sys
with open(sys.argv[1]) as f:
    lines = f.readlines()
in_components = False
for line in lines:
    if re.match(r'^release_version:\s*(\S+)\s*$', line):
        v = line.split(":", 1)[1].strip()
        if v and v != "~":
            print(f"release_version\t{v}")
        continue
    if re.match(r'^components:\s*$', line):
        in_components = True
        continue
    if in_components and re.match(r'^[^ \t#]', line):
        in_components = False
    if in_components:
        m = re.match(r'^\s+([A-Za-z][\w/]*):\s*(\S+)\s*$', line)
        if m:
            comp, ver = m.group(1), m.group(2)
            print(f"{comp}\t{'' if ver == '~' else ver}")
PYEOF
    )
}

# Subcommand dispatch — must run BEFORE the standard arg parser sees
# anything. The subcommands edit the plan file and exit; they don't
# trigger a release run.
case "${1:-}" in
    module)
        shift
        _add_comp="${1:-}"
        _add_ver=""
        shift || true
        while [[ $# -gt 0 ]]; do
            case "$1" in
                --version) [[ $# -ge 2 ]] || die "--version requires a value"
                           _add_ver="$2"; shift 2 ;;
                *) die "module: unknown option $1" ;;
            esac
        done
        plan_add "${_add_comp}" "${_add_ver}"
        exit 0
        ;;
    drop)
        shift
        plan_remove "${1:-}"
        exit 0
        ;;
    plan)
        plan_show
        exit 0
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
  Subcommands: module | drop | plan | check | clean | reset
  Or a known module name (e.g. ./release.sh bootreason)."
            fi
            STAGE_AND_WRITE_MODULES+=("${_m}")
            shift
        done
        # Mark intent for the main pipeline: stage each module via plan_add
        # AND run writes for them (DO_WRITES=1). No branch (DO_BRANCH=0).
        for _m in "${STAGE_AND_WRITE_MODULES[@]}"; do
            plan_add "${_m}" ""
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
DRY_RUN="${DRY_RUN:-0}"
SINCE_REF="${SINCE_REF:-}"
NO_GH="${NO_GH:-0}"
VERBOSE=0

usage() {
    cat <<'EOF'
Release Version Bump Tool

Subcommands (manage release_plan.yaml — what's queued for the next release):
  ./release.sh module <module> [--version X.Y.Z.W]     stage module (auto-bump unless --version pinned)
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

  Only components listed in release_plan.yaml are processed. The detector
  computes the bump level from PR labels since the base ref; an explicit
  --version pin from the plan overrides that.

Modes:
  default       PLAN view (read-only). Reads release_plan.yaml, runs the
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
 13. git commit
 14. git tag <release>

No-op when no component changed:
  If no metadata.yaml moves, the script writes nothing, creates no
  snapshot, leaves mkdocs.yml unchanged, and does not create a release
  branch or tag. Exit clean.

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
#   DO_BRANCH   1 -> create release branch + tag + commit (once per release)
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
# The release runs over components LISTED IN release_plan.yaml — not over
# every component the detector found changes in. This is deliberate: the
# operator decides per-component whether a change is release-worthy this
# cycle. Use `./release.sh module <module>` to stage a component, and
# `./release.sh plan` to view what's queued.

plan_load
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
    # actually requiring a release_plan.yaml file.
    PLAN_COMPONENTS=()
    for comp in "${!COMP_TOUCHED[@]}"; do
        PLAN_COMPONENTS[$comp]=""
    done
elif [[ ${#PLAN_COMPONENTS[@]} -eq 0 ]]; then
    # No plan and no explicit subcommand — auto-fall back to a check view
    # showing ALL detected changes. The operator can then stage what
    # they want via `./release.sh module <name>`. Only an --apply attempt
    # against an empty plan is a hard error.
    if [[ "${DO_BRANCH}" -eq 1 ]]; then
        log ""
        log "❌ --apply requested but release_plan.yaml is empty — nothing to release."
        log ""
        log "  Stage modules first:"
        log "    ./release.sh module <module>"
        log "  Then apply:"
        log "    ./release.sh --apply --release-version ${RELEASE_VERSION}"
        exit 1
    fi
    log ""
    log "ℹ️  release_plan.yaml is empty — showing CHECK view (all detected changes)."
    log "    Stage with: ./release.sh module <module>"
    log ""
    CHECK_MODE=1
    PLAN_COMPONENTS=()
    for comp in "${!COMP_TOUCHED[@]}"; do
        PLAN_COMPONENTS[$comp]=""
    done
fi

# Apply the gate: drop any TOUCHED component not in the plan, and inject
# planned components even if the detector didn't see direct changes
# (operator may have other reasons — re-cut, version pin, etc.).
phase "Applying release plan (${#PLAN_COMPONENTS[@]} component(s) staged)..."
declare -A KEEP=()
PLAN_EXTRA=()       # in plan but no detected change
PLAN_DROPPED=()     # touched but not in plan
for comp in "${!PLAN_COMPONENTS[@]}"; do
    KEEP[$comp]=1
    if [[ -z "${COMP_TOUCHED[$comp]:-}" ]]; then
        # In plan but no detected change — operator wants it released anyway
        # (re-cut, explicit version pin, etc.). Mark as touched with a "manual"
        # reason so the bump code processes it.
        COMP_TOUCHED[$comp]=1
        COMP_NON_DOC[$comp]=1  # default minor unless --version overrides
        COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}plan: manually staged via ./release.sh module ${comp}"$'\n'
        PLAN_EXTRA+=("${comp}")
    fi
done
for comp in "${!COMP_TOUCHED[@]}"; do
    if [[ -z "${KEEP[$comp]:-}" ]]; then
        unset 'COMP_TOUCHED[$comp]' \
              'COMP_BREAKING[$comp]' 'COMP_NON_DOC[$comp]' 'COMP_DOC[$comp]'
        PLAN_DROPPED+=("${comp}")
    fi
done

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

    # Refresh existing snapshot dir rather than refusing. The release flow
    # is iterative — operators run, review, fix, re-run — and the snapshot
    # is just a copy of regenerated current/ bindings, so a stale dir from
    # a prior partial run is safe to wipe and remake.
    if [[ -d "${snapshot_dir}" ]]; then
        log "  [${comp}] refreshing existing ${version}/ snapshot (rm -rf + re-create)"
        rm -rf "${snapshot_dir}" || {
            warn "Failed to remove existing ${comp}/${version}/ — manual cleanup needed."
            return 1
        }
    fi

    log "  [${comp}] regenerating bindings via build_modules.sh..."
    local build_log="${REPO_ROOT}/out/release-snapshot-${comp//\//_}.log"
    mkdir -p "$(dirname "${build_log}")"
    if [[ "${VERBOSE}" -eq 1 ]]; then
        if ! (cd "${REPO_ROOT}" && ./build_modules.sh "${comp}" 2>&1 | tee "${build_log}"); then
            warn "Failed to regenerate ${comp} bindings — see ${build_log}."
            return 1
        fi
    else
        if ! (cd "${REPO_ROOT}" && ./build_modules.sh "${comp}" >"${build_log}" 2>&1); then
            # Surface the actual ERROR line(s) — they're the diagnostic
            # the operator needs, not the noise of the trailing "Available
            # components:" list.
            warn "Failed to regenerate ${comp} bindings (see ${build_log}):"
            grep -E '^(❌|ERROR|FAIL)' "${build_log}" | head -5 | sed 's/^/    /' >&2 \
                || tail -10 "${build_log}" | sed 's/^/    /' >&2
            return 1
        fi
    fi

    log "  [${comp}] copying current/ to ${version}/"
    if ! cp -r "${REPO_ROOT}/${comp}/current" "${snapshot_dir}"; then
        warn "cp failed for ${comp}/${version}/."
        return 1
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
# Release branch + tag (#513)
# ----------------------------------------------------------------------------

create_release_branch_and_tag() {
    local release_version="$1"
    local branch="release/${release_version}"

    if git -C "${REPO_ROOT}" rev-parse --verify "refs/tags/${release_version}" >/dev/null 2>&1; then
        die "Tag ${release_version} already exists. Refusing to overwrite."
    fi

    if git -C "${REPO_ROOT}" rev-parse --verify "refs/heads/${branch}" >/dev/null 2>&1; then
        log "Branch ${branch} already exists locally — checking it out."
        (cd "${REPO_ROOT}" && git checkout "${branch}") || die "Failed to checkout existing ${branch}"
    else
        log "Creating release branch ${branch}"
        (cd "${REPO_ROOT}" && git checkout -b "${branch}") || die "Failed to create ${branch}"
    fi

    # Stage only the explicit release artefacts — never `git add -A`,
    # which would happily stage unrelated worktree changes onto the
    # release branch. The snapshot directories were already staged by
    # create_snapshot(); we add mkdocs.yml here and the per-bumped
    # metadata.yamls (which release.sh just wrote).
    local has_staged=0
    if (cd "${REPO_ROOT}" && git diff --cached --quiet); then
        has_staged=0
    else
        has_staged=1
    fi
    if [[ "${NO_MKDOCS}" -eq 0 ]] && [[ -f "${REPO_ROOT}/mkdocs.yml" ]]; then
        (cd "${REPO_ROOT}" && git add mkdocs.yml) || \
            die "git add mkdocs.yml failed — release branch left in an inconsistent state."
    fi
    for entry in "${BUMPED_COMPONENTS[@]}"; do
        local _comp="${entry%%:*}"
        (cd "${REPO_ROOT}" && git add "${_comp}/metadata.yaml") || \
            die "git add ${_comp}/metadata.yaml failed — bumped version would not be committed."
    done
    if [[ "${has_staged}" -eq 1 ]] || ! (cd "${REPO_ROOT}" && git diff --cached --quiet); then
        log "Committing release artefacts to ${branch}"
        (cd "${REPO_ROOT}" && \
            git commit -m "chore(release): cut ${release_version} — frozen snapshots + mkdocs nav") || \
            die "Failed to commit release artefacts."
    fi

    log "Tagging ${release_version}"
    (cd "${REPO_ROOT}" && git tag -a "${release_version}" -m "Release ${release_version}") || \
        die "Failed to create tag ${release_version}"

    log "Release branch ${branch} and tag ${release_version} created."
    log "Push with: git push origin ${branch} && git push origin ${release_version}"
}

# Auto-detect next release version from the last release tag when the
# caller didn't explicitly provide --release-version. Default rule: bump
# the minor segment (0.20.0 → 0.21.0). Point releases (0.20.0 → 0.20.1)
# require --release-version.
auto_detect_release_version() {
    [[ -n "${RELEASE_VERSION}" ]] && return 0
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
[[ "${APPLY}"   -eq 1 ]] && MODE="APPLY (writes + release branch + tag)"
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
TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-10s %-8s %s" "Module" "Current" "Next" "Bump" "Planned" "Status")")
TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-10s %-8s %s" "------" "-------" "----" "----" "-------" "------")")

changed_count=0
error_count=0
BUMPED_COMPONENTS=()
declare -A METADATA_DRIFT=()  # comp -> "metadata_says|discovered_truth"

# Auto-discover the "real" current version of a component by inspecting
# which <comp>/<version>/ directories are actually tracked in git. The
# value in metadata.yaml is informational; the released snapshot tree is
# the source of truth. Picks the highest version by `sort -V`.
discover_current_version() {
    local comp="$1"
    # `|| true` swallows the non-zero exit from grep when no tracked
    # snapshot dirs exist yet (brand-new component) — we want the empty
    # output and a 0 exit code, not a pipefail-triggered abort.
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
        TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-10s %-8s %s" "${comp}" "-" "-" "-" "no" "metadata missing")")
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
        TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-10s %-8s %s" "${comp}" "-" "-" "skipped" "no" "not buildable")")
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
        current_version="0.1.0.0"
        is_initial=1
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

    # Explicit version pin from release_plan.yaml wins over auto-bump:
    #   ./release.sh module <module> --version X.Y.Z.W
    if [[ -n "${PLAN_COMPONENTS[$comp]:-}" ]]; then
        NEXT_VERSION="${PLAN_COMPONENTS[$comp]}"
        bump="pinned"
        COMP_REASONS[$comp]="${COMP_REASONS[$comp]:-}plan: explicit --version ${NEXT_VERSION}"$'\n'
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

    _planned="no"
    [[ -n "${ACTUAL_PLAN[$comp]+x}" ]] && _planned="yes"

    TABLE_ROWS+=("$(printf "%-24s %-10s %-10s %-10s %-8s %s" \
        "${comp}" "${current_version}" "${NEXT_VERSION}" \
        "$(bump_label "${bump}")" "${_planned}" "${status}")")

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

# Surface metadata.yaml drift so the operator understands why "Current"
# doesn't match what they remember setting. The release heals it
# automatically — this is informational, not a blocker.
if [[ ${#METADATA_DRIFT[@]} -gt 0 ]]; then
    log ""
    log "⚠️  metadata.yaml disagrees with the computed Next version for some modules:"
    log "    metadata.yaml is normally pre-bumped by PR authors to the next planned"
    log "    release; when it matches the detector's Next, no warning. The cases"
    log "    below differ — either a PR set the wrong version, or PR labels imply"
    log "    a different bump than was anticipated. metadata.yaml will be"
    log "    overwritten to the Next column value when the module is released."
    log ""
    for comp in $(printf '%s\n' "${!METADATA_DRIFT[@]}" | sort); do
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
    log "   13. git commit  release artefacts (snapshots + manifests + nav + notes + CHANGELOG)"
    log "   14. git tag ${RELEASE_VERSION}"
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
    run_verification_build() {
        local label="$1"          # "current cohort" / "released cohort"
        local log_file="$2"
        shift 2
        # Remaining args are the build_modules.sh args
        mkdir -p "$(dirname "${log_file}")"
        phase "Verification build (${label}): ./build_modules.sh $*"
        log ""
        log "Verification build (${label}) — output streamed to ${log_file#${REPO_ROOT}/}"
        if [[ "${VERBOSE}" -eq 1 ]]; then
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
    }

    if [[ "${NO_BUILD}" -eq 1 ]]; then
        log ""
        log "Verification builds: SKIPPED (--no-build)"
    else
        run_verification_build \
            "current cohort" \
            "${REPO_ROOT}/out/release-build-current.log" \
            all
        run_verification_build \
            "released cohort via versions_released.yaml" \
            "${REPO_ROOT}/out/release-build-released.log" \
            manifest
    fi

fi

# Branch + commit + tag — runs whenever DO_BRANCH is set, INDEPENDENTLY of
# DO_WRITES. With the new model, writes happen incrementally per-module
# (./release.sh <module>), and --apply just wraps the staged work into a
# release branch + tag. If writes haven't been done and --apply is used,
# the verification builds still fire (catching the "tried to apply with
# nothing staged" case).
if [[ "${DO_BRANCH}" -eq 1 ]]; then
    if [[ "${changed_count}" -eq 0 ]]; then
        die "--apply requested but nothing is staged for release. Use ./release.sh <module> first."
    fi
    # Verification builds: catch broken cohort before tagging. Already ran
    # if DO_WRITES was on in this invocation; otherwise run them now.
    if [[ "${DO_WRITES}" -ne 1 && "${NO_BUILD}" -ne 1 ]]; then
        run_verification_build \
            "current cohort" \
            "${REPO_ROOT}/out/release-build-current.log" \
            all
        run_verification_build \
            "released cohort via versions_released.yaml" \
            "${REPO_ROOT}/out/release-build-released.log" \
            manifest
    fi
    phase "Creating release branch and tag ${RELEASE_VERSION}..."
    log ""
    create_release_branch_and_tag "${RELEASE_VERSION}"
fi

# Print the buffered table NOW — after all diagnostic blocks above,
# so the final-decision view is the last thing the operator reads.
log ""
for _row in "${TABLE_ROWS[@]}"; do
    log "${_row}"
done

log ""
if [[ "${DO_BRANCH}" -eq 1 ]]; then
    log "Release ${RELEASE_VERSION} applied: branch + tag created."
elif [[ "${CHECK_MODE}" -eq 1 ]]; then
    log "Stage modules with: ./release.sh <module>     Apply with: ./release.sh --apply --release-version ${RELEASE_VERSION}"
elif [[ "${changed_count}" -eq 0 ]]; then
    log "Nothing staged."
else
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
