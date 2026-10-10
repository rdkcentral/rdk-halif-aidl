#!/usr/bin/env bash

#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************

# Host build script for HAL modules.
#
# Configures the root CMake build for a selection of (component, version)
# nodes, builds it and installs it into out/target. The root build resolves
# dependencies itself, generates current/ bindings at build time and compiles
# released snapshots from their committed bindings.
#
# Usage:
#   ./build_modules.sh [module|command] [options]
#
# Examples:
#   ./build_modules.sh all              # Build all modules at current
#   ./build_modules.sh boot             # Build boot module only
#   ./build_modules.sh all --clean      # Clean build
#   ./build_modules.sh clean            # Remove out/ directory
#   ./build_modules.sh --help           # Show help

# Show help if no arguments or help requested
if [[ $# -eq 0 ]] || [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]] || [[ "${1:-}" == "--h" ]]; then
    cat << 'EOF2'
Usage: ./build_modules.sh [module|command] [options]

Build HAL module libraries with the root CMake build and install them into
out/target.

Arguments:
  module     Module to build (default: all)
             - "all"  : Build every component at current
             - <name> : Build one component, plus the dependencies it imports

Commands:
  manifest   Build the component set from versions_released.yaml (each at
             its pinned version). Use --file <path> for an alternate manifest
             (e.g. versions_current.yaml for the in-development cohort).
  clean      Remove out/ directory (build artifacts)
  cleanall   Remove out/ and build/ directories

Options:
  --clean                 Clean build directory before building
  --version <ver>         Version to build (default: current)
  --library-type <type>   SHARED (default), STATIC or BOTH, for every component
  --sdk-dir <path>        Binder SDK location (default: out/target)
  --build-dir <path>      CMake build directory (default: build/<selection>)
  --jobs <N>              Number of parallel build jobs (default: nproc)
  --help, -h              Show this help message

Description:
  - Resolves the selection and every dependency it imports, at the version
    each interface.yaml pins (CMakeModules/HalifResolve.cmake)
  - Generates current/ bindings into <module>/current/{include,src} at build
    time (needs the AIDL toolchain from ./build_binder.sh); released
    snapshots compile from their committed include/ and src/
  - Links against Binder SDK (must exist from Stage 1 or Yocto)
  - Installs libraries to out/target/lib/rdk-halif-aidl/
  - Installs headers to out/target/include/rdk-halif-aidl/<module>/<version>/
  - Installs CMake package configs and pkg-config files for each module

Prerequisites:
  1. Binder SDK must exist:
     - Development: Run ./build_interfaces.sh <module> (stages SDK)
     - Production: Provided by Yocto's linux-binder recipe

  2. For current/ modules, the AIDL toolchain must exist:
     - Development: ./build_binder.sh clones it into build-tools/

Build Configuration:
  Use environment variables to control compiler and flags:

    # Standard build (uses system defaults)
    ./build_modules.sh all

    # Custom compiler
    CC=gcc CXX=g++ ./build_modules.sh all

    # With custom flags
    CC=gcc CFLAGS="-O2 -g" CXXFLAGS="-O2 -g" ./build_modules.sh all

  Supported variables: CC, CXX, CFLAGS, CXXFLAGS, LDFLAGS

  Cross-compilation / Yocto: this wrapper is host-only and refuses to run in a
  cross/OpenEmbedded environment. Production and cross builds invoke CMake
  directly — see docs/standards/build_integration.md.

Examples:
  # Basic usage
  ./build_modules.sh all                              # Build all modules
  ./build_modules.sh boot                             # Build boot only
  ./build_modules.sh boot --version current           # Explicit version
  ./build_modules.sh boot --version 0.1.0.0           # Build a released version
  ./build_modules.sh boot --library-type STATIC       # .a instead of .so

  # Manifests
  ./build_modules.sh manifest                         # versions_released.yaml
  ./build_modules.sh manifest --file versions_current.yaml

  # Clean builds
  ./build_modules.sh clean                            # Remove out/ directory
  ./build_modules.sh cleanall                         # Remove out/ and build/
  ./build_modules.sh all --clean                      # Clean before build

  # Custom SDK location (host dev with a non-default SDK prefix)
  ./build_modules.sh all --sdk-dir /opt/sdk/usr

  # Parallel builds
  ./build_modules.sh all --jobs 8                     # 8 parallel jobs

  # Regenerate a released snapshot's committed bindings
  cmake --build build/<module>-<version> --target halif-generate

  # Yocto / cross builds do NOT use this script — invoke CMake directly.
  # See docs/standards/build_integration.md.

Output:
  Libraries: out/target/lib/rdk-halif-aidl/lib<module>-v<version>-cpp.so
  Headers:   out/target/include/rdk-halif-aidl/<module>/<version>/
  Packages:  out/target/lib/rdk-halif-aidl/cmake/, out/target/lib/rdk-halif-aidl/pkgconfig/

For Development Workflow:
  To stage the SDK and build in one step, use:
    ./build_interfaces.sh <module>

EOF2
    exit 0
fi

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$SCRIPT_DIR"

# Host-toolchain guard (#624): build / sdk operations need a native toolchain,
# and Yocto/cross builds must call CMake directly (see
# docs/standards/build_integration.md). clean/help do no toolchain work, so
# they stay usable in any environment.
case "${1:-}" in
    clean|cleanall|--help|-h|--h|"") ;;
    *) source "$SCRIPT_DIR/dev_env_guard.sh"; halif_guard_dev_host_env || exit 1 ;;
