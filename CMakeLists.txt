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

# @brief Build RDK HAL AIDL modules
#
# This CMakeLists builds individual HAL modules that depend on the
# Binder SDK pre-built in out/target/
#
# Two-stage build process:
#
# Stage 1 - Build Binder SDK (once):
#   ./install_binder.sh
#   → Creates out/target/ with binder runtime
#
# Stage 2 - Build HAL module:
#   cmake -S . -B build/<module> -DINTERFACE_TARGET=<module> -DINTERFACE_VERSION=current
#   cmake --build build/<module> -j4
#   → Uses out/target/ and creates module libraries in out/<module>/

cmake_minimum_required(VERSION 3.8)

project(RDK_HAL_AIDL_Modules LANGUAGES NONE VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

#######################################################################
# Configuration variables with sensible defaults
#######################################################################

# Module to build (required)
if (NOT DEFINED INTERFACE_TARGET)
    message(STATUS "INTERFACE_TARGET not set, defaulting to 'all'")
    set(INTERFACE_TARGET "all")
endif()

# Version to build (current, latest, all, or specific version)
if (NOT DEFINED AIDL_SRC_VERSION)
    set(AIDL_SRC_VERSION "current")
    message(STATUS "AIDL_SRC_VERSION defaulted to ${AIDL_SRC_VERSION}")
endif()

# Binder SDK location (must be built first via Stage 1)
if (NOT DEFINED BINDER_SDK_DIR)
    set(BINDER_SDK_DIR "${CMAKE_SOURCE_DIR}/out/target")
endif()

# Module sources root
if (NOT DEFINED INTERFACES_ROOT_DIRS)
    set(INTERFACES_ROOT_DIRS "${CMAKE_SOURCE_DIR}")
endif()

# Output directory for module libraries and headers
if (NOT DEFINED OUT_DIR)
    set(OUT_DIR "${CMAKE_SOURCE_DIR}/out")
endif()

# Binder toolchain root (for CMakeLists.inc inclusion)
if (NOT DEFINED LINUX_BINDER_AIDL_ROOT)
    set(LINUX_BINDER_AIDL_ROOT "${CMAKE_SOURCE_DIR}/build-tools/linux_binder_idl")
endif()

# Host AIDL compiler directory
if (NOT DEFINED HOST_AIDL_DIR)
    set(HOST_AIDL_DIR "${LINUX_BINDER_AIDL_ROOT}/host")
endif()

message(STATUS "====================================")
message(STATUS "RDK HAL AIDL - Module Build")
message(STATUS "====================================")
message(STATUS "Target:      ${INTERFACE_TARGET}")
message(STATUS "Version:     ${AIDL_SRC_VERSION}")
message(STATUS "Binder SDK:  ${BINDER_SDK_DIR}")
message(STATUS "Output:      ${OUT_DIR}")
message(STATUS "====================================")

#######################################################################
# Verify binder SDK exists (Stage 1 must complete first)
#######################################################################

if (NOT EXISTS "${BINDER_SDK_DIR}/.sdk_ready")
    message("")
    message("========================================")
    message("  Binder SDK not found!")
    message("========================================")
    message("")
    message("The Binder SDK must be built before building modules.")
    message("")
    message("Please run Stage 1 first:")
    message("  ./install_binder.sh")
    message("")
    message("This will create the Binder SDK in: ${BINDER_SDK_DIR}")
    message("")
    message("Then retry this module build.")
    message("========================================")
    message(FATAL_ERROR "Binder SDK not ready")
endif()

message(STATUS "✓ Binder SDK found at ${BINDER_SDK_DIR}")

#######################################################################
# Set up paths for module builds to use binder SDK
#######################################################################

# Point binder build system to where generated code should be placed
# The binder system uses this directly without knowing about project structure
set(LINUX_BINDER_AIDL_ROOT_OUT "${CMAKE_SOURCE_DIR}/stable/generated")

# Make binder SDK headers and libraries available (from binder subdirectory)
include_directories(${BINDER_SDK_DIR}/include/binder_sdk)
link_directories(${BINDER_SDK_DIR}/lib/binder)

#######################################################################
# Include binder CMake infrastructure for interface builds
#######################################################################

include(${HOST_AIDL_DIR}/CMakeLists.inc)

#######################################################################
# Build interface libraries based on INTERFACE_TARGET and INTERFACE_VERSION
#######################################################################

target_build_interfaces_libraries()

#######################################################################
# Stage headers BEFORE building so compilation uses staged headers
#######################################################################

message(STATUS "Staging generated headers to ${OUT_DIR}/target/include/halif/...")

# Determine which modules to stage headers for
if (INTERFACE_TARGET STREQUAL "all")
    file(GLOB MODULE_DIRS LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/stable/generated/*")
else()
    set(MODULE_DIRS "${CMAKE_SOURCE_DIR}/stable/generated/${INTERFACE_TARGET}")
endif()

# Copy headers from stable/generated/ to out/target/include/halif/
foreach(module_dir ${MODULE_DIRS})
    if (IS_DIRECTORY "${module_dir}")
        get_filename_component(module_name "${module_dir}" NAME)
        file(GLOB_RECURSE MODULE_HEADERS "${module_dir}/*.h")
        foreach(header ${MODULE_HEADERS})
            file(RELATIVE_PATH rel_path "${CMAKE_SOURCE_DIR}/stable/generated" "${header}")
            get_filename_component(dest_dir "${OUT_DIR}/target/include/halif/${rel_path}" DIRECTORY)
            file(MAKE_DIRECTORY "${dest_dir}")
            file(COPY_FILE "${header}" "${OUT_DIR}/target/include/halif/${rel_path}")
        endforeach()
    endif()
endforeach()

#######################################################################
# Fix AIDL generator bug: Add missing #include <mutex> to generated .cpp files
# The AIDL generator omits this include for callback/listener interfaces
#######################################################################

file(GLOB_RECURSE GENERATED_CPP_FILES "${CMAKE_SOURCE_DIR}/stable/generated/*/current/src/*.cpp")
foreach(CPP_FILE ${GENERATED_CPP_FILES})
    file(READ "${CPP_FILE}" FILE_CONTENTS)
    # Check if file uses mutex but doesn't include it
    if(FILE_CONTENTS MATCHES "std::mutex|std::lock_guard" AND NOT FILE_CONTENTS MATCHES "#include <mutex>")
        # Prepend #include <mutex> to the file
        file(WRITE "${CPP_FILE}" "#include <mutex>\n${FILE_CONTENTS}")
        message(STATUS "Added #include <mutex> to ${CPP_FILE}")
    endif()
endforeach()

#######################################################################
# Stage module outputs to out/ directory
#######################################################################

# Create custom target to stage module libraries and headers
add_custom_target(stage_modules ALL
    COMMAND ${CMAKE_COMMAND}
        -DOUT_DIR=${OUT_DIR}
        -DBUILD_DIR=${CMAKE_BINARY_DIR}
        -DSTABLE_DIR=${LINUX_BINDER_AIDL_ROOT_OUT}
        -DINTERFACE_TARGET=${INTERFACE_TARGET}
        -DAIDL_SRC_VERSION=${AIDL_SRC_VERSION}
        -P ${CMAKE_SOURCE_DIR}/cmake_stage_modules.cmake
    COMMENT "Staging module outputs to ${OUT_DIR}..."
)

# Find all interface library targets and make stage_modules depend on them
# This ensures all modules are built before staging
get_property(ALL_TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
foreach(target ${ALL_TARGETS})
    if (target MATCHES ".*-vcurrent-cpp$" OR target MATCHES ".*-v[0-9]+-cpp$")
        add_dependencies(stage_modules ${target})
    endif()
endforeach()

message(STATUS "")
message(STATUS "Module libraries will be built and staged to: ${OUT_DIR}")
message(STATUS "")
