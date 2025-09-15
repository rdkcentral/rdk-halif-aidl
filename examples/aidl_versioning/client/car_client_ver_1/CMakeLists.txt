cmake_minimum_required(VERSION 3.8)

if (NOT DEFINED INTFS_ROOT_DIRS)
    file(REAL_PATH "../../../" INTFS_ROOT_DIRS BASE_DIRECTORY ${WORKING_DIR})
endif()

set(
    CarClient_Sources
    CarClient.cpp
    )

add_executable(CarClientVer1 ${CarClient_Sources})

target_link_intfs_libraries(CarClientVer1
    com.demo.hal.car-V1-cpp
    )

target_link_libraries(CarClientVer1 PRIVATE
    log
    )

install(
    TARGETS
    CarClientVer1

    DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

