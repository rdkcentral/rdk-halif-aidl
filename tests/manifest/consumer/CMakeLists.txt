# Consumer of an installed rdk-halif-aidl prefix, driven by
# tests/manifest/test_install.sh. HALIF_CONSUMER_VIA selects how the HAL is found:
#   cmake      find_package(<Pkg> <ver> EXACT CONFIG) and the versioned target
#   pkgconfig  pkg-config rdk-halif-aidl-<comp>-<ver>
#   versions   two versions of common, each selected EXACT from one prefix
cmake_minimum_required(VERSION 3.22)
project(halif-consumer LANGUAGES CXX)
set(HALIF_CONSUMER_VIA "cmake" CACHE STRING "cmake | pkgconfig | versions")
set(CMAKE_CXX_STANDARD 17)

add_executable(consumer main.cpp)

if(HALIF_CONSUMER_VIA STREQUAL "cmake")
    find_package(RdkHalifAidlHdmicec 0.1.0.0 EXACT REQUIRED CONFIG)
    target_link_libraries(consumer PRIVATE RdkHalifAidl::hdmicec-v0.1.0.0-cpp)
elseif(HALIF_CONSUMER_VIA STREQUAL "pkgconfig")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(HAL REQUIRED IMPORTED_TARGET rdk-halif-aidl-hdmicec-0.1.0.0)
    target_link_libraries(consumer PRIVATE PkgConfig::HAL)
elseif(HALIF_CONSUMER_VIA STREQUAL "versions")
    find_package(RdkHalifAidlCommon 0.1.0.0 EXACT REQUIRED CONFIG)
    if(NOT RdkHalifAidlCommon_VERSION STREQUAL "0.1.0.0")
        message(FATAL_ERROR "asked for common 0.1.0.0 EXACT, got ${RdkHalifAidlCommon_VERSION}")
    endif()
    unset(RdkHalifAidlCommon_DIR CACHE)
    find_package(RdkHalifAidlCommon 0.2.0.0 EXACT REQUIRED CONFIG)
    if(NOT RdkHalifAidlCommon_VERSION STREQUAL "0.2.0.0")
        message(FATAL_ERROR "asked for common 0.2.0.0 EXACT, got ${RdkHalifAidlCommon_VERSION}")
    endif()
    if(NOT TARGET RdkHalifAidl::common-v0.1.0.0-cpp OR NOT TARGET RdkHalifAidl::common-v0.2.0.0-cpp)
        message(FATAL_ERROR "both common versions must be importable from one prefix")
    endif()
    find_package(RdkHalifAidlHdmicec 0.1.0.0 EXACT REQUIRED CONFIG)
    target_link_libraries(consumer PRIVATE RdkHalifAidl::hdmicec-v0.1.0.0-cpp)
else()
    message(FATAL_ERROR "HALIF_CONSUMER_VIA must be cmake, pkgconfig or versions")
endif()