esac

# Suppress three classes of unfixable upstream noise so the verification
# build output stays readable.
#
#   -Wno-write-strings  AOSP aidl-cpp emits
#                       `static constexpr char* HASHVALUE = "notfrozen";`
#                       in every generated I*.h. Should be `const char*`
#                       — bug in build-tools/linux_binder_idl/android/aidl/
#                       generate_cpp.cpp:904. 93 occurrences across the
#                       cohort.
#
#   -Wno-attributes     binder_sdk headers (Vector.h, IBinder.h, …) carry
#                       clang-only attributes — `__attribute__((no_sanitize
#                       ("cfi")))` via UTILS_VECTOR_NO_CFI, and
#                       `[[clang::lto_visibility_public]]`. GCC accepts
#                       them syntactically but warns on every one.
#                       Vendored binder_sdk code; not ours to patch.
#
#   -Wno-return-type    aidl-cpp's parcelable-union writeToParcel/getTag
#                       dispatch generates an exhaustive switch followed
#                       by `__assert2(...); }` — but GCC doesn't see
#                       __assert2 as [[noreturn]], so it warns "control
#                       reaches end of non-void function". Should be
#                       `__builtin_unreachable()`. Bites every union
#                       (PropertyValue, DrmMetricValue, …).
#
# Plumbed two ways:
#   1. Export CXXFLAGS — picked up on first cmake configure of any
#      build dir (and by build_binder.sh if it's already exported in
#      this shell).
#   2. Inject -DCMAKE_CXX_FLAGS_INIT into every cmake invocation below —
#      defeats stale build/<dir>/CMakeCache.txt where the flags weren't
#      captured on the original configure (env-CXXFLAGS only seeds the
#      cache the FIRST time).
WARNING_SUPPRESSION_FLAGS="-Wno-write-strings -Wno-attributes -Wno-return-type"
export CXXFLAGS="${CXXFLAGS:-} ${WARNING_SUPPRESSION_FLAGS}"

#######################################################################
# Pre-flight checks (#571)
#######################################################################
#
# Surface broken-environment failures as a single actionable error line
# instead of cryptic CMake output deep in the run. Each check exits
# non-zero with a remediation hint pointing at the actual fix.
#
# Skipped for clean / cleanall / help — those should work in any state.

