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

# Fast AIDL check for interface authors.
#
# Answers "did I break anything?" for one or more components in a few seconds,
# without configuring CMake or rebuilding the module libraries. It runs the seven
# checks that catch almost every mistake made while editing AIDL:
#
#   1. aidl compiles      - the interface is valid AIDL at vintf stability
#   2. generated C++ compiles - catches circular includes between generated
#                           headers, which the aidl compiler itself accepts
#                           (e.g. a nested type in an interface that a
#                           parcelable reachable from that interface uses)
#   3. line length        - the 120-column limit from .clang-format; a comment
#                           line that is only a URL is exempt, as it cannot wrap
#   4. formatting         - clang-format reports no changes, and every file
#                           ends with a newline
#   5. documentation      - every declaration carries Doxygen documentation;
#                           injected comments match freshly generated C++; and
#                           checked-in generated headers need no reinjection
#                           (scripts/aidl_comment_inject.py --validate)
#   6. String annotation  - every String carries @utf8InCpp, so the C++ backend
#                           generates std::string rather than String16
#   7. Comment structure  - block comments do not contain nested openers
#
# Generation happens in out/aidlcheck/ (gitignored) and nothing in the component
# tree is touched, so this is safe to run on a dirty working tree. For the real
# build, which regenerates <component>/current/{include,src}/ and links the
# libraries, use ./build_interfaces.sh instead.
#
# Usage:
#     ./scripts/validate_aidl.sh [component ...]
#
#     component   Component name, e.g. broadcast (resolves to broadcast/current).
#                 Imports declared in interface.yaml are staged automatically,
#                 so `./scripts/validate_aidl.sh broadcast` also pulls in ringbuffer.
#                 Defaults to every component with a current/interface.yaml.
#
# Environment:
#     CXX            Compiler for the generated C++ check (default: g++)
#     CLANG_FORMAT   Formatter to check against (default: clang-format)
#     JOBS           Translation units to compile at once (default: nproc)
#     SKIP_CXX=1     Skip the generated C++ check (much faster; use when
#                    iterating on wording rather than on types)
#     SKIP_DOCS=1    Skip the documentation check
#
# Returns:
#     0 - All checks passed
#     1 - A check failed
#     2 - Prerequisite missing (Binder SDK not staged, etc.)

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# The components, the staged toolchain and the build outputs are all one level
# up, in the repository this script lives under.
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
cd "${REPO_ROOT}"

AIDL_BIN="${REPO_ROOT}/build/binder/aidl"
WORK_DIR="${REPO_ROOT}/out/aidlcheck"
CXX="${CXX:-g++}"
CLANG_FORMAT="${CLANG_FORMAT:-clang-format}"
COLUMN_LIMIT=120
JOBS="${JOBS:-$(nproc 2> /dev/null || getconf _NPROCESSORS_ONLN 2> /dev/null || echo 4)}"

# clang-format is configured for Java (see .clang-format); AIDL is close enough
# that the repo formats it that way, so the check has to claim the same.
ASSUME_FILENAME="X.java"

usage() {
    sed -n '21,67p' "${BASH_SOURCE[0]}" | sed 's/^# \?//'
}

case "${1:-}" in
    -h | --help)
        usage
        exit 0
        ;;
esac

if [[ ! -x "${AIDL_BIN}" ]]; then
    echo "❌ aidl compiler not found at ${AIDL_BIN}" >&2
    echo "   Stage the Binder SDK first: ./build_binder.sh" >&2
    exit 2
fi

# Header root for the generated C++ check. Mirrors the candidate order used by
# the per-component CMakeLists, so this agrees with the real build.
BINDER_INC=""
for cand in \
    "${REPO_ROOT}/out/build/include/binder_sdk" \
    "${REPO_ROOT}/out/target/include/binder_sdk" \
    "${REPO_ROOT}/out/build/include" \
    "${REPO_ROOT}/out/target/include"; do
    if [[ -d "${cand}" ]]; then
        BINDER_INC="${cand}"
        break
    fi
done

if [[ -z "${BINDER_INC}" && -z "${SKIP_CXX:-}" ]]; then
    echo "❌ Binder SDK headers not found under out/" >&2
    echo "   Stage them with ./build_binder.sh, or re-run with SKIP_CXX=1" >&2
    exit 2
fi

