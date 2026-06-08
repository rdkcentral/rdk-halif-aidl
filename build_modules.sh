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

# Production build script for HAL modules
#
# This script compiles HAL libraries from pre-generated C++ code.
# It does NOT run AIDL generation - code must already exist in stable/generated/
#
# Usage:
#   ./build_modules.sh [module|command] [options]
#
# Examples:
#   ./build_modules.sh all              # Build all modules
#   ./build_modules.sh boot             # Build boot module only
#   ./build_modules.sh all --clean      # Clean build
#   ./build_modules.sh clean            # Remove out/ directory
#   ./build_modules.sh --help           # Show help

# Show help if no arguments or help requested
if [[ $# -eq 0 ]] || [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]] || [[ "${1:-}" == "--h" ]]; then
    cat << 'EOF'
Usage: ./build_modules.sh [module|command] [options]

Build HAL module libraries from pre-generated C++ code (Stage 3 only).

Arguments:
  module     Module to build (default: all)
             - "all"  : Build all modules
             - <name> : Build specific module (e.g., boot, videodecoder)

Commands:
  manifest   Build the component set from versions_released.yaml (each at
             its pinned version). Use --file <path> for an alternate manifest
             (e.g. versions_current.yaml for the in-development cohort).
  clean      Remove out/ directory (build artifacts)
  cleanall   Remove out/ and build/ directories

Options:
  --clean            Clean build directory before building
  --version <ver>    Version to build (default: current)
  --sdk-dir <path>   Binder SDK location (default: out/target)
  --build-dir <path> CMake build directory (default: build/current)
  --jobs <N>         Number of parallel build jobs (default: nproc)
  --help, -h         Show this help message

Description:
  This script performs Stage 3 of the build process:
  - Compiles pre-generated C++ from stable/generated/
  - Links against Binder SDK (must exist from Stage 1 or Yocto)
  - Outputs libraries to out/target/lib/halif/
  - Outputs headers to out/build/include/

  ⚠️  This is a Stage 3 (compilation only) script.
  For full workflow, use ./build_interfaces.sh <module>

Prerequisites:
  1. Binder SDK must exist:
     - Development: Run ./build_interfaces.sh <module> (stages SDK)
     - Production: Provided by Yocto's linux-binder recipe

  2. Generated C++ must exist in stable/generated/
     - Development: Run ./build_interfaces.sh <module> (generates code)
     - Production: Pre-generated code is committed to repo

Build Configuration:
  Use environment variables to control compiler and flags:

    # Standard build (uses system defaults)
    ./build_modules.sh all

    # Custom compiler
    CC=gcc CXX=g++ ./build_modules.sh all

    # With custom flags
    CC=gcc CFLAGS="-O2 -g" CXXFLAGS="-O2 -g" ./build_modules.sh all

    # Cross-compilation (Yocto pattern)
    CC=arm-linux-gnueabihf-gcc \
    CXX=arm-linux-gnueabihf-g++ \
    CFLAGS="-march=armv7-a" \
    CXXFLAGS="-march=armv7-a" \
    LDFLAGS="-Wl,--hash-style=gnu" \
    ./build_modules.sh all --sdk-dir /opt/sysroot/usr

  Supported variables: CC, CXX, CFLAGS, CXXFLAGS, LDFLAGS

Examples:
  # Basic usage
  ./build_modules.sh all                              # Build all modules
  ./build_modules.sh boot                             # Build boot only
  ./build_modules.sh boot --version current           # Explicit version
  ./build_modules.sh boot --version v1                # Build frozen version

  # Clean builds
  ./build_modules.sh clean                            # Remove out/ directory
  ./build_modules.sh cleanall                         # Remove out/ and build/
  ./build_modules.sh all --clean                      # Clean before build

  # Custom SDK location (for Yocto/cross-compilation)
  ./build_modules.sh all --sdk-dir /opt/sysroot/usr

  # Parallel builds
  ./build_modules.sh all --jobs 8                     # 8 parallel jobs

  # Yocto/BitBake integration
  CC="${CC}" CXX="${CXX}" \
  CFLAGS="${CFLAGS}" CXXFLAGS="${CXXFLAGS}" LDFLAGS="${LDFLAGS}" \
  ./build_modules.sh all --sdk-dir ${STAGING_DIR}${prefix}

Output:
  Libraries: out/target/lib/halif/lib<module>-vcurrent-cpp.so
  Headers:   out/build/include/<module>/

For Development Workflow:
  To modify AIDL interfaces and regenerate C++ code, use:
    ./build_interfaces.sh <module>

EOF
    exit 0
fi

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$SCRIPT_DIR"

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

# Check for clean commands first
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
    manifest)
        # Build the component set described by the manifest, each at the
        # version the manifest pins it to. Default file is the released
        # cohort (`versions_released.yaml`); dev users override with
        # `--file versions_current.yaml` to build the in-development tree.
        MANIFEST="$ROOT_DIR/versions_released.yaml"
        if [[ "${2:-}" == "--file" && -n "${3:-}" ]]; then
            MANIFEST="$3"
        fi
        if [[ ! -f "$MANIFEST" ]]; then
            echo "❌ ERROR: version manifest not found: $MANIFEST"
            exit 1
        fi

        DEFAULT_VER="$(grep -E '^default:' "$MANIFEST" | head -1 | awk '{print $2}')"
        DEFAULT_VER="${DEFAULT_VER:-current}"

        # Read "<component> <version>" pairs from the components: map.
        mapfile -t MANIFEST_PAIRS < <(awk -v def="$DEFAULT_VER" '
            /^components:/      { inmap=1; next }
            inmap && /^[^[:space:]#]/ { inmap=0 }
            inmap && /^[[:space:]]+[A-Za-z0-9_]+:/ {
                gsub(/:/, " "); print $1, ($2 == "" ? def : $2)
            }' "$MANIFEST")

        if [[ ${#MANIFEST_PAIRS[@]} -eq 0 ]]; then
            echo "❌ ERROR: no components listed in $MANIFEST"
            exit 1
        fi

        echo "📋 Version manifest: $MANIFEST"
        echo "   ${#MANIFEST_PAIRS[@]} component(s), default version '${DEFAULT_VER}'"

        # Topologically sort MANIFEST_PAIRS so each component's
        # dependencies build (and install their headers/libs into
        # out/target) before the component itself does. Without this,
        # alphabetical iteration breaks any importer of `common`:
        # audiodecoder builds before common, can't find common's
        # PropertyValue.h etc. (#583). The dep graph comes from each
        # component's <version>/interface.yaml `imports:` list (or
        # <comp>/current/interface.yaml when version=current).
        mapfile -t MANIFEST_PAIRS < <(python3 - "$ROOT_DIR" "${MANIFEST_PAIRS[@]}" <<'PYEOF'
import os, re, sys
root = sys.argv[1]
pairs = [arg.split(None, 1) for arg in sys.argv[2:]]
version_of = {comp: ver for comp, ver in pairs}

def imports_of(comp, ver):
    """Parse <comp>/<ver>/interface.yaml `imports:` -> [dep names]."""
    iface = os.path.join(root, comp, ver, "interface.yaml")
    if not os.path.isfile(iface):
        return []
    deps = []
    in_block = False
    with open(iface) as f:
        for line in f:
            if re.match(r'^  imports:\s*$', line):
                in_block = True
                continue
            if in_block and re.match(r'^  [^ ]', line):
                break  # next top-level key
            if in_block:
                m = re.match(r'^    - ([A-Za-z0-9_]+)(?:@.*)?\s*$', line)
                if m:
                    deps.append(m.group(1))
    return deps

# Build graph + Kahn's BFS toposort.
graph = {comp: set(imports_of(comp, ver)) for comp, ver in pairs}
# Restrict edges to deps that are actually in the manifest — external
# refs (e.g. android.hardware.common.fmq) shouldn't block toposort.
for comp, deps in graph.items():
    graph[comp] = {d for d in deps if d in version_of}

indegree = {comp: 0 for comp in graph}
for comp, deps in graph.items():
    for d in deps:
        indegree[comp] += 1

# Reverse map: dep -> [importers]
importers = {comp: [] for comp in graph}
for comp, deps in graph.items():
    for d in deps:
        importers[d].append(comp)

ready = sorted(c for c, deg in indegree.items() if deg == 0)
ordered = []
while ready:
    c = ready.pop(0)
    ordered.append(c)
    for imp in sorted(importers[c]):
        indegree[imp] -= 1
        if indegree[imp] == 0:
            ready.append(imp)
    ready.sort()

if len(ordered) != len(graph):
    sys.stderr.write("toposort: cycle detected; falling back to alphabetical\n")
    ordered = sorted(graph.keys())

for c in ordered:
    print(f"{c} {version_of[c]}")
PYEOF
        )

        # Echo the resolved build order so the operator can see what's
        # being built when and why.
        echo "   build order (toposort by imports): $(awk '{print $1}' <<< "$(printf '%s\n' "${MANIFEST_PAIRS[@]}")" | tr '\n' ' ')"
        echo ""

        # Pre-stage each component's include/ tree into
        # out/build/include/<comp>/<ver>/include/ so downstream snapshot
        # builds can satisfy their `${HALIF_INCLUDE_DIR}/<dep>/<ver>/include`
        # references. The root CMakeLists copy step only handles
        # */current/include (it pre-dates module-local snapshots), so for
        # snapshot manifest builds we need this here. Pure copy, no build —
        # snapshot include/ trees are committed pre-generated C++.
        echo "   pre-staging snapshot headers into out/build/include/ ..."
        INC_STAGE="$ROOT_DIR/out/build/include"
        for pair in "${MANIFEST_PAIRS[@]}"; do
            read -r comp ver <<< "$pair"
            src_inc="$ROOT_DIR/$comp/$ver/include"
            [[ -d "$src_inc" ]] || continue
            dst_inc="$INC_STAGE/$comp/$ver/include"
            mkdir -p "$dst_inc"
            cp -RT "$src_inc" "$dst_inc"
        done
        echo ""

        # Components pinned to 'current' build together in one pass; any
        # component pinned to a released version is built individually.
        ALL_CURRENT=true
        for pair in "${MANIFEST_PAIRS[@]}"; do
            read -r _ ver <<< "$pair"
            [[ "$ver" != "current" ]] && ALL_CURRENT=false
        done

        rc=0
        if $ALL_CURRENT; then
            "$0" all || rc=$?
        else
            for pair in "${MANIFEST_PAIRS[@]}"; do
                read -r comp ver <<< "$pair"
                echo "── building ${comp} (version ${ver}) ──"
                "$0" "$comp" --version "$ver" || rc=$?
            done
        fi
        exit $rc
        ;;
esac

MODULE="${1:-all}"
VERSION="current"
SDK_DIR=""
BUILD_DIR=""
JOBS=$(nproc 2>/dev/null || echo 4)
CLEAN=false

shift 1 2>/dev/null || true

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
    BUILD_DIR="$ROOT_DIR/build/current"
fi

#######################################################################
# Validation
#######################################################################

echo "========================================="
echo "  HAL Module Build (Stage 3)"
echo "========================================="
echo "Module:     $MODULE"
echo "Version:    $VERSION"
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

# Module-local layout: each component holds its own AIDL and generates its
# own C++ into <module>/current/{include,src}. The CMake configure step
# generates any missing sources, so there is no central stable/generated
# tree to pre-check here.
MODULE_COUNT=$(ls -d "$ROOT_DIR"/*/current/interface.yaml 2>/dev/null | wc -l)
echo "✓ Found $MODULE_COUNT component interface(s)"

# Validate specific module exists if not building all
if [[ "$MODULE" != "all" ]]; then
    if [[ ! -f "$ROOT_DIR/$MODULE/current/interface.yaml" ]]; then
        echo "❌ ERROR: Component '$MODULE' not found ($ROOT_DIR/$MODULE/current/interface.yaml)"
        echo ""
        echo "Available components:"
        ls -d "$ROOT_DIR"/*/current/interface.yaml 2>/dev/null \
            | sed -E 's#.*/([^/]+)/current/interface.yaml#  \1#' | sort
        echo ""
        exit 1
    fi
    echo "✓ Component '$MODULE' exists"
fi

#######################################################################
# Snapshot build (released version)
#
# A non-'current' version selects a released snapshot at <MODULE>/<VERSION>/.
# The snapshot carries committed pre-generated C++ and a standalone
# CMakeLists.txt written by release.sh - we just compile and install it.
# No toolchain involvement, no code generation.
#######################################################################

if [[ "$VERSION" != "current" ]]; then
    if [[ "$MODULE" == "all" ]]; then
        echo "❌ ERROR: --version $VERSION cannot be combined with 'all'."
        echo "   Specify a component, e.g. './build_modules.sh boot --version $VERSION'"
        echo "   or use './build_modules.sh manifest' for mixed-version builds."
        exit 1
    fi
    SNAPSHOT_DIR="$ROOT_DIR/$MODULE/$VERSION"
    if [[ ! -f "$SNAPSHOT_DIR/CMakeLists.txt" ]]; then
        echo "❌ ERROR: snapshot $MODULE/$VERSION not found at $SNAPSHOT_DIR."
        echo "   Snapshots are produced by the cohort-wide './release.sh' run;"
        echo "   verify the version number is one that has been released."
        exit 1
    fi

    SNAPSHOT_BUILD_DIR="$ROOT_DIR/build/$MODULE-$VERSION"
    if [[ "$CLEAN" == true ]]; then
        echo "🧹 Cleaning snapshot build directory: $SNAPSHOT_BUILD_DIR"
        rm -rf "$SNAPSHOT_BUILD_DIR"
    fi

    echo ""
    echo "📸 Snapshot build: $MODULE/$VERSION"
    echo "    source: $SNAPSHOT_DIR"
    echo "    build:  $SNAPSHOT_BUILD_DIR"
    echo ""

    # The local dev layout splits binder headers (out/build/include/binder_sdk)
    # from libs (out/target/lib/binder); BINDER_SDK_INCLUDE_DIR lets the
    # snapshot CMakeLists find the headers. Yocto stages a flat SDK so
    # BINDER_SDK_DIR alone resolves both.
    cmake -S "$SNAPSHOT_DIR" -B "$SNAPSHOT_BUILD_DIR" \
        -DCMAKE_CXX_FLAGS_INIT="${WARNING_SUPPRESSION_FLAGS}" \
        -DBINDER_SDK_DIR="$SDK_DIR" \
        -DBINDER_SDK_INCLUDE_DIR="$ROOT_DIR/out/build" \
        -DHALIF_LIB_DIR="$ROOT_DIR/out/target/lib/halif" \
        -DHALIF_INCLUDE_DIR="$ROOT_DIR/out/build/include" \
        -DCMAKE_INSTALL_PREFIX="$ROOT_DIR/out/target" || {
            echo "❌ Snapshot CMake configuration failed"; exit 1; }

    cmake --build "$SNAPSHOT_BUILD_DIR" -j"$JOBS" || {
        echo "❌ Snapshot build failed"; exit 1; }

    cmake --install "$SNAPSHOT_BUILD_DIR" >/dev/null || {
        echo "❌ Snapshot install failed"; exit 1; }

    SO_PATH="$ROOT_DIR/out/target/lib/halif/lib${MODULE}-v${VERSION}-cpp.so"
    if [[ -f "$SO_PATH" ]]; then
        echo "✅ Snapshot built and installed:"
        echo "    $SO_PATH"
    else
        echo "❌ Snapshot library not found at $SO_PATH"; exit 1
    fi
    exit 0
fi

echo ""

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

echo "⚙️  Configuring CMake..."
echo ""

cmake -S "$ROOT_DIR" -B "$BUILD_DIR" \
    -DCMAKE_CXX_FLAGS_INIT="${WARNING_SUPPRESSION_FLAGS}" \
    -DINTERFACE_TARGET="$MODULE" \
    -DAIDL_SRC_VERSION="$VERSION" \
    -DBINDER_SDK_DIR="$SDK_DIR"

if [[ $? -ne 0 ]]; then
    echo ""
    echo "❌ CMake configuration failed"
    exit 1
fi

echo ""
echo "✓ CMake configuration complete"
echo ""

#######################################################################
# Build
#######################################################################

echo "🔨 Building HAL modules..."
echo ""

cmake --build "$BUILD_DIR" -j"$JOBS"

if [[ $? -ne 0 ]]; then
    echo ""
    echo "❌ Build failed"
    exit 1
fi

echo ""
echo "✓ Build complete"
echo ""

#######################################################################
# Summary
#######################################################################

OUT_DIR="$ROOT_DIR/out/target"
LIB_DIR="$OUT_DIR/lib/halif"
INC_DIR="$ROOT_DIR/out/build/include"

echo "========================================="
echo "  Build Summary"
echo "========================================="
echo ""

# Count built libraries
if [[ -d "$LIB_DIR" ]]; then
    LIB_COUNT=$(find "$LIB_DIR" -name "*.so" 2>/dev/null | wc -l)
    echo "Libraries: $LIB_COUNT built"
    echo "  Location: $LIB_DIR"
    echo ""
    if [[ $LIB_COUNT -gt 0 ]] && [[ $LIB_COUNT -le 10 ]]; then
        echo "  Built libraries:"
        find "$LIB_DIR" -name "*.so" -exec basename {} \; | sort | sed 's/^/    - /'
        echo ""
    fi
fi

# Count staged headers
if [[ -d "$INC_DIR" ]]; then
    HEADER_COUNT=$(find "$INC_DIR" -name "*.h" 2>/dev/null | wc -l)
    echo "Headers: $HEADER_COUNT staged"
    echo "  Location: $INC_DIR"
    echo ""
fi

echo "========================================="
echo "✅ Build completed successfully!"
echo "========================================="
echo ""

exit 0