preflight_check() {
    # Toolchain artefacts present. Honour BINDER_TOOLCHAIN_ROOT /
    # BINDER_SOURCE_DIR / BINDER_SDK_DIR overrides used by Yocto and
    # cross-compile flows (a non-default toolchain location is a
    # legitimate state and shouldn't fail the local-tree check).
    local toolchain_root="${BINDER_TOOLCHAIN_ROOT:-${BINDER_SOURCE_DIR:-$ROOT_DIR/build-tools/linux_binder_idl}}"
    if [[ ! -f "$toolchain_root/host/aidl_ops.py" ]]; then
        echo "❌ AIDL toolchain not found at $toolchain_root/host/aidl_ops.py." >&2
        echo "   Fix: run ./build_binder.sh to bootstrap, symlink build-tools/" >&2
        echo "        from a known-good worktree, or set BINDER_TOOLCHAIN_ROOT" >&2
        echo "        (or BINDER_SOURCE_DIR) to the toolchain location." >&2
        exit 1
    fi

    # Binder SDK runtime present (Stage 1 must have completed).
    # Honour --sdk-dir <path> flag, BINDER_SDK_DIR env var, or the
    # default out/target/lib/binder location in order of preference.
    local sdk_dir="${BINDER_SDK_DIR:-}"
    # Scan args for --sdk-dir <path>
    local -a args=("$@")
    local i=0
    while [[ $i -lt ${#args[@]} ]]; do
        if [[ "${args[$i]}" == "--sdk-dir" ]] && [[ $((i+1)) -lt ${#args[@]} ]]; then
            sdk_dir="${args[$((i+1))]}/lib/binder"
            break
        fi
        i=$((i + 1))
    done
    if [[ -z "$sdk_dir" ]]; then
        sdk_dir="$ROOT_DIR/out/target/lib/binder"
    fi
    if [[ ! -d "$sdk_dir" ]]; then
        echo "❌ Binder SDK runtime not found at $sdk_dir." >&2
        echo "   Fix: run ./build_interfaces.sh <module> (stages the SDK and" >&2
        echo "        delegates here), or ./build_binder.sh to stage it directly." >&2
        echo "        For cross-compile / Yocto, set BINDER_SDK_DIR to the staged path" >&2
        echo "        or pass --sdk-dir <path>." >&2
        exit 1
    fi
}

# Snapshot-version builds (--version <released>) and toolchain-bootstrap
# commands (clean / cleanall / sdk / sdk-only / help) bypass preflight —
# they either don't touch the toolchain at all or are the very mechanism
# that stages it.
skip_preflight=0
case "${1:-}" in
    clean|cleanall|sdk|sdk-only|--help|-h|--h|"") skip_preflight=1 ;;
esac
# Also skip when caller pinned a released snapshot via --version <X>
# (where X != "current"): the snapshot's own pre-generated bindings are
# all that's needed; no toolchain regen happens.
for ((j=1; j<=$#; j++)); do
    if [[ "${!j}" == "--version" ]]; then
        next=$((j+1))
        if [[ $next -le $# ]] && [[ "${!next}" != "current" ]]; then
            skip_preflight=1
            break
        fi
    fi
done

if [[ "$skip_preflight" -eq 0 ]]; then
    preflight_check "$@"
fi


#######################################################################
# Parse Arguments
#######################################################################

case "${1:-}" in
    clean)
        echo "🧹 Cleaning out/ directory..."
        rm -rf "$ROOT_DIR/out"
        echo "✓ Removed: $ROOT_DIR/out/"
        echo ""
        echo "✅ Clean complete"
        exit 0
        ;;
    cleanall)
        echo "🧹 Cleaning out/ and build/ directories..."
        rm -rf "$ROOT_DIR/out"
        rm -rf "$ROOT_DIR/build"
        echo "✓ Removed: $ROOT_DIR/out/"
        echo "✓ Removed: $ROOT_DIR/build/"
        echo ""
        echo "✅ Clean complete"
        exit 0
        ;;
    sdk|sdk-only)
        echo "→ Redirecting: ./build_modules.sh sdk → ./build_binder.sh sdk"
        echo ""

        BUILD_BINDER_SCRIPT="$ROOT_DIR/build_binder.sh"

        if [ ! -f "$BUILD_BINDER_SCRIPT" ]; then
            echo "❌ ERROR: build_binder.sh not found at $BUILD_BINDER_SCRIPT"
            exit 1
        fi

        # Execute build_binder.sh
        exec "$BUILD_BINDER_SCRIPT" "${@:2}"
        ;;
esac

MODULE="${1:-all}"
VERSION="current"
MANIFEST=""
LIBRARY_TYPE="SHARED"
SDK_DIR=""
BUILD_DIR=""
JOBS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
CLEAN=false

shift 1 2>/dev/null || true

if [[ "$MODULE" == "manifest" ]]; then
    # Build the component set described by the manifest, each at the version
    # the manifest pins it to. Default file is the released cohort; dev users
    # pass --file versions_current.yaml to build the in-development tree.
    MANIFEST="$ROOT_DIR/versions_released.yaml"
fi

while [[ $# -gt 0 ]]; do
    case "$1" in
        --clean)
            CLEAN=true
            shift
            ;;
        --version)
            VERSION="$2"
            shift 2
            ;;
        --file)
            [[ "$MODULE" == "manifest" ]] || { echo "❌ --file applies to 'manifest' only"; exit 1; }
            MANIFEST="$2"
            shift 2
            ;;
        --library-type)
            LIBRARY_TYPE="$2"
            shift 2
            ;;
        --sdk-dir)
            SDK_DIR="$2"
            shift 2
            ;;
        --build-dir)
            BUILD_DIR="$2"
            shift 2
            ;;
        --jobs|-j)
            JOBS="$2"
            shift 2
            ;;
        *)
            echo "❌ Unknown option: $1"
            echo "Run './build_modules.sh --help' for usage"
            exit 1
            ;;
    esac