# Components to check: the ones named, or every component holding AIDL.
declare -a COMPONENTS=()
if [[ $# -gt 0 ]]; then
    COMPONENTS=("$@")
else
    while IFS= read -r yaml; do
        COMPONENTS+=("$(basename "$(dirname "$(dirname "${yaml}")")")")
    done < <(find . -mindepth 3 -maxdepth 3 -path './*/current/interface.yaml' | sort)
fi

# Stage a component's AIDL and, transitively, that of everything it imports.
# Imports are the `- <name>@<version>` entries in interface.yaml; only current/
# is ever staged, which is what this script is for.
declare -a STAGED=()
stage_component() {
    local component="$1"
    local dir="${REPO_ROOT}/${component}/current"

    for done_component in "${STAGED[@]+"${STAGED[@]}"}"; do
        [[ "${done_component}" == "${component}" ]] && return 0
    done

    if [[ ! -d "${dir}/com" ]]; then
        echo "❌ ${component}: no AIDL found at ${component}/current/com" >&2
        return 1
    fi
    STAGED+=("${component}")

    mkdir -p "${WORK_DIR}/src"
    cp -r "${dir}/com" "${WORK_DIR}/src/"

    if [[ -f "${dir}/interface.yaml" ]]; then
        local import
        while IFS= read -r import; do
            stage_component "${import}"
        done < <(grep -oE '^[[:space:]]*-[[:space:]]*[A-Za-z0-9_]+@[^[:space:]]+' "${dir}/interface.yaml" |
            sed -E 's/^[[:space:]]*-[[:space:]]*//; s/@.*$//')
    fi
}

rm -rf "${WORK_DIR}"
mkdir -p "${WORK_DIR}"/{src,gen,inc}

for component in "${COMPONENTS[@]}"; do
    stage_component "${component}"
done

echo "Checking: ${COMPONENTS[*]}"
if [[ ${#STAGED[@]} -gt ${#COMPONENTS[@]} ]]; then
    echo "Staged with imports: ${STAGED[*]}"
fi

# The files belonging to the components asked for, i.e. the ones the hygiene
# checks apply to. Imports are staged so they can be compiled against, but a
# formatting complaint about another component is not this run's business.
declare -a OWN_FILES=()
while IFS= read -r f; do
    OWN_FILES+=("${f}")
done < <(for component in "${COMPONENTS[@]}"; do
    find "${REPO_ROOT}/${component}/current/com" -name '*.aidl'
done | sort)

FAILED=0
fail() {
    echo "❌ $*" >&2
    FAILED=1
}

# ---------------------------------------------------------------------------
# 1. AIDL compiles
# ---------------------------------------------------------------------------
declare -a ALL_FILES=()
while IFS= read -r f; do
    ALL_FILES+=("${f}")
done < <(find "${WORK_DIR}/src" -name '*.aidl' | sort)

if "${AIDL_BIN}" --lang=cpp --min_sdk_version=33 --structured --stability=vintf \
    -I "${WORK_DIR}/src" -o "${WORK_DIR}/gen" -h "${WORK_DIR}/inc" "${ALL_FILES[@]}"; then
    echo "✅ aidl: ${#ALL_FILES[@]} files compiled"
else
    fail "aidl: compilation failed"
    exit 1 # nothing downstream can run
fi

# ---------------------------------------------------------------------------
# 2. Generated C++ compiles
# ---------------------------------------------------------------------------
if [[ -n "${SKIP_CXX:-}" ]]; then
    echo "⏭️  generated C++: skipped (SKIP_CXX set)"
else
    declare -a GEN_SRCS=()
    while IFS= read -r f; do
        GEN_SRCS+=("${f}")
    done < <(find "${WORK_DIR}/gen" -name '*.cpp' | sort)

    # By far the slowest part of this script - a cohort component is around a
    # minute of compiling in one go, with nothing on screen. One process per
    # translation unit fixes both halves of that: the units are independent, so
    # they run ${JOBS} at a time, and each one that finishes moves a counter.
    #
    # Each child writes its diagnostics to a log, renames it to .failed on
    # error, and prints a line for the loop below to count. Reported through a
    # process substitution so the counting loop runs in this shell.
    #
    # -w because the vendored SDK headers emit clang-only attribute warnings
    # under gcc; this check is about the generated code, not about them.
    CXX_LOG_DIR="${WORK_DIR}/cxx"
    mkdir -p "${CXX_LOG_DIR}"
    export CXX CXX_LOG_DIR
    export CXX_INCLUDES="-I ${WORK_DIR}/inc -I ${BINDER_INC}"

    echo "   generated C++: compiling ${#GEN_SRCS[@]} translation units (${JOBS} jobs) ..."
    compiled=0
    while IFS= read -r _; do
        compiled=$((compiled + 1))
        [[ -t 1 ]] && printf '\r   generated C++: %d/%d' "${compiled}" "${#GEN_SRCS[@]}"
    done < <(printf '%s\n' "${GEN_SRCS[@]}" | xargs -P "${JOBS}" -I{} sh -c '
        log="${CXX_LOG_DIR}/$(basename "$1").log"
        if ${CXX} -fsyntax-only -std=c++17 -w ${CXX_INCLUDES} "$1" > "${log}" 2>&1; then
            echo ok
        else
            mv "${log}" "${log}.failed"
            echo failed
        fi' _ {})
    # Drop the counter, so the verdict lands on a line of its own.
    [[ -t 1 ]] && printf '\r%-60s\r' ''

    declare -a FAILED_TUS=()
    while IFS= read -r log; do
        FAILED_TUS+=("${log}")
    done < <(find "${CXX_LOG_DIR}" -name '*.failed' | sort)

    if [[ ${#FAILED_TUS[@]} -eq 0 ]]; then
        echo "✅ generated C++: ${#GEN_SRCS[@]} translation units compiled"
    else
        fail "generated C++: ${#FAILED_TUS[@]} of ${#GEN_SRCS[@]} translation units failed" \
            "(circular include between generated headers?)"
        for log in "${FAILED_TUS[@]}"; do
            echo "--- $(basename "${log}" .log.failed)" >&2
            cat "${log}" >&2
        done
    fi
fi

# ---------------------------------------------------------------------------
# 3. Line length
# ---------------------------------------------------------------------------
# A comment line holding nothing but a URL cannot be wrapped, so it is exempt.
LONG_LINES="$(awk -v limit="${COLUMN_LIMIT}" '
    length > limit && $0 !~ /^[[:space:]]*(\/\*\*?|\*|\/\/[\/!]?)?[[:space:]]*https?:\/\/[^[:space:]]+[[:space:]]*$/ {
        print FILENAME":"FNR" ("length" cols)"
    }' "${OWN_FILES[@]}" || true)"
if [[ -z "${LONG_LINES}" ]]; then
    echo "✅ line length: no line exceeds ${COLUMN_LIMIT} columns"
else
    fail "line length: lines over ${COLUMN_LIMIT} columns"
    echo "${LONG_LINES}" >&2
fi

# ---------------------------------------------------------------------------
# 4. Formatting and trailing newline
# ---------------------------------------------------------------------------
NO_NEWLINE=""
for f in "${OWN_FILES[@]}"; do
    [[ -n "$(tail -c 1 "${f}")" ]] && NO_NEWLINE+="${f}"$'\n'
done
if [[ -z "${NO_NEWLINE}" ]]; then
    echo "✅ trailing newline: present on every file"
else
    fail "trailing newline: missing"
    printf '%s' "${NO_NEWLINE}" >&2
fi

if ! command -v "${CLANG_FORMAT}" > /dev/null 2>&1; then
    echo "⏭️  formatting: skipped ('${CLANG_FORMAT}' not on PATH)"
else
    UNFORMATTED=""
    for f in "${OWN_FILES[@]}"; do
        if "${CLANG_FORMAT}" -assume-filename="${ASSUME_FILENAME}" < "${f}" |
            diff -q "${f}" - > /dev/null; then
            continue
        fi
        UNFORMATTED+="${f}"$'\n'
    done
    if [[ -z "${UNFORMATTED}" ]]; then
        echo "✅ formatting: clang-format clean"
    else
        fail "formatting: would be reformatted (run ./scripts/format_aidl.sh)"
        printf '%s' "${UNFORMATTED}" >&2
    fi
fi

# ---------------------------------------------------------------------------
# 5. Documentation
# ---------------------------------------------------------------------------
# The AIDL compiler strips every comment, so inject into the temporary headers
# first, then validate that injection against the generated declarations. Also
# validate the checked-in headers: --validate fails if they would change during
# injection, catching missing or stale documentation without modifying them.
DOC_CHECK="${SCRIPT_DIR}/aidl_comment_inject.py"

if [[ -n "${SKIP_DOCS:-}" ]]; then
    echo "⏭️  documentation: skipped (SKIP_DOCS set)"
elif [[ ! -f "${DOC_CHECK}" ]]; then
    echo "⏭️  documentation: skipped (${DOC_CHECK#"${REPO_ROOT}/"} not found)"
elif ! command -v python3 > /dev/null 2>&1; then
    echo "⏭️  documentation: skipped (python3 not on PATH)"
else
    DOC_ERRORS=""
    for component in "${COMPONENTS[@]}"; do
        aidl_dir="${REPO_ROOT}/${component}/current"
        generated_include="${WORK_DIR}/inc"
        current_include="${aidl_dir}/include"

        if ! output="$(python3 "${DOC_CHECK}" \
            --repo-root "${REPO_ROOT}" \
            --aidl-dir "${aidl_dir}" \
            --include-dir "${generated_include}" 2>&1)"; then
            DOC_ERRORS+="${output}"$'\n'
        fi

        if ! output="$(python3 "${DOC_CHECK}" --validate \
            --repo-root "${REPO_ROOT}" \
            --aidl-dir "${aidl_dir}" \
            --include-dir "${generated_include}" 2>&1)"; then
            DOC_ERRORS+="${output}"$'\n'
        fi

        if [[ ! -d "${current_include}" ]]; then
            DOC_ERRORS+="❌ Generated headers not found: ${current_include}"$'\n'
        elif ! output="$(python3 "${DOC_CHECK}" --validate \
            --repo-root "${REPO_ROOT}" \
            --aidl-dir "${aidl_dir}" \
            --include-dir "${current_include}" 2>&1)"; then
            DOC_ERRORS+="${output}"$'\n'
        fi
    done
    if [[ -z "${DOC_ERRORS}" ]]; then
        echo "✅ documentation: complete, injected, and current headers are up to date"
    else
        fail "documentation: incomplete, inconsistent, or stale generated headers"
        printf '%s' "${DOC_ERRORS}" >&2
    fi
fi

# ---------------------------------------------------------------------------
# 6. String annotation
# ---------------------------------------------------------------------------
# Only the C++ backend is generated here, and there an unannotated String is
# android::String16 (UTF-16) while @utf8InCpp String is std::string (UTF-8).
# Mixing the two across one interface means every caller converts, so the repo
# requires the annotation everywhere - see HAL.AIDL.83.
#
# Comments and string literals are stripped first: the word "String" appears in
# plenty of prose, and a literal may legitimately contain it.
STRING_FINDINGS="$(awk '
    FNR == 1 { incomment = 0; carry = 0 }
    {
        line = $0
        sub(/\/\/.*/, "", line)                       # line comment
        if (incomment) {                              # inside /* ... */
            idx = index(line, "*/")
            if (idx == 0) next
            line = substr(line, idx + 2)
            incomment = 0
        }
        while ((idx = index(line, "/*")) > 0) {       # block comment on this line
            pre = substr(line, 1, idx - 1)
            rest = substr(line, idx + 2)
            jdx = index(rest, "*/")
            if (jdx > 0) { line = pre substr(rest, jdx + 2) }
            else { line = pre; incomment = 1; break }
        }
        gsub(/"[^"]*"/, "\"\"", line)                 # string literals

        trimmed = line
        sub(/^[[:space:]]+/, "", trimmed)
        sub(/[[:space:]]+$/, "", trimmed)
        if (trimmed == "") next

        if (trimmed ~ /(^|[^A-Za-z0-9_])String([^A-Za-z0-9_]|$)/ &&
            trimmed !~ /@utf8InCpp/ && !carry) {
            printf "%s:%d: %s\n", FILENAME, FNR, trimmed
        }

        # An annotation on its own line applies to the declaration below it.
        if (trimmed ~ /^@[A-Za-z]/ && trimmed !~ /[;({]/) carry = (trimmed ~ /@utf8InCpp/)
        else carry = 0
    }
' "${OWN_FILES[@]}")"

if [[ -z "${STRING_FINDINGS}" ]]; then
    echo "✅ String annotation: every String is @utf8InCpp"
else
    fail "String annotation: String without @utf8InCpp (generates String16, not std::string)"
    printf '%s\n' "${STRING_FINDINGS}" >&2
fi

# ---------------------------------------------------------------------------
# 7. Block-comment structure
# ---------------------------------------------------------------------------
# A nested block-comment opener can swallow or misparse Doxygen documentation.
# Ignore comment-like text in strings and line comments.
COMMENT_FINDINGS="$(awk '
    FNR == 1 { in_block = 0 }
    {
        in_string = 0
        for (i = 1; i <= length($0);) {
            pair = substr($0, i, 2)
            char = substr($0, i, 1)

            if (in_block) {
                if (pair == "/*") {
                    printf "%s:%d: nested block-comment opener inside block comment\n", FILENAME, FNR
                    i += 2
                } else if (pair == "*/") {
                    in_block = 0
                    i += 2
                } else {
                    i++
                }
                continue
            }

            if (in_string) {
                if (char == "\\") i += 2
                else {
                    if (char == "\"") in_string = 0
                    i++
                }
                continue
            }

            if (pair == "//") break
            if (pair == "/*") {
                in_block = 1
                i += 2
                continue
            }
            if (char == "\"") in_string = 1
            i++
        }
    }
' "${OWN_FILES[@]}")"

if [[ -z "${COMMENT_FINDINGS}" ]]; then
    echo "✅ Comment structure: no nested block-comment openers"
else
    fail "comment structure: nested block-comment openers"
    printf '%s' "${COMMENT_FINDINGS}" >&2
fi

echo
if [[ ${FAILED} -eq 0 ]]; then
    echo "✅ All checks passed."
else
    echo "❌ One or more checks failed." >&2
fi
exit "${FAILED}"
