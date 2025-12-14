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

INTERFACE_NAME="$1"

if [ -z "$INTERFACE_NAME" ]; then
    echo "Usage: ./freeze_interface.sh <interface_name>"
    exit 1
fi

ROOT_DIR=$(pwd)

# 1. PRE-FLIGHT: Ensure Toolchain is Ready
if [ -f "./install_binder.sh" ]; then
    source ./install_binder.sh
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
AIDL_OUT_DIR="${ROOT_DIR}/build/out"

echo "=========================================="
echo "  RELEASE: Freezing Interface '$INTERFACE_NAME'"
echo "=========================================="

mkdir -p "$AIDL_OUT_DIR"

# Run freeze operation
$AIDL_OPS -f -r "$ROOT_DIR" -o "$AIDL_OUT_DIR" "$INTERFACE_NAME"

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Interface Frozen Successfully."
    echo "   Run ./dev_build.sh to verify the build."
else
    echo "❌ Freeze Failed."
    exit 1
fi
