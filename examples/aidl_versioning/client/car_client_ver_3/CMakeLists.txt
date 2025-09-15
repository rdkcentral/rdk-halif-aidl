#/**
# * Copyright 2024 Comcast Cable Communications Management, LLC
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
# * SPDX-License-Identifier: Apache-2.0
# */

cmake_minimum_required(VERSION 3.8)

set(
    CarClient_Sources
    CarClient.cpp
    )

add_executable(CarClientVer3 ${CarClient_Sources})

# Link the interface library against your module.
# Ensure that correct name and the version provided and provided version is available
target_link_interfaces_libraries(CarClientVer3
    car-v3-cpp
    )

target_include_directories(CarClientVer3
    PRIVATE
    ${INTERFACES_ROOT_DIRS}/stable/generated/car/include/
    )

target_link_libraries(CarClientVer3 PRIVATE
    log
    )

install(
    TARGETS
    CarClientVer3

    DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

