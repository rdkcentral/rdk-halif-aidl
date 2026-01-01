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

# Configure SDK subdirectory structure (overridable for Yocto flat structure)
if (NOT DEFINED BINDER_SDK_INCLUDE_SUBDIR)
    set(BINDER_SDK_INCLUDE_SUBDIR "include/binder_sdk")
endif()
if (NOT DEFINED BINDER_SDK_LIB_SUBDIR)
    set(BINDER_SDK_LIB_SUBDIR "lib/binder")
endif()

message(STATUS "Binder include path: ${BINDER_SDK_DIR}/${BINDER_SDK_INCLUDE_SUBDIR}")
message(STATUS "Binder library path: ${BINDER_SDK_DIR}/${BINDER_SDK_LIB_SUBDIR}")

# Make binder SDK headers and libraries available
include_directories(${BINDER_SDK_DIR}/${BINDER_SDK_INCLUDE_SUBDIR})
link_directories(${BINDER_SDK_DIR}/${BINDER_SDK_LIB_SUBDIR})

#######################################################################
# Configure installation directories
#######################################################################

# Default to OUT_DIR/target for local development (maintains current behavior)
# Yocto will override with -DCMAKE_INSTALL_PREFIX=${D}${prefix}
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${OUT_DIR}/target" CACHE PATH "Install prefix" FORCE)
    message(STATUS "CMAKE_INSTALL_PREFIX defaulted to ${CMAKE_INSTALL_PREFIX}")
else()
    message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
endif()

# Set standard installation directories
include(GNUInstallDirs)
if (NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR "lib/halif")
endif()
if (NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR "include/halif")
endif()

message(STATUS "Libraries will install to: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
message(STATUS "Headers will install to: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")

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
# Install module outputs using standard CMake install commands
#######################################################################

# Install HAL module libraries
# Pattern matches all generated library files from build directory
install(CODE "
    file(GLOB_RECURSE MODULE_LIBS
         \"${CMAKE_BINARY_DIR}/lib*-vcurrent-cpp.so*\"
         \"${CMAKE_BINARY_DIR}/lib*-v[0-9]+-cpp.so*\")
    foreach(lib IN LISTS MODULE_LIBS)
        file(INSTALL \${lib}
             DESTINATION \"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\"
             USE_SOURCE_PERMISSIONS)
    endforeach()
    message(STATUS \"Installed HAL module libraries to ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}\")
")

# Install HAL module headers from pre-generated code
if (INTERFACE_TARGET STREQUAL "all")
    # Install all module headers
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/stable/generated/"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
            FILES_MATCHING PATTERN "*.h"
            PATTERN "CMakeFiles" EXCLUDE)
else()
    # Install single module headers
    if (EXISTS "${CMAKE_SOURCE_DIR}/stable/generated/${INTERFACE_TARGET}")
        install(DIRECTORY "${CMAKE_SOURCE_DIR}/stable/generated/${INTERFACE_TARGET}/"
                DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${INTERFACE_TARGET}"
                FILES_MATCHING PATTERN "*.h"
                PATTERN "CMakeFiles" EXCLUDE)
    endif()
endif()

message(STATUS "")
message(STATUS "Build complete. Use 'cmake --install' to install:")
message(STATUS "  Libraries: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
message(STATUS "  Headers:   ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "")
