#!/usr/bin/env bash
# Format AIDL files under the directories listed below using the .clang-format in this directory.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ASSUME_FILENAME="${SCRIPT_DIR}/dummy.java"
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
Usage: ./format_aidl.sh [--all | <component|dir> ...]

Formats AIDL files with clang-format, using the .clang-format in this directory.

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
    if [[ -d "${SCRIPT_DIR}/${arg}/current" ]]; then
        echo "${SCRIPT_DIR}/${arg}/current"
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
            TARGET_DIRS+=("${SCRIPT_DIR}/${mydir}/current")
        done
        ;;
    "")
        for mydir in ${FORMAT_DIRS[@]+"${FORMAT_DIRS[@]}"}; do
            TARGET_DIRS+=("${SCRIPT_DIR}/${mydir}/current")
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
    echo "   binary to use, for example: CLANG_FORMAT=clang-format-21 ./format_aidl.sh ..." >&2
    exit 1
fi

for dir in "${TARGET_DIRS[@]}"; do
    if [[ -d "${dir}" ]]; then
        find "${dir}" -name "*.aidl" -print0 | while IFS= read -r -d '' f; do
            "${CLANG_FORMAT}" -assume-filename="${ASSUME_FILENAME}" < "${f}" > "${f}.tmp" && mv "${f}.tmp" "${f}"
        done
    fi
done

echo "Formatted AIDL files in: ${TARGET_DIRS[*]#"${SCRIPT_DIR}/"}"
