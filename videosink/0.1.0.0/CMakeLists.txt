# Auto-written by release.sh - do not hand-edit.
#
# Standalone direct-compile build for the released videosink snapshot
# (version 0.1.0.0). The committed C++ in src/ and include/ is compiled
# into libvideosink-v0.1.0.0-cpp.so. No code generation, no toolchain
# dependency - the snapshot is frozen pre-generated code.
#
# Inputs (set by the caller, typically build_modules.sh --version 0.1.0.0):
#   BINDER_SDK_DIR  - linux_binder SDK root (lib/binder + include/binder_sdk)
#   HALIF_LIB_DIR   - directory holding dependency lib<dep>-vcurrent-cpp.so
cmake_minimum_required(VERSION 3.8)
project(videosink-v0.1.0.0-cpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIB_NAME "videosink-v0.1.0.0-cpp")

if (NOT DEFINED BINDER_SDK_DIR)
    message(FATAL_ERROR "BINDER_SDK_DIR must be set for snapshot build")
endif()

# Resolve binder include path. Yocto stages a flat SDK so headers live under
# ${BINDER_SDK_DIR}/include/binder_sdk. The local dev layout splits headers
# (out/build/include/binder_sdk) from runtime libs (out/target/lib/binder),
# so allow BINDER_SDK_INCLUDE_DIR to point at the headers root.
set(_BINDER_INC "${BINDER_SDK_DIR}/include/binder_sdk")
if (NOT IS_DIRECTORY "${_BINDER_INC}")
    if (DEFINED BINDER_SDK_INCLUDE_DIR AND
        IS_DIRECTORY "${BINDER_SDK_INCLUDE_DIR}/include/binder_sdk")
        set(_BINDER_INC "${BINDER_SDK_INCLUDE_DIR}/include/binder_sdk")
    else()
        message(FATAL_ERROR
            "Binder SDK headers not found at ${_BINDER_INC}. "
            "Set BINDER_SDK_INCLUDE_DIR to the headers root.")
    endif()
endif()

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
if (NOT SRCS)
    message(FATAL_ERROR "No sources under src/. The snapshot must carry committed generated C++.")
endif()

add_library(${LIB_NAME} SHARED ${SRCS})

target_include_directories(${LIB_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${_BINDER_INC}"
)
# Dependency component headers (staged by the current/ build into HALIF_INCLUDE_DIR).
if (DEFINED HALIF_INCLUDE_DIR)
    target_include_directories(${LIB_NAME} PRIVATE
    "${HALIF_INCLUDE_DIR}/avclock/current/include"
    "${HALIF_INCLUDE_DIR}/common/current/include"
    "${HALIF_INCLUDE_DIR}/videodecoder/current/include")
endif()
target_link_directories(${LIB_NAME} PRIVATE
    "${BINDER_SDK_DIR}/lib/binder"
)
if (DEFINED HALIF_LIB_DIR)
    target_link_directories(${LIB_NAME} PRIVATE "${HALIF_LIB_DIR}")
endif()

target_link_libraries(${LIB_NAME} PRIVATE binder utils avclock-vcurrent-cpp common-vcurrent-cpp videodecoder-vcurrent-cpp)
target_link_options(${LIB_NAME} PRIVATE -Wl,--allow-shlib-undefined)

set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME "${LIB_NAME}")

include(GNUInstallDirs)
install(TARGETS ${LIB_NAME} LIBRARY DESTINATION lib/halif)
