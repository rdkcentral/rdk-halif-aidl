#!/usr/bin/env bash
# Format AIDL files using the .clang-format file in the repository root.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
ASSUME_FILENAME="${REPO_ROOT}/dummy.java"
CLANG_FORMAT="${CLANG_FORMAT:-clang-format}"

# Default: only the modules under active development, to keep diffs small.
FORMAT_DIRS=(
)

# Every component with AIDL under <component>/current. Used by --all.
ALL_DIRS=(
    "audiodecoder"
    "audiomixer"
    "audiosink"
    "avbuffer"
    "avclock"
    "bootreason"
    "broadcast"
    "common"
    "compositeinput"
    "deepsleep"
    "deviceinfo"
    "drm"
    "firmwareupdate"
    "hdmicec"
    "hdmiinput"
    "hdmioutput"
    "indicator"
    "panel"
    "planecontrol"
    "ringbuffer"
    "sensor"
    "videodecoder"
    "videosink"
)

usage() {
    cat <<EOF
Usage: ./scripts/format_aidl.sh [--all | <component|dir> ...]

Formats AIDL files with clang-format, using the repository root's .clang-format.

  (no option)      Format the default set in FORMAT_DIRS (currently: ${FORMAT_DIRS[*]:-none configured})
  --all            Format every component with AIDL (${#ALL_DIRS[@]} components)
  <component>      Format that component's current/ (e.g. audiodecoder)
  <dir>            Format that directory as given, if it is not a component name
  -h, --help       Show this message

A bare component name always resolves to <component>/current, so frozen snapshots
are not touched by accident. Pass an explicit path to format one of those.
EOF
}

# Resolve an argument to a directory: component name first, so that a bare name
# never picks up frozen snapshots; otherwise use the path as given.
resolve_dir() {
    local arg="${1%/}"
    if [[ -d "${REPO_ROOT}/${arg}/current" ]]; then
        echo "${REPO_ROOT}/${arg}/current"
    elif [[ -d "${arg}" ]]; then
        (cd "${arg}" && pwd)
    else
        return 1
    fi
}

TARGET_DIRS=()

case "${1:-}" in
    -h | --help)
        usage
        exit 0
        ;;
    --all)
        [[ $# -gt 1 ]] && {
            echo "❌ --all takes no further arguments" >&2
            exit 1
        }
        for mydir in "${ALL_DIRS[@]}"; do
            TARGET_DIRS+=("${REPO_ROOT}/${mydir}/current")
        done
        ;;
    "")
        for mydir in ${FORMAT_DIRS[@]+"${FORMAT_DIRS[@]}"}; do
            TARGET_DIRS+=("${REPO_ROOT}/${mydir}/current")
        done
        ;;
    -*)
        echo "❌ Unknown option: $1" >&2
        usage >&2
        exit 1
        ;;
    *)
        for arg in "$@"; do
            if resolved="$(resolve_dir "${arg}")"; then
                TARGET_DIRS+=("${resolved}")
            else
                echo "❌ Not a component or directory: ${arg}" >&2
                exit 1
            fi
        done
        ;;
esac

if [[ ${#TARGET_DIRS[@]} -eq 0 ]]; then
    usage
    exit 1
fi

# Checked here rather than at the top so that --help still works without it.
if ! command -v "${CLANG_FORMAT}" > /dev/null 2>&1; then
    echo "❌ '${CLANG_FORMAT}' not found on PATH." >&2
    echo "   Install it (e.g. 'sudo apt install clang-format') or point CLANG_FORMAT at the" >&2
    echo "   binary to use, for example: CLANG_FORMAT=clang-format-21 ./scripts/format_aidl.sh ..." >&2
    exit 1
fi

format_failed=0
for dir in "${TARGET_DIRS[@]}"; do
    if [[ -d "${dir}" ]]; then
        while IFS= read -r -d '' f; do
            if ! "${CLANG_FORMAT}" -assume-filename="${ASSUME_FILENAME}" < "${f}" > "${f}.tmp"; then
                rm -f "${f}.tmp"
                echo "❌ Failed to format ${f}" >&2
                format_failed=1
                continue
            fi
            if ! mv "${f}.tmp" "${f}"; then
                rm -f "${f}.tmp"
                echo "❌ Failed to replace ${f}" >&2
                format_failed=1
            fi
        done < <(find "${dir}" -name "*.aidl" -print0)
    fi
done

if [[ ${format_failed} -ne 0 ]]; then
    exit 1
fi

echo "Formatted AIDL files in: ${TARGET_DIRS[*]#"${REPO_ROOT}/"}"