done

# Set defaults
if [[ -z "$SDK_DIR" ]]; then
    SDK_DIR="$ROOT_DIR/out/target"
fi

if [[ -z "$BUILD_DIR" ]]; then
    if [[ "$MODULE" == "manifest" ]]; then
        BUILD_DIR="$ROOT_DIR/build/manifest-$(basename "$MANIFEST" .yaml)"
    elif [[ "$MODULE" == "all" ]]; then
        BUILD_DIR="$ROOT_DIR/build/$VERSION"
    else
        BUILD_DIR="$ROOT_DIR/build/$MODULE-$VERSION"
    fi
fi

#######################################################################
# Validation
#######################################################################

echo "========================================="
echo "  HAL Module Build"
echo "========================================="
if [[ "$MODULE" == "manifest" ]]; then
echo "Manifest:   $MANIFEST"
else
echo "Module:     $MODULE"
echo "Version:    $VERSION"
fi
echo "Library:    $LIBRARY_TYPE"
echo "SDK:        $SDK_DIR"
echo "Build Dir:  $BUILD_DIR"
echo "Jobs:       $JOBS"
echo "========================================="
echo ""

# Check for Binder SDK. In local dev (SDK at the default out/target path)
# we auto-stage it via build_binder.sh so './build_modules.sh all' works
# out of the box. In Yocto the SDK is staged by the linux-binder recipe
# (DEPENDS = "linux-binder") and SDK_DIR points outside the repo, so we
# never auto-build there - that case is a recipe configuration error.
if [[ ! -f "$SDK_DIR/.sdk_ready" ]]; then
    if [[ "$SDK_DIR" == "$ROOT_DIR/out/target" && -x "$ROOT_DIR/build_binder.sh" ]]; then
        echo "ℹ️  Binder SDK not found at $SDK_DIR — staging it via build_binder.sh"
        echo "    (one-time prerequisite; subsequent builds reuse it)"
        echo ""
        if ! "$ROOT_DIR/build_binder.sh"; then
            echo ""
            echo "❌ build_binder.sh failed; cannot continue."
            exit 1
        fi
        echo ""
    fi
    if [[ ! -f "$SDK_DIR/.sdk_ready" ]]; then
        echo "❌ ERROR: Binder SDK not found at $SDK_DIR"
        echo ""
        echo "Production (Yocto): the linux-binder recipe must stage the SDK to"
        echo "                    \${BINDER_SDK_DIR}; declare DEPENDS = \"linux-binder\"."
        echo ""
        exit 1
    fi
fi

echo "✓ Binder SDK found at $SDK_DIR"

MODULE_COUNT=$(ls -d "$ROOT_DIR"/*/current/interface.yaml 2>/dev/null | wc -l)
echo "✓ Found $MODULE_COUNT component interface(s)"

# What to build: a manifest, every component at one version, or one component.
# The root build adds every dependency the selection imports.
if [[ "$MODULE" == "manifest" ]]; then
    if [[ ! -f "$MANIFEST" ]]; then
        echo "❌ ERROR: version manifest not found: $MANIFEST"
        exit 1
    fi
    VERSIONS_FILE="$MANIFEST"
    COMPONENTS=""
elif [[ "$MODULE" == "all" ]]; then
    if [[ "$VERSION" != "current" ]]; then
        echo "❌ ERROR: --version $VERSION cannot be combined with 'all'."
        echo "   Specify a component, e.g. './build_modules.sh boot --version $VERSION'"
        echo "   or use './build_modules.sh manifest' for mixed-version builds."
        exit 1
    fi
    VERSIONS_FILE=""
    COMPONENTS="$(ls -d "$ROOT_DIR"/*/current/interface.yaml \
        | sed -E 's#.*/([^/]+)/current/interface.yaml#\1:current#' | sort | paste -sd ';' -)"
