#!/usr/bin/env bash

#/**
# * Copyright 2024 Comcast Cable Communications Management, LLC
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

# Helper script to update AIDL APIs and build interface libraries.
# 
# This script:
#   1. Runs aidl_ops -u to copy {module}/current/*.aidl → stable/aidl/{module}/current/
#   2. Generates C++ code → stable/generated/{module}/current/
#   3. Builds libraries from generated code
#
# Usage:
#   ./build_interfaces.sh [module]
#       module: "all" (default) or specific module name (e.g., "boot", "videodecoder")
#
# Examples:
#   ./build_interfaces.sh              # Update API and build all modules
#   ./build_interfaces.sh all          # Update API and build all modules
#   ./build_interfaces.sh videodecoder # Update API and build only videodecoder

set -euo pipefail

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SCRIPT_PATH="$SCRIPT_DIR/$(basename "${BASH_SOURCE[0]}")"

# Show help if no arguments or help requested
if [[ $# -eq 0 ]] || [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]]; then
    cat << EOF
Usage: ./build_interfaces.sh <module|command> [--version <ver>]

Build AIDL interface libraries or clean build artifacts.

Arguments:
  module     Module to build (required)
             - "all"  : Build all modules
             - <name> : Build specific module (e.g., boot, videodecoder)

Commands:
  clean       Remove out/ directory (build outputs)
  cleanstable Remove stable/ directory (generated code and AIDL copies)
  cleanall    Remove out/, stable/, and build-tools/ directories
  test        Build sample modules (boot, common, flash) and verify outputs
  test-all    Comprehensive test: build each module individually and validate

Options:
  --version <ver>    Version to build (default: current)
                     - "current" : Working development version
                     - "v1"      : Frozen version 1
                     - "v2"      : Frozen version 2, etc.

  --help, -h         Show this help message

Description:
  This script performs a complete build:
  1. Updates AIDL APIs (copies module/current → stable/<module>/<version>/)
  2. Generates C++ code → stable/generated/<module>/<version>/
  3. Builds shared libraries (.so) and headers (.h)
  4. Outputs everything to out/ directory ready for deployment

Build Configuration:
  Use CC/CXX environment variables to control compiler and flags:
    CC=gcc CXX=g++ ./build_interfaces.sh <module>              # Release (default)
    CC="gcc -g" CXX="g++ -g" ./build_interfaces.sh <module>   # Debug build
    CC=arm-linux-gnueabihf-gcc ./build_interfaces.sh <module>  # Cross-compile

Examples:
  # Building
  ./build_interfaces.sh all                    # Build all modules
  ./build_interfaces.sh boot                   # Build boot module
  ./build_interfaces.sh boot --version current # Explicit version
  ./build_interfaces.sh videodecoder --version v1  # Build frozen v1
  
  # Cleaning
  ./build_interfaces.sh clean                  # Remove build outputs (out/)
  ./build_interfaces.sh cleanstable            # Remove generated code (stable/)
  ./build_interfaces.sh cleanall               # Remove all artifacts
  
  # Testing
  ./build_interfaces.sh test                   # Quick SDK validation
  ./build_interfaces.sh test-all               # Test all modules individually

Output Structure:
  stable/
    aidl/<module>/<version>/            # Copied AIDL definitions
    generated/<module>/<version>/       # Generated C++ code
    dependencies.txt                    # Module dependency graph
  out/target/
    lib/
      binder/                           # Binder runtime libraries (*.so)
      halif/                            # HAL interface libraries (*.so)
    include/
      binder_sdk/                       # Binder headers (for compilation)
      halif/                            # HAL interface headers
    .sdk_ready                          # SDK marker file

Workflow:
  1. Edit:   vim <module>/current/com/rdk/hal/<module>/*.aidl
  2. Build:  ./build_interfaces.sh all
  3. Test:   ./build_interfaces.sh test
  4. Deploy: scp -r out/target/* device:/usr/
  5. Freeze: ./freeze_interface.sh <module>

EOF
    exit 0
fi

# Handle clean commands
case "${1:-}" in
    clean)
        echo "🧹 Cleaning build outputs..."
        rm -rf out/
        echo "✅ Removed out/ directory"
        exit 0
        ;;
    cleanstable)
        echo "🧹 Cleaning generated code and AIDL copies..."
        rm -rf stable/
        echo "✅ Removed stable/ directory"
        exit 0
        ;;
    cleanall)
        echo "🧹 Cleaning all build artifacts..."
        rm -rf out/ stable/ build-tools/
        echo "✅ Removed out/, stable/, and build-tools/ directories"
        exit 0
        ;;
    test)
        echo "🧪 Testing interface builds..."
        echo "=========================================="
        echo ""
        
        # Clean previous build
        echo "Cleaning previous build..."
        rm -rf stable/ build/current
        
        echo "Building all interfaces..."
        if "$SCRIPT_PATH" all > /tmp/test_build_all.log 2>&1; then
            echo ""
            echo "Verifying build outputs..."
            
            # Check if libraries were built
            LIB_COUNT=$(find out/target/lib/halif -name "*.so" 2>/dev/null | wc -l || echo 0)
            LIB_COUNT=$(echo "$LIB_COUNT" | tr -d ' ')
            
            if [ "${LIB_COUNT:-0}" -gt 0 ]; then
                echo "  ✅ HAL libraries: $LIB_COUNT files"
            else
                echo "  ❌ No HAL libraries built"
                echo "  Last 20 lines of build log:"
                tail -20 /tmp/test_build_all.log | sed 's/^/     /'
                exit 1
            fi
            
            # Check if headers were generated
            HDR_COUNT=$(find out/target/include/halif -name "*.h" 2>/dev/null | wc -l || echo 0)
            HDR_COUNT=$(echo "$HDR_COUNT" | tr -d ' ')
            
            if [ "${HDR_COUNT:-0}" -gt 0 ]; then
                echo "  ✅ HAL headers: $HDR_COUNT files"
            else
                echo "  ❌ No HAL headers generated"
                exit 1
            fi
            
            # Check generated C++ code structure
            GEN_CPP=$(find stable/generated -name "*.cpp" 2>/dev/null | wc -l || echo 0)
            GEN_CPP=$(echo "$GEN_CPP" | tr -d ' ')
            
            if [ "${GEN_CPP:-0}" -gt 0 ]; then
                echo "  ✅ Generated C++ files: $GEN_CPP files"
            else
                echo "  ❌ No C++ code generated"
                exit 1
            fi
            
            echo ""
            echo "✅ Interface build test passed"
            exit 0
        else
            echo ""
            echo "❌ Build failed"
            echo "Last 30 lines of build log:"
            tail -30 /tmp/test_build_all.log | sed 's/^/   /'
            exit 1
        fi
        ;;
    test-all)
        echo "🧪 Running comprehensive build tests..."
        echo "=========================================="
        echo ""
        
        # List of all modules in dependency order
        MODULES=(
            common flash deepsleep indicator boot
            videodecoder audiodecoder hdmicec hdmiinput
            videosink audiosink hdmioutput deviceinfo
            planecontrol panel avbuffer avclock
        )
        
        FAILED_MODULES=()
        
        for module in "${MODULES[@]}"; do
            echo "----------------------------------------"
            echo "Testing: $module"
            echo "----------------------------------------"
            
            # Remove stable directory for clean test
            rm -rf stable/
            
            # Build the module
            if "$SCRIPT_PATH" "$module" > /tmp/build_$module.log 2>&1; then
                # Check stable directory structure
                AIDL_DIR=$(ls -d stable/aidl 2>/dev/null | wc -l)
                GEN_DIR=$(ls -d stable/generated 2>/dev/null | wc -l)
                DEPS_FILE=$(ls stable/dependencies.txt 2>/dev/null | wc -l)
                HIDDEN_API=$(ls -d stable/.api_temp 2>/dev/null | wc -l)
                
                AIDL_MODULES=$(ls stable/aidl/ 2>/dev/null | wc -l)
                GEN_MODULES=$(ls stable/generated/ 2>/dev/null | wc -l)
                
                if [ "$AIDL_DIR" -eq 1 ] && [ "$GEN_DIR" -eq 1 ] && [ "$DEPS_FILE" -eq 1 ] && [ "$HIDDEN_API" -eq 1 ]; then
                    echo "  ✅ Build: SUCCESS"
                    echo "  ✅ Structure: Clean (aidl/, generated/, dependencies.txt, .api_temp/)"
                    echo "  ✅ Modules in stable/aidl/: $AIDL_MODULES"
                    echo "  ✅ Modules in stable/generated/: $GEN_MODULES"
                    
                    # Check for unexpected directories
                    UNEXPECTED=$(ls stable/ 2>/dev/null | grep -v "^aidl$" | grep -v "^generated$" | grep -v "^dependencies.txt$" | wc -l)
                    if [ "$UNEXPECTED" -gt 0 ]; then
                        echo "  ⚠️  Warning: Unexpected items in stable/:"
                        ls stable/ | grep -v "^aidl$" | grep -v "^generated$" | grep -v "^dependencies.txt$"
                        FAILED_MODULES+=("$module (unexpected dirs)")
                    fi
                else
                    echo "  ❌ Structure: FAILED"
                    echo "     aidl/: $AIDL_DIR (expected 1)"
                    echo "     generated/: $GEN_DIR (expected 1)"
                    echo "     dependencies.txt: $DEPS_FILE (expected 1)"
                    echo "     .api_temp/: $HIDDEN_API (expected 1)"
                    FAILED_MODULES+=("$module")
                fi
            else
                echo "  ❌ Build: FAILED"
                echo "  Last 10 lines of build log:"
                tail -10 /tmp/build_$module.log | sed 's/^/     /'
                FAILED_MODULES+=("$module")
            fi
            echo ""
        done
        
        echo "=========================================="
        echo "  Summary"
        echo "=========================================="
        if [ ${#FAILED_MODULES[@]} -eq 0 ]; then
            echo "✅ All ${#MODULES[@]} modules passed!"
        else
            echo "❌ ${#FAILED_MODULES[@]} module(s) failed:"
            for module in "${FAILED_MODULES[@]}"; do
                echo "   - $module"
            done
            exit 1
        fi
        exit 0
        ;;
esac

# Ensure binder toolchain is installed and PATH is set
if [ -f "./install_binder.sh" ]; then
    source ./install_binder.sh
    if [ $? -ne 0 ]; then
        echo "❌ Critical Error: Failed to setup Binder Toolchain."
        exit 1
    fi
else
    echo "❌ Error: install_binder.sh not found in root."
    exit 1
fi

# Parse arguments
MODULE="${1:-all}"
VERSION="current"

shift || true  # Remove first argument
while [[ $# -gt 0 ]]; do
    case "$1" in
        --version)
            VERSION="$2"
            shift 2
            ;;
        *)
            echo "❌ Unknown option: $1"
            echo "Run './build_interfaces.sh --help' for usage."
            exit 1
            ;;
    esac
done

ROOT_DIR=$(pwd)
STABLE_DIR="${ROOT_DIR}/stable"
OUT_DIR="${ROOT_DIR}/out"              # Final output: headers + libs for deployment
BUILD_DIR="${ROOT_DIR}/build/${VERSION}"  # CMake build directory
SDK_INCLUDE_DIR="${BUILD_DIR}/sdk/include"
SDK_LIB_DIR="${BUILD_DIR}/sdk/lib"

# Use BINDER_TOOLCHAIN_ROOT exported by install_binder.sh
BINDER_ROOT="${BINDER_TOOLCHAIN_ROOT:-${ROOT_DIR}/build-tools/linux_binder_idl}"
AIDL_OPS="${BINDER_ROOT}/host/aidl_ops.py"

echo "=========================================="
echo "  Building AIDL Interfaces"
echo "  Module:     $MODULE"
echo "  Version:    $VERSION"
echo "  Compiler:   ${CC:-gcc} / ${CXX:-g++}"
echo "  Output:     $OUT_DIR"
echo "=========================================="

mkdir -p "$OUT_DIR"
mkdir -p "$BUILD_DIR"
mkdir -p "$SDK_INCLUDE_DIR"
mkdir -p "$SDK_LIB_DIR"

# Create Python helper script for dependency resolution
cat > /tmp/resolve_deps_$$.py << 'EOFPY'
import sys

if len(sys.argv) != 3:
    print("Usage: resolve_deps.py <module> <deps_file>")
    sys.exit(1)

target = sys.argv[1]
deps_file = sys.argv[2]

# Read dependency file
deps = {}
order = []
with open(deps_file, 'r') as f:
    for line in f:
        line = line.strip()
        if ':' in line:
            module, dependencies = line.split(':', 1)
            module = module.replace('-vcurrent-cpp', '').strip()
            order.append(module)
            dep_list = [d.replace('-vcurrent-cpp', '').strip() 
                       for d in dependencies.split() if d.strip()]
            deps[module] = dep_list

# Check if target exists
if target not in deps:
    print(target)
    sys.exit(0)

# Recursively collect all dependencies
def collect_deps(mod, collected=None):
    if collected is None:
        collected = set()
    if mod in collected:
        return collected
    if mod not in deps:
        return collected
    collected.add(mod)
    for dep in deps.get(mod, []):
        collect_deps(dep, collected)
    return collected

# Get all dependencies including the target
all_needed = collect_deps(target)

# Print in topological order (order from deps file)
result = [m for m in order if m in all_needed]
print(' '.join(result))
EOFPY

RESOLVE_DEPS_SCRIPT="/tmp/resolve_deps_$$.py"

# Stage SDK from toolchain
echo "--> [Step 1/4] Staging SDK..."
TOOLCHAIN_INSTALL_DIR="$BINDER_ROOT/out/target"
if [ -d "$TOOLCHAIN_INSTALL_DIR/include" ]; then
    cp -au "$TOOLCHAIN_INSTALL_DIR/include/." "$SDK_INCLUDE_DIR/" 2>/dev/null || true
fi
if [ -d "$TOOLCHAIN_INSTALL_DIR/lib" ]; then
    cp -au "$TOOLCHAIN_INSTALL_DIR/lib/"*.so* "$SDK_LIB_DIR/" 2>/dev/null || true
fi

# Determine which modules to process
if [ "$MODULE" == "all" ]; then
    echo "--> [Step 2/4] Calculating build order..."
    $AIDL_OPS -a -r "$ROOT_DIR" -o "$STABLE_DIR" > /dev/null
    DEPS_FILE="${STABLE_DIR}/dependencies.txt"
    if [ -f "$DEPS_FILE" ]; then
        MODULES=$(grep -- "-vcurrent-cpp:" "$DEPS_FILE" | cut -d: -f1 | sed 's/-vcurrent-cpp//')
        echo "    Build Order: [ $(echo $MODULES | tr '\n' ' ') ]"
    else
        echo "❌ Failed to generate dependency tree"
        exit 1
    fi
else
    # Building a specific module - calculate full dependency tree
    echo "--> [Step 2/4] Calculating dependencies for $MODULE..."
    $AIDL_OPS -a -r "$ROOT_DIR" -o "$STABLE_DIR" >/dev/null 2>&1
    DEPS_FILE="${STABLE_DIR}/dependencies.txt"
    
    if [ -f "$DEPS_FILE" ]; then
        # Use Python helper script to resolve transitive dependencies
        if [ ! -f "$RESOLVE_DEPS_SCRIPT" ]; then
            echo "    ERROR: Dependency resolution script not found: $RESOLVE_DEPS_SCRIPT"
            MODULES="$MODULE"
        else
            MODULES=$(python3 "$RESOLVE_DEPS_SCRIPT" "$MODULE" "$DEPS_FILE" 2>&1)
            
            if [ $? -ne 0 ]; then
                echo "    ERROR: Dependency resolution failed: $MODULES"
                MODULES="$MODULE"
            fi
        fi
        
        if [ -n "$MODULES" ]; then
            # Count dependencies (all except the target module)
            # Note: grep -v returns 1 if no matches, so we use || true to prevent exit
            DEP_LIST=$(echo "$MODULES" | tr ' ' '\n' | { grep -v "^${MODULE}$" || true; })
            if [ -n "$DEP_LIST" ]; then
                DEP_COUNT=$(echo "$DEP_LIST" | wc -l)
                DEPS=$(echo "$DEP_LIST" | tr '\n' ' ')
                echo "    Dependencies: [ $DEPS]"
            else
                DEP_COUNT=0
                echo "    No dependencies"
            fi
            echo "    Build Order: [ $MODULES ]"
        else
            echo "    Module not found in dependency tree"
            MODULES="$MODULE"
        fi
    else
        echo "    No dependency tree available"
        MODULES="$MODULE"
    fi
fi

# Update APIs for each module
echo "--> [Step 3/4] Updating APIs..."
for mod in $MODULES; do
    echo "    Updating: $mod"
    $AIDL_OPS -u -r "$ROOT_DIR" -o "$STABLE_DIR" "$mod" || exit 1
done

# Note: C++ code generation is handled by CMake via CMakeLists.inc
# which calls aidl_ops -g automatically during the build

# Sanitize generated files (mutex include fix)
if [ -d "$STABLE_DIR/generated" ]; then
    grep -rl "std::mutex" "$STABLE_DIR/generated" 2>/dev/null | while read -r file; do
        [ -f "$file" ] || continue
        if ! grep -q "#include <mutex>" "$file"; then
            if grep -q "^#include" "$file"; then
                sed -i '0,/^#include/s//#include <mutex>\n&/' "$file"
            elif grep -q "^#pragma once" "$file"; then
                sed -i 's/^#pragma once/#pragma once\n#include <mutex>/' "$file"
            else
                sed -i '1i #include <mutex>' "$file"
            fi
        fi
    done
fi

# Build with CMake
echo "--> [Step 4/4] Building libraries..."

# Check if we need to reconfigure CMake due to target change
NEEDS_RECONFIG=false
if [ -f "${BUILD_DIR}/CMakeCache.txt" ]; then
    CACHED_TARGET=$(grep "^INTERFACE_TARGET:" "${BUILD_DIR}/CMakeCache.txt" | cut -d= -f2)
    if [ "$MODULE" == "all" ] && [ -n "$CACHED_TARGET" ]; then
        NEEDS_RECONFIG=true
    elif [ "$MODULE" != "all" ] && [ "$CACHED_TARGET" != "$MODULE" ]; then
        NEEDS_RECONFIG=true
    fi
fi

if [ "$NEEDS_RECONFIG" = true ]; then
    echo "    Reconfiguring CMake (target changed)..."
    rm -rf "${BUILD_DIR}"
fi

# Pass the module name to CMake if building a specific module
if [ "$MODULE" != "all" ]; then
    MODULE_ARG="-DINTERFACE_TARGET=${MODULE}"
else
    MODULE_ARG="-DINTERFACE_TARGET=all"
fi

cmake -S"${ROOT_DIR}" -B"${BUILD_DIR}" \
    -DAIDL_SRC_VERSION="${VERSION}" \
    -DLINUX_BINDER_AIDL_ROOT="${BINDER_ROOT}" \
    -DLINUX_BINDER_AIDL_ROOT_OUT="${STABLE_DIR}" \
    -DHOST_AIDL_DIR="${BINDER_ROOT}/host" \
    -DINTERFACES_ROOT_DIRS="${ROOT_DIR}" \
    -DSDK_INCLUDE_DIR="${SDK_INCLUDE_DIR}" \
    -DSDK_LIB_DIR="${SDK_LIB_DIR}" \
    ${MODULE_ARG}

if [ $? -ne 0 ]; then
    echo "❌ CMake configuration failed"
    exit 1
fi

JOBS=$(command -v nproc >/dev/null 2>&1 && nproc || echo 4)
cmake --build "${BUILD_DIR}" -j"$JOBS"

if [ $? -eq 0 ]; then
    # Staging is handled by cmake_stage_modules.cmake during build
    echo ""
    echo "✅ Build Complete - SDK Ready for Deployment"
    echo ""
    
    # Verify deployment structure
    BINDER_LIBS=$(ls out/target/lib/binder/*.so 2>/dev/null | wc -l || echo 0)
    MODULE_LIBS=$(ls out/target/lib/halif/*.so 2>/dev/null | wc -l || echo 0)
    BINDER_HEADERS=$(find out/target/include/binder_sdk -name "*.h" 2>/dev/null | wc -l || echo 0)
    MODULE_HEADERS=$(find out/target/include/halif -name "*.h" 2>/dev/null | wc -l || echo 0)
    
    echo "   📦 out/target/ SDK contents:"
    echo "      • Binder libraries: ${BINDER_LIBS} files"
    echo "      • Binder headers: ${BINDER_HEADERS} files"
    echo "      • HAL libraries: ${MODULE_LIBS} files"
    echo "      • HAL headers: ${MODULE_HEADERS} files"
    echo ""
    echo "   📂 Deploy to target:"
    echo "      scp -r out/target/* device:/usr/"
    echo ""
else
    echo "❌ Build failed"
    exit 1
fi

