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

cmake_minimum_required(VERSION 3.22)
project(RDK_HAL_AIDL_Modules LANGUAGES CXX C VERSION 0.21.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/")
include(HandleModules)

find_package(Binder REQUIRED)

option(BUILD_CURRENT "Build current version of HAL modules" OFF)

add_subdirectory("CMakeModules")

add_subdirectory("common")
add_subdirectory("avclock")

# @brief Build RDK HAL AIDL modules
#
# This CMakeLists builds individual HAL modules that depend on the
# Binder SDK pre-built in out/target/
#
# Two-stage build process:
#
# Stage 1 - Build Binder SDK (once):
#   ./build_binder.sh
#   → Creates out/target/ with binder runtime
#
# Stage 2 - Build HAL module:
#   cmake -S . -B build/<module> -DINTERFACE_TARGET=<module> -DINTERFACE_VERSION=current
#   cmake --build build/<module> -j4
#   → Uses out/target/ and creates module libraries in out/<module>/
#
#cmake_minimum_required(VERSION 3.8)
#
########################################################################
## Respect Yocto/external compiler and flags environment variables
########################################################################
#
## CMake respects CC/CXX environment variables if set before project()
## For Yocto integration: export CC, CXX, CFLAGS, CXXFLAGS in recipe
## Example: CC="${CC}" CXX="${CXX}" cmake ...
#
## Append environment CFLAGS/CXXFLAGS to CMake flags if provided
#if(DEFINED ENV{CFLAGS})
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} $ENV{CFLAGS}" CACHE STRING "C compiler flags" FORCE)
#    message(STATUS "Using CFLAGS from environment: $ENV{CFLAGS}")
#endif()
#
#if(DEFINED ENV{CXXFLAGS})
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} $ENV{CXXFLAGS}" CACHE STRING "C++ compiler flags" FORCE)
#    message(STATUS "Using CXXFLAGS from environment: $ENV{CXXFLAGS}")
#endif()
#
#if(DEFINED ENV{LDFLAGS})
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} $ENV{LDFLAGS}" CACHE STRING "Linker flags" FORCE)
#    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} $ENV{LDFLAGS}" CACHE STRING "Shared linker flags" FORCE)
#    message(STATUS "Using LDFLAGS from environment: $ENV{LDFLAGS}")
#endif()
#
#project(RDK_HAL_AIDL_Modules LANGUAGES CXX C VERSION 1.0)
#
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
#
## Display compiler information for verification
#message(STATUS "C Compiler:   ${CMAKE_C_COMPILER}")
#message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
#message(STATUS "C Flags:      ${CMAKE_C_FLAGS}")
#message(STATUS "CXX Flags:    ${CMAKE_CXX_FLAGS}")
#
########################################################################
## Configuration variables with sensible defaults
########################################################################
#
## Module to build (required)
#if (NOT DEFINED INTERFACE_TARGET)
#    message(STATUS "INTERFACE_TARGET not set, defaulting to 'all'")
#    set(INTERFACE_TARGET "all")
#endif()
#
## Version to build (current, latest, all, or specific version)
#if (NOT DEFINED AIDL_SRC_VERSION)
#    set(AIDL_SRC_VERSION "current")
#    message(STATUS "AIDL_SRC_VERSION defaulted to ${AIDL_SRC_VERSION}")
#endif()
#
## Binder SDK location (must be built first via Stage 1)
#if (NOT DEFINED BINDER_SDK_DIR)
#    set(BINDER_SDK_DIR "${CMAKE_SOURCE_DIR}/out/target")
#endif()
#
## Module sources root
#if (NOT DEFINED INTERFACES_ROOT_DIRS)
#    set(INTERFACES_ROOT_DIRS "${CMAKE_SOURCE_DIR}")
#endif()
#
## Output directory for module libraries and headers
#if (NOT DEFINED OUT_DIR)
#    set(OUT_DIR "${CMAKE_SOURCE_DIR}/out")
#endif()
#
## Binder toolchain root (for CMakeLists.inc inclusion)
#if (NOT DEFINED LINUX_BINDER_AIDL_ROOT)
#    set(LINUX_BINDER_AIDL_ROOT "${CMAKE_SOURCE_DIR}/build-tools/linux_binder_idl")
#endif()
#
## Host AIDL compiler directory
#if (NOT DEFINED HOST_AIDL_DIR)
#    set(HOST_AIDL_DIR "${LINUX_BINDER_AIDL_ROOT}/host")
#endif()
#
#message(STATUS "====================================")
#message(STATUS "RDK HAL AIDL - Module Build")
#message(STATUS "====================================")
#message(STATUS "Target:      ${INTERFACE_TARGET}")
#message(STATUS "Version:     ${AIDL_SRC_VERSION}")
#message(STATUS "Binder SDK:  ${BINDER_SDK_DIR}")
#message(STATUS "Output:      ${OUT_DIR}")
#message(STATUS "====================================")
#
########################################################################
## Verify binder SDK exists (Stage 1 must complete first)
########################################################################
#
#if (NOT EXISTS "${BINDER_SDK_DIR}/.sdk_ready")
#    message("")
#    message("========================================")
#    message("  Binder SDK not found!")
#    message("========================================")
#    message("")
#    message("The Binder SDK must be built before building modules.")
#    message("")
#    message("Please run Stage 1 first:")
#    message("  ./build_binder.sh")
#    message("")
#    message("This will create the Binder SDK in: ${BINDER_SDK_DIR}")
#    message("")
#    message("Then retry this module build.")
#    message("========================================")
#    message(FATAL_ERROR "Binder SDK not ready")
#endif()
#
#message(STATUS "✓ Binder SDK found at ${BINDER_SDK_DIR}")
#
########################################################################
## Set up paths for module builds to use binder SDK
########################################################################
#
## Module-local generation: each component's generated C++ lives in its own
## directory, <module>/<version>/{include,src}. LINUX_BINDER_AIDL_GENERATED_ROOT
## is the base the binder build system resolves <module>/<version>/ against, so
## it is the repo root. LINUX_BINDER_AIDL_ROOT_OUT is the intermediate out/ tree
## (dependency graph, preprocessed AIDL) and is kept separate.
#set(LINUX_BINDER_AIDL_GENERATED_ROOT "${CMAKE_SOURCE_DIR}")
#set(LINUX_BINDER_AIDL_ROOT_OUT "${OUT_DIR}/aidl")
#
## Separate base directories for headers (build-time) vs runtime (libs/bins)
#if (NOT DEFINED BINDER_SDK_INCLUDE_DIR)
#    set(BINDER_SDK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/out/build")
#endif()
#
## Configure SDK subdirectory structure (overridable for Yocto flat structure)
#if (NOT DEFINED BINDER_SDK_INCLUDE_SUBDIR)
#    set(BINDER_SDK_INCLUDE_SUBDIR "include/binder_sdk")
#endif()
#if (NOT DEFINED BINDER_SDK_LIB_SUBDIR)
#    set(BINDER_SDK_LIB_SUBDIR "lib/binder")
#endif()
#
#message(STATUS "Binder include path: ${BINDER_SDK_INCLUDE_DIR}/${BINDER_SDK_INCLUDE_SUBDIR}")
#message(STATUS "Binder library path: ${BINDER_SDK_DIR}/${BINDER_SDK_LIB_SUBDIR}")
#
## Make binder SDK headers and libraries available
#include_directories(${BINDER_SDK_INCLUDE_DIR}/${BINDER_SDK_INCLUDE_SUBDIR})
#link_directories(${BINDER_SDK_DIR}/${BINDER_SDK_LIB_SUBDIR})
#
########################################################################
## Configure installation directories
########################################################################
#
## Default to OUT_DIR/target for local development (maintains current behavior)
## Yocto will override with -DCMAKE_INSTALL_PREFIX=${D}${prefix}
#if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#    set(CMAKE_INSTALL_PREFIX "${OUT_DIR}/target" CACHE PATH "Install prefix" FORCE)
#    message(STATUS "CMAKE_INSTALL_PREFIX defaulted to ${CMAKE_INSTALL_PREFIX}")
#else()
#    message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
#endif()
#
## Set halif subdirectories as defaults BEFORE including GNUInstallDirs
## This allows caller to override via -DCMAKE_INSTALL_LIBDIR=... while providing sensible defaults
#if (NOT DEFINED CMAKE_INSTALL_LIBDIR)
#    set(CMAKE_INSTALL_LIBDIR "lib/halif" CACHE PATH "Library install directory")
#endif()
#if (NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
#    set(CMAKE_INSTALL_INCLUDEDIR "include/halif" CACHE PATH "Header install directory")
#endif()
#
## Set standard installation directories (will respect variables already set above)
#include(GNUInstallDirs)
#
#message(STATUS "Libraries will install to: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
#message(STATUS "Headers will install to: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
#
########################################################################
## Include binder CMake infrastructure for interface builds.
##
## Any root build (this top-level CMakeLists, for any INTERFACE_TARGET) includes
## the linux_binder_idl toolchain's CMakeLists.inc unconditionally, so it needs
## that source tree present — i.e. the local dev / integrated build. A standalone
## Yocto/staged-SDK build does NOT have it: there, libbinder is built + staged by
## the `linux-binder` recipe and
## the HAL libraries are built PER COMPONENT from the staged SDK, using each
## component's self-contained CMakeLists (no CMakeLists.inc):
##     cmake -S <module>/<version> -B build \
##           -DBINDER_SDK_DIR=<sysroot> -DBINDER_SDK_INCLUDE_DIR=<sysroot>
## Fail fast with that pointer rather than a cryptic include() error. (#635)
########################################################################
#if (NOT EXISTS "${HOST_AIDL_DIR}/CMakeLists.inc")
#    message(FATAL_ERROR
#        "linux_binder_idl toolchain not found at ${HOST_AIDL_DIR}.\n"
#        "The root build (this top-level CMakeLists, any INTERFACE_TARGET) requires the linux_binder_idl source. "
#        "For a staged-SDK / Yocto build, build components individually from the "
#        "staged SDK instead:\n"
#        "  cmake -S <module>/<version> -B build "
#        "-DBINDER_SDK_DIR=<sysroot> -DBINDER_SDK_INCLUDE_DIR=<sysroot>\n"
#        "Each <module>/<version>/CMakeLists.txt is self-contained. See the "
#        "production-build section of the README.")
#endif()
#include("${HOST_AIDL_DIR}/CMakeLists.inc")
#
########################################################################
## Build interface libraries based on INTERFACE_TARGET and INTERFACE_VERSION
########################################################################
#
#target_build_interfaces_libraries()
#
########################################################################
## Stage headers BEFORE building so compilation uses staged headers
########################################################################
#
#message(STATUS "Staging generated headers to ${OUT_DIR}/target/include/halif/...")
#
## Module-local layout: generated headers live in <module>/current/include/.
#if (INTERFACE_TARGET STREQUAL "all")
#    file(GLOB MODULE_INC_DIRS LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/*/current/include")
#else()
#    set(MODULE_INC_DIRS "${CMAKE_SOURCE_DIR}/${INTERFACE_TARGET}/current/include")
#endif()
#
## Copy generated headers from <module>/current/include/ to out/build/include/
#foreach(inc_dir ${MODULE_INC_DIRS})
#    if (IS_DIRECTORY "${inc_dir}")
#        file(GLOB_RECURSE MODULE_HEADERS "${inc_dir}/*.h")
#        foreach(header ${MODULE_HEADERS})
#            file(RELATIVE_PATH rel_path "${CMAKE_SOURCE_DIR}" "${header}")
#            get_filename_component(dest_dir "${OUT_DIR}/build/include/${rel_path}" DIRECTORY)
#            file(MAKE_DIRECTORY "${dest_dir}")
#            file(COPY_FILE "${header}" "${OUT_DIR}/build/include/${rel_path}")
#        endforeach()
#    endif()
#endforeach()
#
########################################################################
## Post-build: Stage module libraries to out/target/lib/halif/
########################################################################
## Invoke cmake_stage_modules.cmake after all libraries are built
#
#add_custom_target(stage_modules ALL
#    COMMAND ${CMAKE_COMMAND}
#        -DOUT_DIR=${OUT_DIR}
#        -DBUILD_DIR=${CMAKE_BINARY_DIR}
#        -DREPO_ROOT=${CMAKE_SOURCE_DIR}
#        -DINTERFACE_TARGET=${INTERFACE_TARGET}
#        -DAIDL_SRC_VERSION=${AIDL_SRC_VERSION}
#        -P ${CMAKE_SOURCE_DIR}/cmake_stage_modules.cmake
#    COMMENT "Staging HAL module libraries and headers to out/target/"
#    VERBATIM
#)
#
## Ensure staging happens after all libraries are built. The pattern
## matches both current (`-vcurrent-cpp`) and frozen-snapshot
## (`-v<X.Y.Z.W>-cpp`) target names so on-disk snapshot libraries that
## the toolchain auto-discovers (linux_binder_idl#23 / #538) are also
## staged alongside `current/`.
#if (INTERFACE_TARGET STREQUAL "all")
#    # When building all modules, add dependencies on all library targets
#    get_property(all_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
#    foreach(target ${all_targets})
#        if (target MATCHES ".*-v[^-]+-cpp$")
#            add_dependencies(stage_modules ${target})
#        endif()
#    endforeach()
#else()
#    # When building a specific module, depend on every variant of its
#    # library target — current plus any registered snapshots.
#    get_property(all_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
#    foreach(target ${all_targets})
#        if (target MATCHES "^${INTERFACE_TARGET}-v[^-]+-cpp$")
#            add_dependencies(stage_modules ${target})
#        endif()
#    endforeach()
#endif()
#
########################################################################
## Build completion message
########################################################################
#
#message(STATUS "")
#message(STATUS "Build configured. HAL modules will be staged to:")
#message(STATUS "  Libraries: ${OUT_DIR}/target/lib/halif/")
#message(STATUS "  Headers:   ${OUT_DIR}/target/include/halif/")
#message(STATUS "")
#message(STATUS "Run 'cmake --build <build-dir>' to build")
#message(STATUS "")
