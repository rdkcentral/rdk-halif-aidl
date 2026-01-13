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

# @brief Stage module libraries and headers to out/ directory
#
# This script is invoked by CMakeLists.txt as a post-build step to copy
# built module libraries and generated headers to the out/ directory.
#
# Expected variables:
#   OUT_DIR           - Base output directory (e.g., out/)
#   BUILD_DIR         - CMake build directory
#   STABLE_DIR        - Stable directory with generated headers
#   INTERFACE_TARGET  - Module name or "all"
#   AIDL_SRC_VERSION  - Version being built

cmake_minimum_required(VERSION 3.8)

# Determine module-specific subdirectory
if (INTERFACE_TARGET STREQUAL "all")
    set(MODULE_SUBDIR "")
    set(SEARCH_PATTERN "lib*-vcurrent-cpp.so")
else()
    set(MODULE_SUBDIR "${INTERFACE_TARGET}")
    set(SEARCH_PATTERN "lib${INTERFACE_TARGET}-vcurrent-cpp.so")
endif()

# Create output directories - separate binder and halif
set(BINDER_LIB_OUT_DIR "${OUT_DIR}/target/lib/binder")
set(HALIF_LIB_OUT_DIR "${OUT_DIR}/target/lib/halif")

file(MAKE_DIRECTORY "${BINDER_LIB_OUT_DIR}")
file(MAKE_DIRECTORY "${HALIF_LIB_OUT_DIR}")

#######################################################################
# Stage module libraries to out/target/lib/halif/
#######################################################################

message(STATUS "Staging module libraries from ${BUILD_DIR}...")

file(GLOB_RECURSE MODULE_LIBS "${BUILD_DIR}/${SEARCH_PATTERN}")

set(LIB_COUNT 0)
foreach(lib ${MODULE_LIBS})
    get_filename_component(lib_name "${lib}" NAME)

    # Extract module name from library name (e.g., libavclock-vcurrent-cpp.so -> avclock)
    string(REGEX MATCH "lib([a-z]+)-v" module_match "${lib_name}")
    if (module_match)
        set(module_name ${CMAKE_MATCH_1})

        # Copy to halif library directory
        file(COPY_FILE "${lib}" "${HALIF_LIB_OUT_DIR}/${lib_name}")

        math(EXPR LIB_COUNT "${LIB_COUNT} + 1")
        message(STATUS "  ✓ ${lib_name}")
    endif()
endforeach()

if (LIB_COUNT EQUAL 0)
    message(WARNING "No module libraries found in ${BUILD_DIR}")
else()
    message(STATUS "Staged ${LIB_COUNT} HAL interface libraries to ${HALIF_LIB_OUT_DIR}")
endif()

message(STATUS "")
message(STATUS "✓ Module staging complete")
message(STATUS "  HAL Libraries: ${HALIF_LIB_OUT_DIR}/")
message(STATUS "")
message(STATUS "Complete SDK structure:")
message(STATUS "  ${OUT_DIR}/target/bin/                - Binder servicemanager (runtime)")
message(STATUS "  ${OUT_DIR}/target/lib/binder/        - Binder runtime libraries")
message(STATUS "  ${OUT_DIR}/target/lib/halif/         - HAL interface libraries")
message(STATUS "  ${OUT_DIR}/build/include/binder_sdk/ - Binder headers (build-time)")
message(STATUS "  ${STABLE_DIR}/generated/             - HAL interface headers (build-time)")
message(STATUS "")
message(STATUS "Deploy to target: scp -r ${OUT_DIR}/target/{bin,lib} device:/usr/")
message(STATUS "                  (headers not needed on target)")
message(STATUS "")
