#!/usr/bin/env bash
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2025 RDK Management
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
# release.sh - snapshot a component's current/ into a versioned release.
#
# A "release" is a plain copy: <module>/current/ -> <module>/<version>/, where
# <version> is read verbatim from the component's metadata.yaml `version:`
# field. The release directory is a controlled, immutable snapshot - it carries
# a .hash of its AIDL for integrity. Generation is NOT re-run; the release is a
# faithful copy of current/ at release time.
#
# Usage:
#   ./release.sh                 Release every component not yet released.
#   ./release.sh <component> ... Release the named component(s).
#   ./release.sh --help
#
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$(realpath "${BASH_SOURCE[0]}")")" && pwd)"
cd "${REPO_ROOT}"

if [ "${1:-}" = "--help" ] || [ "${1:-}" = "-h" ]; then
    sed -n '23,33p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
    exit 0
fi

# Resolve the component list: explicit args, or every component with an
# interface definition under <module>/current/.
if [ "$#" -gt 0 ]; then
    COMPONENTS=("$@")
else
    COMPONENTS=()
    for f in */current/interface.yaml; do
        COMPONENTS+=("${f%/current/interface.yaml}")
    done
fi

released=0
skipped=0
for component in "${COMPONENTS[@]}"; do
    current="${component}/current"
    metadata="${component}/metadata.yaml"

    if [ ! -d "${current}" ]; then
        echo "  SKIP ${component}: no current/ directory"
        skipped=$((skipped + 1)); continue
    fi
    if [ ! -f "${metadata}" ]; then
        echo "  SKIP ${component}: no metadata.yaml"
        skipped=$((skipped + 1)); continue
    fi

    version="$(grep -E '^version:' "${metadata}" | head -1 | awk '{print $2}')"
    if [ -z "${version}" ]; then
        echo "  SKIP ${component}: no version: in metadata.yaml"
        skipped=$((skipped + 1)); continue
    fi

    target="${component}/${version}"
    if [ -d "${target}" ]; then
        echo "  SKIP ${component}: already released at ${version}"
        skipped=$((skipped + 1)); continue
    fi

    # Snapshot current/ -> <version>/ (a plain copy, no regeneration).
    cp -r "${current}" "${target}"

    # Parse imports: from interface.yaml so the snapshot CMakeLists can link
    # against the right dependency libraries. Handles both inline (`[a, b]`)
    # and block (`- a\n  - b`) YAML list forms.
    deps=""
    if [ -f "${target}/interface.yaml" ]; then
        deps="$(awk '
            /^[[:space:]]*imports:[[:space:]]*\[/ {
                line=$0; gsub(/.*\[|\].*/,"",line); gsub(/,/," ",line)
                print line; exit
            }
            /^[[:space:]]*imports:/ { inmap=1; next }
            inmap && /^[[:space:]]+-[[:space:]]*/ {
                gsub(/^[[:space:]]+-[[:space:]]*/,""); printf "%s ", $0; next
            }
            inmap && /^[^[:space:]-]/ { exit }
        ' "${target}/interface.yaml" | xargs)"
    fi
    dep_libs=""
    dep_inc_lines=""
    for d in ${deps}; do
        dep_libs+=" ${d}-vcurrent-cpp"
        dep_inc_lines+="
    \"\${HALIF_INCLUDE_DIR}/${d}/current/include\""
    done
    # Only emit the dependency-include block when the component has imports;
    # an empty target_include_directories() call is invalid-looking noise.
    dep_include_block=""
    if [ -n "${dep_inc_lines}" ]; then
        dep_include_block="

# Dependency component headers (staged by the current/ build into HALIF_INCLUDE_DIR).
if (DEFINED HALIF_INCLUDE_DIR)
    target_include_directories(\${LIB_NAME} PRIVATE${dep_inc_lines})
endif()"
    fi

    # Write the snapshot's CMakeLists.txt as a standalone, direct-compile
    # build. A released snapshot is frozen pre-generated code - the toolchain
    # is not involved; we just compile what's committed in src/ and include/
    # into lib<component>-v<version>-cpp.so.
    cat > "${target}/CMakeLists.txt" << SNAPSHOT_CMAKE_EOF
# Auto-written by release.sh - do not hand-edit.
#
# Standalone direct-compile build for the released ${component} snapshot
# (version ${version}). The committed C++ in src/ and include/ is compiled
# into lib${component}-v${version}-cpp.so. No code generation, no toolchain
# dependency - the snapshot is frozen pre-generated code.
#
# Inputs (set by the caller, typically build_modules.sh --version ${version}):
#   BINDER_SDK_DIR  - linux_binder SDK root (lib/binder + include/binder_sdk)
#   HALIF_LIB_DIR   - directory holding dependency lib<dep>-vcurrent-cpp.so
cmake_minimum_required(VERSION 3.8)
project(${component}-v${version}-cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIB_NAME "${component}-v${version}-cpp")

if (NOT DEFINED BINDER_SDK_DIR)
    message(FATAL_ERROR "BINDER_SDK_DIR must be set for snapshot build")
endif()

# Resolve binder include path. Yocto stages a flat SDK so headers live under
# \${BINDER_SDK_DIR}/include/binder_sdk. The local dev layout splits headers
# (out/build/include/binder_sdk) from runtime libs (out/target/lib/binder),
# so allow BINDER_SDK_INCLUDE_DIR to point at the headers root.
set(_BINDER_INC "\${BINDER_SDK_DIR}/include/binder_sdk")
if (NOT IS_DIRECTORY "\${_BINDER_INC}")
    if (DEFINED BINDER_SDK_INCLUDE_DIR AND
        IS_DIRECTORY "\${BINDER_SDK_INCLUDE_DIR}/include/binder_sdk")
        set(_BINDER_INC "\${BINDER_SDK_INCLUDE_DIR}/include/binder_sdk")
    else()
        message(FATAL_ERROR
            "Binder SDK headers not found at \${_BINDER_INC}. "
            "Set BINDER_SDK_INCLUDE_DIR to the headers root.")
    endif()
endif()

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "\${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
if (NOT SRCS)
    message(FATAL_ERROR "No sources under src/. The snapshot must carry committed generated C++.")
endif()

add_library(\${LIB_NAME} SHARED \${SRCS})

target_include_directories(\${LIB_NAME} PRIVATE
    "\${CMAKE_CURRENT_SOURCE_DIR}/include"
    "\${_BINDER_INC}"
)${dep_include_block}

target_link_directories(\${LIB_NAME} PRIVATE
    "\${BINDER_SDK_DIR}/lib/binder"
)
if (DEFINED HALIF_LIB_DIR)
    target_link_directories(\${LIB_NAME} PRIVATE "\${HALIF_LIB_DIR}")
endif()

target_link_libraries(\${LIB_NAME} PRIVATE binder utils${dep_libs})

set_target_properties(\${LIB_NAME} PROPERTIES OUTPUT_NAME "\${LIB_NAME}")

include(GNUInstallDirs)
install(TARGETS \${LIB_NAME}
    LIBRARY DESTINATION lib/halif
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                        GROUP_READ GROUP_EXECUTE
                        WORLD_READ WORLD_EXECUTE)
SNAPSHOT_CMAKE_EOF

    # Freeze the interface version in the copied documentation. Each component
    # doc carries an "Interface Version" row in its References section; in
    # current/ it reads `current`, and the Interface Definition link points at
    # <component>/current. A release pins both to the released <version>.
    if [ -d "${target}/docs" ]; then
        while IFS= read -r -d '' doc; do
            sed -i \
                -e "s/|\*\*Interface Version\*\*|\`current\`|/|**Interface Version**|\`${version}\`|/" \
                -e "s#${component}/current#${component}/${version}#g" \
                "${doc}"
        done < <(find "${target}/docs" -name '*.md' -type f -print0)
    fi

    # Integrity hash of the released AIDL contract - a controlled release is
    # not to be edited; the .hash makes any change tamper-evident.
    find "${target}" -name '*.aidl' -type f | LC_ALL=C sort \
        | xargs cat 2>/dev/null | sha256sum | awk '{print $1}' > "${target}/.hash"

    echo "  released ${component} -> ${target} (.hash $(cut -c1-12 < "${target}/.hash")...)"
    released=$((released + 1))
done

echo ""
echo "release.sh: ${released} released, ${skipped} skipped."
