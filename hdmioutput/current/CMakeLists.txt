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

<<<<<<< HEAD
add_current(
    NAME "hdmioutput"
    DEPENDENCIES
    "common"
)
||||||| parent of 4b173fd3 (Split up cmake packages for binder and binderutils Change install path for cmake packages Add full list of source files to cmake packages)
set(LIB_NAME "hdmioutput-vcurrent-cpp")

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
        "${BINDER_SDK_INCLUDE_DIR}/include")
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
    message(FATAL_ERROR "No sources under src/. Run ./build_interfaces.sh hdmioutput first to regenerate.")
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
        "Set it to the directory holding dependency lib*-cpp.so (e.g. out/target/lib/rdk-halif-aidl).")
endif()
if (DEFINED HALIF_LIB_DIR)
    target_link_directories(${LIB_NAME} PRIVATE "${HALIF_LIB_DIR}")
endif()

target_link_libraries(${LIB_NAME} PRIVATE binder utils common-vcurrent-cpp)

# The target_link_directories() above are BUILD-time search paths. By default
# CMake bakes them into the library as RPATH/RUNPATH, which ships absolute build
# paths inside the .so - Yocto's do_package_qa rejects that, and the runtime
# search path belongs to the integrator's image, not to this library.
#
# Default to emitting no RPATH. Overridable for builds that genuinely need one:
# pass -DHALIF_INSTALL_RPATH=<path>.
if (NOT DEFINED HALIF_INSTALL_RPATH)
    set(HALIF_INSTALL_RPATH "")
endif()

set_target_properties(${LIB_NAME} PROPERTIES
    OUTPUT_NAME "${LIB_NAME}"
    SKIP_BUILD_RPATH TRUE
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "${HALIF_INSTALL_RPATH}")

include(GNUInstallDirs)

# Install destination for the built interface library. Overridable so the
# location can be changed by the build (or in future) without editing this
# snapshot: pass -DHALIF_INSTALL_LIBDIR=<dir>.
if (NOT DEFINED HALIF_INSTALL_LIBDIR)
    set(HALIF_INSTALL_LIBDIR "lib/rdk-halif-aidl")
endif()

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION ${HALIF_INSTALL_LIBDIR}
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                        GROUP_READ GROUP_EXECUTE
                        WORLD_READ WORLD_EXECUTE)
=======
add_current(NAME "hdmioutput" DEPENDENCIES "common")
>>>>>>> 4b173fd3 (Split up cmake packages for binder and binderutils Change install path for cmake packages Add full list of source files to cmake packages)
