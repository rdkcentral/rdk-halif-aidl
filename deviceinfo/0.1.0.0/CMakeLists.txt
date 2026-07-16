# Auto-written by release.sh - do not hand-edit.
#
# Standalone direct-compile build for the released deviceinfo snapshot
# (version 0.1.0.0). The committed C++ in src/ and include/ is compiled
# into libdeviceinfo-v0.1.0.0-cpp.so. No code generation, no toolchain
# dependency - the snapshot is frozen pre-generated code.
#
# Inputs (set by the caller, typically build_modules.sh --version 0.1.0.0):
#   BINDER_SDK_DIR  - linux_binder SDK root (lib/binder + include/binder_sdk)
#   HALIF_LIB_DIR   - directory holding dependency lib<dep>-v<X.Y.Z.W>-cpp.so
cmake_minimum_required(VERSION 3.8)
project(deviceinfo-v0.1.0.0-cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIB_NAME "deviceinfo-v0.1.0.0-cpp")

if (NOT DEFINED BINDER_SDK_DIR)
    message(FATAL_ERROR "BINDER_SDK_DIR must be set for snapshot build")
endif()

# Resolve binder include path. Yocto stages a flat SDK so headers live under
# ${BINDER_SDK_DIR}/include/binder_sdk. The local dev layout splits headers
# (out/build/include/binder_sdk) from runtime libs (out/target/lib/binder),
# so allow BINDER_SDK_INCLUDE_DIR to point at the headers root.
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

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
if (NOT SRCS)
    message(FATAL_ERROR "No sources under src/. The snapshot must carry committed generated C++.")
endif()

add_library(${LIB_NAME} SHARED ${SRCS})

target_include_directories(${LIB_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${_BINDER_INC}")

target_link_directories(${LIB_NAME} PRIVATE
    "${BINDER_SDK_DIR}/lib/binder"
)
if (DEFINED HALIF_LIB_DIR)
    target_link_directories(${LIB_NAME} PRIVATE "${HALIF_LIB_DIR}")
endif()

target_link_libraries(${LIB_NAME} PRIVATE binder utils)

set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME "${LIB_NAME}")

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
