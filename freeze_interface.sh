#!/usr/bin/env bash

#/**
# * Copyright 2025 Comcast Cable Communications Management, LLC
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

#!/usr/bin/env bash

# Show help if requested
if [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]]; then
    cat << EOF
Usage: ./freeze_interface.sh <interface_name>

Freeze an interface to create a versioned release.

Arguments:
  interface_name  Name of the module to freeze (required)
                  Examples: boot, videodecoder, audiosink

Description:
  This command creates a frozen, versioned copy of the interface:
  1. Determines the next version number (v1, v2, v3, etc.)
  2. Copies stable/<module>/current/ → stable/<module>/v<next>/
  3. Generates frozen C++ code in stable/generated/<module>/v<next>/

Warning:
  Only freeze ONE interface at a time.
  Freezing creates a permanent API version that must be maintained.
  Ensure the interface is fully tested before freezing.

Examples:
  ./freeze_interface.sh boot          # Freeze boot interface
  ./freeze_interface.sh videodecoder  # Freeze videodecoder interface

Output:
  Frozen AIDL: stable/<module>/v<N>/<module>-api/
  Generated:   stable/generated/<module>/v<N>/

Workflow:
  After freezing, commit the versioned files to preserve the API.
  Continue development work on the 'current' version.

EOF
    exit 0
fi

INTERFACE_NAME="$1"

if [ -z "$INTERFACE_NAME" ]; then
    echo "Usage: ./freeze_interface.sh <interface_name>"
    echo "Run './freeze_interface.sh --help' for more information."
    exit 1
fi

ROOT_DIR=$(pwd)

# 1. PRE-FLIGHT: Ensure Toolchain is Ready
if [ -f "./build_binder.sh" ]; then
    source ./build_binder.sh
    if [ $? -ne 0 ]; then
        echo "❌ Critical Error: Failed to setup Binder Toolchain."
        exit 1
    fi
fi

# 2. Activate Venv
if [ -f "./activate_venv.sh" ]; then
    source ./activate_venv.sh
fi

# Use toolchain variable or fallback
AIDL_TOOL_ROOT="${BINDER_TOOLCHAIN_ROOT:-$ROOT_DIR/build-tools/linux_binder_idl}"
AIDL_OPS="${AIDL_TOOL_ROOT}/host/aidl_ops.py"
STABLE_DIR="${ROOT_DIR}/stable"

echo "=========================================="
echo "  RELEASE: Freezing Interface '$INTERFACE_NAME'"
echo "  This will create stable/$INTERFACE_NAME/v<next>/"
echo "=========================================="
echo ""
echo "⚠️  WARNING: Only freeze ONE interface at a time!"
echo "   Freezing creates a permanent API version."
echo "   Ensure this interface is fully tested."
echo ""
read -p "Continue freezing '$INTERFACE_NAME'? (y/N): " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "❌ Freeze cancelled."
    exit 1
fi

mkdir -p "$STABLE_DIR"

# Run freeze operation
# This will:
#  1. Determine next version number (e.g., v1, v2, etc.)
#  2. Copy stable/<module>/current → stable/<module>/v<next>
#  3. Generate stable/generated/<module>/v<next>/ with frozen C++ code
$AIDL_OPS -f -r "$ROOT_DIR" -o "$STABLE_DIR" "$INTERFACE_NAME"

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Interface Frozen Successfully."
    echo "   Frozen AIDL: stable/$INTERFACE_NAME/v<version>/$INTERFACE_NAME-api/"
    echo "   Generated:   stable/generated/$INTERFACE_NAME/v<version>/"
    echo ""
    echo "Next Steps:"
    echo "  1. Build the frozen version: ./build_interfaces.sh $INTERFACE_NAME --version v<N>"
    echo "  2. Test the frozen version thoroughly"
    echo "  3. Commit frozen files: git add stable/$INTERFACE_NAME/v<N>/ && git commit"
    echo "  4. Continue development on 'current': ./build_interfaces.sh $INTERFACE_NAME"
else
    echo "❌ Freeze Failed."
    exit 1
fi
