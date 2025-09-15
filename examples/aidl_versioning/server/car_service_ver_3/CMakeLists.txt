cmake_minimum_required(VERSION 3.8)

if (NOT DEFINED INTFS_ROOT_DIRS)
    file(REAL_PATH "../../../" INTFS_ROOT_DIRS BASE_DIRECTORY ${WORKING_DIR})
endif()

set(
    CarService_Sources
    CarServer.cpp
    CarService.cpp
    )

add_executable(CarServiceVer3 ${CarService_Sources})

target_link_intfs_libraries(CarServiceVer3
    com.demo.hal.car-V3-cpp
    )

target_link_libraries(CarServiceVer3 PRIVATE
    log
    )

install(
    TARGETS
    CarServiceVer3

    DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