else
    if [[ ! -f "$ROOT_DIR/$MODULE/current/interface.yaml" ]]; then
        echo "❌ ERROR: Component '$MODULE' not found ($ROOT_DIR/$MODULE/current/interface.yaml)"
        echo ""
        echo "Available components:"
        ls -d "$ROOT_DIR"/*/current/interface.yaml 2>/dev/null \
            | sed -E 's#.*/([^/]+)/current/interface.yaml#  \1#' | sort
        echo ""
        exit 1
    fi
    if [[ "$VERSION" != "current" && ! -f "$ROOT_DIR/$MODULE/$VERSION/interface.yaml" ]]; then
        echo "❌ ERROR: $MODULE/$VERSION is not a released snapshot."
        echo "   Snapshots are produced by the cohort-wide './release.sh' run;"
        echo "   verify the version number is one that has been released."
        exit 1
    fi
    echo "✓ Component '$MODULE' exists"
    VERSIONS_FILE=""
    COMPONENTS="$MODULE:$VERSION"
fi

#######################################################################
# Clean if requested
#######################################################################

if [[ "$CLEAN" == true ]]; then
    echo "🧹 Cleaning build directory: $BUILD_DIR"
    rm -rf "$BUILD_DIR"
    echo "✓ Clean complete"
    echo ""
fi

#######################################################################
# CMake Configure
#######################################################################

echo ""
echo "⚙️  Configuring CMake..."
echo ""

# The local dev layout splits binder headers (out/build/include/binder_sdk)
# from libs (out/target/lib/binder); Yocto stages a flat SDK, where
# BINDER_SDK_DIR alone resolves both.
TOOLCHAIN_ROOT="${BINDER_TOOLCHAIN_ROOT:-${BINDER_SOURCE_DIR:-$ROOT_DIR/build-tools/linux_binder_idl}}"
if ! cmake -S "$ROOT_DIR" -B "$BUILD_DIR" \
    -DCMAKE_CXX_FLAGS_INIT="${WARNING_SUPPRESSION_FLAGS}" \
    -DHALIF_VERSIONS_FILE="$VERSIONS_FILE" \
    -DHALIF_COMPONENTS="$COMPONENTS" \
    -DHALIF_LIBRARY_TYPE="$LIBRARY_TYPE" \
    -DBINDER_SDK_DIR="$SDK_DIR" \
    -DBINDER_SDK_INCLUDE_DIR="$ROOT_DIR/out/build" \
    -DHOST_AIDL_DIR="$TOOLCHAIN_ROOT/host" \
    -DCMAKE_INSTALL_PREFIX="$ROOT_DIR/out/target" \
    -DCMAKE_INSTALL_LIBDIR="lib/rdk-halif-aidl" \
    -DCMAKE_INSTALL_INCLUDEDIR="include"; then
    echo ""
    echo "❌ CMake configuration failed"
    exit 1
fi

echo ""
echo "✓ CMake configuration complete"
echo ""

#######################################################################
# Build and install
#######################################################################

echo "🔨 Building HAL modules..."
echo ""

if ! cmake --build "$BUILD_DIR" -j"$JOBS"; then
    echo ""
    echo "❌ Build failed"
    exit 1
fi

if ! cmake --install "$BUILD_DIR" >/dev/null; then
    echo ""
    echo "❌ Install failed"
    exit 1
fi

echo ""
echo "✓ Build complete"
echo ""

#######################################################################
# Summary
#######################################################################

OUT_DIR="$ROOT_DIR/out/target"
LIB_DIR="$OUT_DIR/lib/rdk-halif-aidl"
INC_DIR="$OUT_DIR/include/rdk-halif-aidl"

echo "========================================="
echo "  Build Summary"
echo "========================================="
echo ""
echo "Plan: $(paste -sd ',' "$BUILD_DIR/halif_plan.txt" | sed 's/,/, /g')"
echo ""

# Count built libraries
if [[ -d "$LIB_DIR" ]]; then
    LIB_COUNT=$(find "$LIB_DIR" -maxdepth 1 \( -name "*.so" -o -name "*.a" \) 2>/dev/null | wc -l)
    echo "Libraries: $LIB_COUNT installed"
    echo "  Location: $LIB_DIR"
    echo ""
    if [[ $LIB_COUNT -gt 0 ]] && [[ $LIB_COUNT -le 10 ]]; then
        echo "  Installed libraries:"
        find "$LIB_DIR" -maxdepth 1 \( -name "*.so" -o -name "*.a" \) -exec basename {} \; | sort | sed 's/^/    - /'
        echo ""
    fi
fi

# Count installed headers
if [[ -d "$INC_DIR" ]]; then
    HEADER_COUNT=$(find "$INC_DIR" -name "*.h" 2>/dev/null | wc -l)
    echo "Headers: $HEADER_COUNT installed"
    echo "  Location: $INC_DIR"
    echo ""
fi

echo "========================================="
echo "✅ Build completed successfully!"
echo "========================================="
echo ""

exit 0
