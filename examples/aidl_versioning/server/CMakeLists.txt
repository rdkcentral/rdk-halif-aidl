cmake_minimum_required(VERSION 3.8)

execute_process(COMMAND pwd OUTPUT_VARIABLE WORKING_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
if (DEFINED LINUX_BINDER_AIDL_ROOT)
    file(REAL_PATH ${LINUX_BINDER_AIDL_ROOT} LINUX_BINDER_AIDL_ROOT BASE_DIRECTORY ${WORKING_DIR})
else()
    file(REAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../build-tools/linux_binder_idl/" LINUX_BINDER_AIDL_ROOT BASE_DIRECTORY ${WORKING_DIR})
endif()

include(${LINUX_BINDER_AIDL_ROOT}/CMakeLists.inc)

add_subdirectory(car_service_ver_2)
add_subdirectory(car_service_ver_3)
