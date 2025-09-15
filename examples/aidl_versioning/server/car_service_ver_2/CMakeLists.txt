cmake_minimum_required(VERSION 3.8)

if (NOT DEFINED INTFS_ROOT_DIRS)
    file(REAL_PATH "../../../" INTFS_ROOT_DIRS BASE_DIRECTORY ${WORKING_DIR})
endif()

set(
    CarService_Sources
    CarServer.cpp
    CarService.cpp
    )

add_executable(CarServiceVer2 ${CarService_Sources})

target_link_intfs_libraries(CarServiceVer2
    com.demo.hal.car-V2-cpp
    )

target_link_libraries(CarServiceVer2 PRIVATE
    log
    )

install(
    TARGETS
    CarServiceVer2

    DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
