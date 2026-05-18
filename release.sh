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

    # Pin the version in the copied module CMakeLists.txt.
    if [ -f "${target}/CMakeLists.txt" ]; then
        sed -i "s/set(INTERFACE_VERSION current)/set(INTERFACE_VERSION ${version})/" \
            "${target}/CMakeLists.txt"
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
