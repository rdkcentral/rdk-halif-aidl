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
# Standalone direct-compile build for <component>/current/.
#
# Mirrors the shape of the snapshot CMakeLists written by release.sh into
# <component>/<version>/, so a downstream consumer can build any single
# component from its own directory:
#
#     cmake -S <component>/current -B build/<component> \
#         -DBINDER_SDK_DIR=/path/to/out/target \
#         -DBINDER_SDK_INCLUDE_DIR=/path/to/out/build \
#         -DHALIF_LIB_DIR=/path/to/out/target/lib/halif \
#         -DHALIF_INCLUDE_DIR=/path/to/out/build/include
#     cmake --build build/<component>
#
# The repo's overall build path (build_modules.sh / build_interfaces.sh)
# still uses the toolchain's CMakeLists.inc machinery to wire all
# components together; this file is for the single-module case (#546).
#
# PRE-REQUISITE — regenerate the bindings first. Since #566, src/ and
# include/ under current/ are gitignored toolchain output and do not
# exist in a fresh clone. Before invoking this standalone CMakeLists,
# run ./build_interfaces.sh <component> (from the repo root) to
# regenerate current/src/ and current/include/.
#
# Inputs:
#   BINDER_SDK_DIR          - linux_binder SDK root (lib/binder + include/binder_sdk)
#   BINDER_SDK_INCLUDE_DIR  - alternate headers root (dev layout splits headers/runtime)
#   HALIF_LIB_DIR           - directory holding dependency lib*-cpp.so
#   HALIF_INCLUDE_DIR       - directory holding dependency headers
cmake_minimum_required(VERSION 3.16)
project(hdmiinput-vcurrent-cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIB_NAME "hdmiinput-vcurrent-cpp")

if (NOT DEFINED BINDER_SDK_DIR)
    message(FATAL_ERROR "BINDER_SDK_DIR must be set")
endif()

# Resolve the Binder header root across the local-dev layout
# (<prefix>/include/binder_sdk) and Yocto/sysroot layouts (a direct include
# dir). First existing candidate wins; the dev layout is tried first so local
# builds are unaffected (#644).
set(_BINDER_INC "")
# Only consider a candidate whose base variable is actually set — otherwise an
# unset BINDER_SDK_INCLUDE_DIR would expand to an absolute "/include/..." path
# that could accidentally match a host directory.
set(_binder_inc_cands "")
if (BINDER_SDK_DIR)
    list(APPEND _binder_inc_cands "${BINDER_SDK_DIR}/include/binder_sdk")
endif()
if (BINDER_SDK_INCLUDE_DIR)
    list(APPEND _binder_inc_cands
        "${BINDER_SDK_INCLUDE_DIR}/include/binder_sdk"
        "${BINDER_SDK_INCLUDE_DIR}")
endif()
if (BINDER_SDK_DIR)
    list(APPEND _binder_inc_cands "${BINDER_SDK_DIR}/include")
endif()
foreach(_cand IN LISTS _binder_inc_cands)
    if (IS_DIRECTORY "${_cand}")
        set(_BINDER_INC "${_cand}")
        break()
    endif()
endforeach()
if (_BINDER_INC STREQUAL "")
    message(FATAL_ERROR
        "Binder SDK headers not found. Set BINDER_SDK_INCLUDE_DIR to the headers "
        "root (local dev: <prefix>/include/binder_sdk; Yocto: the staged include dir).")
endif()

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
if (NOT SRCS)
    message(FATAL_ERROR "No sources under src/. Run ./build_interfaces.sh hdmiinput first to regenerate.")
endif()

add_library(${LIB_NAME} SHARED ${SRCS})

target_include_directories(${LIB_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${_BINDER_INC}")

# Dependency component headers (staged by the toolchain build into HALIF_INCLUDE_DIR).
# Includes the transitive closure of imports so headers reachable via a direct
# dependency (e.g. common via audiodecoder) are also on the search path.
if (NOT DEFINED HALIF_INCLUDE_DIR)
    message(FATAL_ERROR "HALIF_INCLUDE_DIR is required (this component has HAL dependencies). "
        "Set it to the directory holding dependency headers (e.g. out/build/include).")
endif()
if (DEFINED HALIF_INCLUDE_DIR)
    target_include_directories(${LIB_NAME} PRIVATE
    "${HALIF_INCLUDE_DIR}/common/current/include")
endif()

target_link_directories(${LIB_NAME} PRIVATE
    "${BINDER_SDK_DIR}/lib/binder"
)
if (NOT DEFINED HALIF_LIB_DIR)
    message(FATAL_ERROR "HALIF_LIB_DIR is required (this component has HAL dependencies). "
        "Set it to the directory holding dependency lib*-cpp.so (e.g. out/target/lib/halif).")
endif()
if (DEFINED HALIF_LIB_DIR)
    target_link_directories(${LIB_NAME} PRIVATE "${HALIF_LIB_DIR}")
endif()

target_link_libraries(${LIB_NAME} PRIVATE binder utils common-vcurrent-cpp)

set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME "${LIB_NAME}")

include(GNUInstallDirs)
install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION lib/halif
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                        GROUP_READ GROUP_EXECUTE
                        WORLD_READ WORLD_EXECUTE)
