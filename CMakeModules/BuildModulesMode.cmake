# This file provides a collection of environment settings required when invoking CMake from build_modules.sh. It is
# needed because build_modules.sh does not follow standard CMake conventions for cross-compilation and toolchain
# handling, so these settings compensate for that gap.

set(CMAKE_FIND_ROOT_PATH "${CMAKE_SOURCE_DIR}/out/target;${CMAKE_FIND_ROOT_PATH}")
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/out/target")
set(CMAKE_INSTALL_LIBDIR "lib/rdk-halif-aidl")
set(BUILD_SHARED_LIBS ON)
set(CMAKE_CXX_FLAGS_INIT "-Wno-write-strings -Wno-attributes -Wno-return-type")
