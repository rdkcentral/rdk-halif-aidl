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
# Shared environment guard for the developer / architecture-team wrapper scripts
# (build_binder.sh, build_modules.sh, build_interfaces.sh).
#
# These wrappers assume a NATIVE host toolchain. They exist for the architecture
# team to test interfaces and cut releases on a developer machine — they are NOT
# part of the production build path. Production / cross builds (Yocto/BitBake)
# MUST invoke CMake directly with the correct variables; see
# build-tools/linux_binder_idl/BUILD.md ("Production Build (CMake Direct)").
#
# Run inside a sourced OpenEmbedded cross environment, a wrapper produces broken
# or empty output: the host AIDL tool gets cross-compiled (and can't run on the
# build host), and the binder CMake auto-enables BUILD_ENV_YOCTO from OECORE_*,
# which disables every install() rule — so out/target is silently never staged.
#
# This guard fails fast with a clear pointer instead. Override (not recommended)
# with BINDER_ALLOW_CROSS_ENV=1.

# Returns non-zero (with an explanatory message) when the current environment is
# a Yocto/cross environment unsuitable for these host wrappers.
halif_guard_dev_host_env() {
    [ "${BINDER_ALLOW_CROSS_ENV:-0}" = "1" ] && return 0

    local reasons=()

    # The reliable Yocto signal: an OE shell exports these sysroots, and they are
    # exactly what the binder CMake keys BUILD_ENV_YOCTO off.
    if [ -n "${OECORE_NATIVE_SYSROOT:-}" ] || [ -n "${OECORE_TARGET_SYSROOT:-}" ]; then
        reasons+=("OpenEmbedded/Yocto environment detected (OECORE_*_SYSROOT set)")
    fi

    # A cross CC set outside an OE shell: compare target triples. (Inside an OE
    # shell PATH may already point cc at the cross compiler, so this can match
    # the host triple — the OECORE check above is what catches that case.)
    if [ -n "${CC:-}" ]; then
        local cc_machine host_machine
        cc_machine="$(${CC} -dumpmachine 2>/dev/null || true)"
        host_machine="$(cc -dumpmachine 2>/dev/null || gcc -dumpmachine 2>/dev/null || true)"
        if [ -n "$cc_machine" ] && [ -n "$host_machine" ] && [ "$cc_machine" != "$host_machine" ]; then
            reasons+=("cross-compiler detected (CC -> ${cc_machine}, host ${host_machine})")
        fi
    fi

    [ "${#reasons[@]}" -eq 0 ] && return 0

    local self
    self="$(basename "${0:-this script}")"
    {
        echo ""
        echo "ERROR: ${self} is a developer/architecture wrapper and requires a native host toolchain."
        local r
        for r in "${reasons[@]}"; do echo "   - ${r}"; done
        echo ""
        echo "   Production / cross (Yocto/BitBake) builds MUST call CMake directly — these"
        echo "   wrappers are not for production recipes. See:"
        echo "     build-tools/linux_binder_idl/BUILD.md  (\"Production Build (CMake Direct)\")"
        echo ""
        echo "   To proceed anyway (not recommended): BINDER_ALLOW_CROSS_ENV=1 ./${self} ..."
        echo ""
    } >&2
    return 1
}
