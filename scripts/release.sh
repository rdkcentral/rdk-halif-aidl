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

APPLY=0
SINCE_REF=""
NO_GH=0
VERBOSE=0

usage() {
    cat <<'EOF'
Release Version Bump Tool

Usage:
  ./scripts/release.sh [--since <ref>] [--apply] [--release-version X.Y.Z]
                       [--no-gh] [--no-snapshot] [--no-mkdocs] [--no-git]
                       [--verbose]

Options:
  --since <ref>          Base reference to diff from (default: nearest
                         reachable tag).
  --apply                Apply computed version updates to metadata.yaml,
                         create frozen <module>/<version>/ snapshots for
                         each bumped component, update mkdocs.yml,
                         create a release/X.Y.Z branch, and tag the repo
                         X.Y.Z. The --release-version flag is required
                         when --apply produces at least one component
                         bump (and ignored otherwise).
  --release-version X.Y.Z
                         Repo-level release version (e.g. "0.21.0"). The
                         release branch and tag are named from this.
                         Required with --apply when any component is
                         bumped.
  --no-gh                Disable GitHub label lookup; use local heuristics
                         only.
  --no-snapshot          With --apply, skip creating <module>/<version>/
                         frozen snapshots (regenerate-then-copy step).
                         For testing only — a real release MUST snapshot.
  --no-mkdocs            With --apply, skip updating mkdocs.yml.
  --no-git               With --apply, skip creating the release branch
                         and tag. For testing only.
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

Snapshot creation (--apply default, suppress with --no-snapshot):
  For each component whose version moved, the script:
    1. Runs ./build_modules.sh <component> so the toolchain regenerates
       current/include/*.h and current/src/*.cpp into the working tree.
       (These directories are .gitignored under current/ per #566.)
    2. Copies current/ to <component>/<NEXT_VERSION>/, capturing the
       regenerated bindings into the immutable frozen snapshot.
    3. Stages the new <version>/ directory for commit.

  Placeholder components (those with no current/ directory — e.g. ffv,
  r4ce, vsi/abstractfilesystem; tracked under #517) are skipped silently.
  The metadata.yaml bump still records the cycle; no snapshot is produced
  because there's no source to snapshot.

No-op when no component changed:
  If no metadata.yaml moves, the script writes nothing, creates no
  snapshot, leaves mkdocs.yml unchanged, and does not create a release
  branch or tag. Exit clean.

Notes:
  - Script is intended for manual release-time usage (not CI).
  - Default is dry-run; no files are modified unless --apply is set.
EOF
}

log() {
    echo "$*"
}

# phase: prominent stage header so the user can see progress through long
# silent stretches (GitHub PR/label fetch, snapshot regen, etc.). Single
# line to stderr to keep stdout clean for piping the report.
phase() {
    echo "==> $*" >&2
}

warn() {
    echo "WARN: $*" >&2
}

die() {
    echo "ERROR: $*" >&2
    exit 1
}

# Defaults for the new flags (added by #513)
RELEASE_VERSION=""
NO_SNAPSHOT=0
NO_MKDOCS=0
NO_GIT=0

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
        --no-git)
            NO_GIT=1
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

    if [[ -d "${snapshot_dir}" ]]; then
        warn "${comp}/${version}/ already exists from a prior run."
        warn "  Refusing to risk a stale snapshot: delete the directory and re-run,"
        warn "  or run with --no-snapshot if you know the existing snapshot is current."
        return 1
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
            warn "Failed to regenerate ${comp} bindings. Tail of ${build_log}:"
            tail -20 "${build_log}" | sed 's/^/    /' >&2
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

MODE="DRY-RUN"
[[ "${APPLY}" -eq 1 ]] && MODE="APPLY"

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

printf "%-28s %-12s %-12s %-10s %s\n" "Component" "Current" "Next" "Bump" "Status"
printf "%-28s %-12s %-12s %-10s %s\n" "---------" "-------" "----" "----" "------"

changed_count=0
error_count=0
BUMPED_COMPONENTS=()

mapfile -t TOUCHED_COMPONENTS < <(printf '%s\n' "${!COMP_TOUCHED[@]}" | sort)
for comp in "${TOUCHED_COMPONENTS[@]}"; do
    meta="${REPO_ROOT}/${comp}/metadata.yaml"
    if [[ ! -f "${meta}" ]]; then
        printf "%-28s %-12s %-12s %-10s %s\n" "${comp}" "-" "-" "-" "metadata missing"
        error_count=$((error_count + 1))
        continue
    fi

    current_version="$(awk -F': *' '$1=="version"{print $2; exit}' "${meta}")"

    bump="none"
    if [[ "${COMP_BREAKING[$comp]:-0}" -eq 1 ]]; then
        bump="generation"
    elif [[ "${COMP_NON_DOC[$comp]:-0}" -eq 1 ]]; then
        bump="minor"
    elif [[ "${COMP_DOC[$comp]:-0}" -eq 1 ]]; then
        bump="patch"
    fi

    compute_next_versions "${current_version}" "${bump}"

    status="ok"
    if [[ "${NEXT_NOTE}" == "breaking change on frozen interface: create new component instead" ]]; then
        status="manual action required"
        error_count=$((error_count + 1))
    elif [[ "${NEXT_NOTE}" == "unsupported version format" ]]; then
        status="unsupported version format"
        error_count=$((error_count + 1))
    fi

    printf "%-28s %-12s %-12s %-10s %s\n" "${comp}" "${current_version}" "${NEXT_VERSION}" "${bump}" "${status}"

    if [[ "${VERBOSE}" -eq 1 ]]; then
        echo "  Reasons:"
        while IFS= read -r line; do
            [[ -n "${line}" ]] && echo "    - ${line}"
        done <<< "${COMP_REASONS[$comp]:-}"
    fi

    if [[ "${current_version}" != "${NEXT_VERSION}" && "${status}" == "ok" ]]; then
        # Record this component as bumped so the snapshot / mkdocs /
        # release-tag steps (apply) and the dry-run preview block can
        # iterate them.
        BUMPED_COMPONENTS+=("${comp}:${NEXT_VERSION}")
        changed_count=$((changed_count + 1))
        if [[ "${APPLY}" -eq 1 ]]; then
            update_metadata "${meta}" "${NEXT_VERSION}"
        fi
    fi
done

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
# Dry-run preview of the apply pipeline
# ----------------------------------------------------------------------------
#
# When the user runs the script without --apply, show exactly what the
# real run will do per component. Otherwise the dry-run looks "done"
# at the table when in fact the regeneration / snapshot / mkdocs / branch
# steps haven't even been previewed.

if [[ "${APPLY}" -eq 0 && ${#BUMPED_COMPONENTS[@]} -gt 0 ]]; then
    log ""
    log "Apply pipeline preview — what --apply will do:"
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
    if [[ -n "${RELEASE_VERSION}" ]]; then
        log "  Then once per release:"
        log "    5. Insert mkdocs.yml nav entries for the ${#BUMPED_COMPONENTS[@]} new <module>/<version>/ doc sets"
        log "    6. git checkout -b release/${RELEASE_VERSION}; git commit; git tag ${RELEASE_VERSION}"
        log ""
    fi
fi

# ----------------------------------------------------------------------------
# Snapshot + mkdocs + release-branch/tag pipeline (#513)
# ----------------------------------------------------------------------------
#
# Only run with --apply AND at least one component bumped. No-op otherwise.

if [[ "${APPLY}" -eq 1 && "${changed_count}" -gt 0 ]]; then
    if [[ -x "${REPO_ROOT}/scripts/generate_rag_report.sh" ]]; then
        "${REPO_ROOT}/scripts/generate_rag_report.sh" >/dev/null || warn "Failed to regenerate RAG_STATUS_REPORT.md"
    fi

    # Require --release-version when applying with bumps AND auto-detect
    # couldn't infer one (no existing release tag). Otherwise the
    # auto-detected value is used (announced in the header).
    if [[ -z "${RELEASE_VERSION}" ]]; then
        die "--release-version is required with --apply when one or more components are bumped and no prior release tag exists to auto-detect from. Provide e.g. --release-version 0.21.0"
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
        for entry in "${BUMPED_COMPONENTS[@]}"; do
            comp="${entry%%:*}"
            version="${entry##*:}"
            if ! create_snapshot "${comp}" "${version}"; then
                snapshot_fail=$((snapshot_fail + 1))
            fi
        done
        if [[ "${snapshot_fail}" -gt 0 ]]; then
            die "${snapshot_fail} snapshot(s) failed to create. Aborting release."
        fi
    fi

    # 2. mkdocs.yml entries. A real release MUST update the nav so the
    # frozen docs are reachable from the built site. Failures are fatal
    # unless suppressed with --no-mkdocs (testing only).
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

    # 3. Release branch + tag.
    if [[ "${NO_GIT}" -eq 1 ]]; then
        log ""
        log "Release branch / tag: SKIPPED (--no-git)"
    else
        phase "Creating release branch and tag ${RELEASE_VERSION}..."
        log ""
        create_release_branch_and_tag "${RELEASE_VERSION}"
    fi
fi

log ""
if [[ "${APPLY}" -eq 1 ]]; then
    log "Applied updates to ${changed_count} component metadata file(s)."
    if [[ "${changed_count}" -eq 0 ]]; then
        log "No components changed — no release branch, no tag, no doc edits."
    fi
else
    log "Would update ${changed_count} component metadata file(s)."
    if [[ "${error_count}" -gt 0 ]]; then
        log ""
        log "⚠️  ${error_count} component(s) need manual action above before applying."
        log "    Resolve those, then re-run as below."
    fi
    if [[ "${changed_count}" -gt 0 ]] || [[ -n "${RELEASE_VERSION}" ]]; then
        log ""
        log "Next step — apply for real (writes metadata.yaml, creates snapshots,"
        log "updates mkdocs.yml, creates release branch + tag):"
        if [[ -n "${RELEASE_VERSION}" ]]; then
            log ""
            log "    ./scripts/release.sh --apply --release-version ${RELEASE_VERSION}"
            if [[ "${RELEASE_VERSION_AUTO}" -eq 1 ]]; then
                log ""
                log "    (release version auto-detected; pass --release-version explicitly to override)"
            fi
        else
            log ""
            log "    ./scripts/release.sh --apply --release-version <X.Y.Z>"
        fi
    fi
fi

if [[ "${error_count}" -gt 0 ]]; then
    log "Completed with ${error_count} item(s) requiring manual action."
    exit 2
fi

log "Release scan completed successfully."
