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
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************

# rdk-halif-aidl — manifest-driven build of the HAL interface bindings.
#
# The caller states WHICH versions to build; CMake resolves the rest from the
# tree. No <component>/<version>/ directory carries build logic.
#
#   cmake -S . -B build \
#       -DHALIF_VERSIONS_FILE=versions_released.yaml \      # top-level pins (default)
#       -DHALIF_COMPONENTS="hdmicec;audiodecoder:0.1.0.0" \ # subset, optional
#       -DBINDER_SDK_DIR=<sysroot>                          # Binder SDK (see FindBinder)
#   cmake --build build && cmake --install build --prefix <prefix>
#
#   -DHALIF_PLAN_ONLY=ON   resolve and print the plan, write build/halif_plan.txt, stop.
#
# Resolution: CMakeModules/HalifResolve.cmake. Per-node build and packaging:
# CMakeModules/HalifModule.cmake.

cmake_minimum_required(VERSION 3.22)
project(rdk-halif-aidl LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
include(GNUInstallDirs)
include(HalifResolve)
include(HalifModule)

#######################################################################
# Inputs
#######################################################################
set(HALIF_VERSIONS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/versions_released.yaml" CACHE FILEPATH
    "Versions manifest pinning the top-level components (empty: no manifest, latest released)")
set(HALIF_COMPONENTS "" CACHE STRING
    "Components to build, '<comp>' or '<comp>:<ver>' (empty: every component the manifest pins)")
option(HALIF_PLAN_ONLY "Resolve and print the build plan, then stop" OFF)

# Binder SDK location. The same variables the previous build and the Yocto
# recipes pass; FindBinder.cmake reads them.
set(BINDER_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/out/target" CACHE PATH "Binder SDK root (libraries)")
set(BINDER_SDK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/out/build" CACHE PATH "Binder SDK root (headers)")
set(HOST_AIDL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build-tools/linux_binder_idl/host" CACHE PATH
    "Directory holding the host aidl compiler (needed for 'current' nodes only)")

# Previous entry point (-DINTERFACE_TARGET=<comp|all> -DAIDL_SRC_VERSION=<ver>).
if(DEFINED INTERFACE_TARGET AND HALIF_COMPONENTS STREQUAL "")
    if(NOT DEFINED AIDL_SRC_VERSION)
        set(AIDL_SRC_VERSION "current")
    endif()
    message(DEPRECATION "INTERFACE_TARGET/AIDL_SRC_VERSION are replaced by HALIF_COMPONENTS/HALIF_VERSIONS_FILE")
    if(INTERFACE_TARGET STREQUAL "all")
        halif_all_components(_all)
        set(HALIF_COMPONENTS "")
        foreach(c IN LISTS _all)
            list(APPEND HALIF_COMPONENTS "${c}:${AIDL_SRC_VERSION}")
        endforeach()
    else()
        set(HALIF_COMPONENTS "${INTERFACE_TARGET}:${AIDL_SRC_VERSION}")
    endif()
endif()

#######################################################################
# Plan
#######################################################################
halif_resolve_plan(
    MANIFEST   "${HALIF_VERSIONS_FILE}"
    COMPONENTS ${HALIF_COMPONENTS}
    OUT_PLAN   HALIF_PLAN)

list(LENGTH HALIF_PLAN _n)
message(STATUS "rdk-halif-aidl: manifest '${HALIF_VERSIONS_FILE}', ${_n} node(s):")
set(_plan_text "")
set(_needs_aidl FALSE)
foreach(node IN LISTS HALIF_PLAN)
    halif_node_split("${node}" _c _v)
    halif_node_deps("${node}" _deps)
    string(REPLACE ";" " " _deps_text "${_deps}")
    message(STATUS "  ${_c} ${_v}  [${_deps_text}]")
    string(APPEND _plan_text "${_c} ${_v}\n")
    if(_v STREQUAL "current")
        set(_needs_aidl TRUE)
    endif()
endforeach()
file(WRITE "${CMAKE_BINARY_DIR}/halif_plan.txt" "${_plan_text}")

if(HALIF_PLAN_ONLY)
    message(STATUS "HALIF_PLAN_ONLY: plan written to ${CMAKE_BINARY_DIR}/halif_plan.txt")
    return()
endif()

#######################################################################
# Toolchain inputs
#######################################################################
find_package(Binder REQUIRED)

if(_needs_aidl)
    find_program(HALIF_AIDL_EXECUTABLE NAMES aidl
        HINTS "${HOST_AIDL_DIR}" "${HOST_AIDL_DIR}/bin"
        DOC "aidl compiler used to generate bindings for 'current' nodes")
    if(NOT HALIF_AIDL_EXECUTABLE)
        message(FATAL_ERROR
            "The plan contains 'current' nodes, which need the aidl compiler.\n"
            "Not found under HOST_AIDL_DIR=${HOST_AIDL_DIR}. Run ./build_binder.sh, "
            "or pass -DHALIF_AIDL_EXECUTABLE=<path>.")
    endif()
endif()

#######################################################################
# Build every node, dependencies first
#######################################################################
foreach(node IN LISTS HALIF_PLAN)
    halif_node_split("${node}" _c _v)
    halif_node_deps("${node}" _deps)
    halif_add_module(NAME "${_c}" VERSION "${_v}" DEPENDENCIES ${_deps})
endforeach()

# Find modules the installed package configs depend on, once per prefix.
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/FindBinder.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/FindAndroidUtils.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/rdk-halif-aidl")
