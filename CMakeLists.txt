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

# Libraries are default build as static use -DBUILD_SHARED_LIBS=ON for shared
# Usage:
#
# build all current version
# cmake --build build
#
# build all released versions
# cmake --build build -DINTERFACE_VERSION=release
#
# build module in current version
# cmake --build build -DINTERFACE_TARGET=boot
#
# build module in release version
# cmake --build build -DINTERFACE_TARGET=boot -DINTERFACE_VERSION=0.1.0.0

cmake_minimum_required(VERSION 3.22)
project(RDK_HAL_AIDL_Modules LANGUAGES CXX C VERSION 0.23.0)

# BUILD_SHARED_LIBS is a cmake default option. just adding it to make it more explicit.
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/")
include(HandleModules)

find_package(Binder REQUIRED)
find_package(AndroidUtils REQUIRED)

add_subdirectory("CMakeModules")

if(NOT INTERFACE_VERSION)
    parse_versions_yaml("${CMAKE_CURRENT_SOURCE_DIR}/versions_current.yaml" COMPONENTS)
else()
    parse_versions_yaml("${CMAKE_CURRENT_SOURCE_DIR}/versions_released.yaml" COMPONENTS)
endif()

# Build all current or release versions
if(NOT INTERFACE_TARGET)
    if(INTERFACE_VERSION AND NOT INTERFACE_VERSION STREQUAL "release")
        message(FATAL_ERROR " Unknown INTERFACE_VERSION ${INTERFACE_VERSION}")
    endif()
    foreach(_entry IN LISTS COMPONENTS)
        string(REGEX MATCH "^([^=]+)=(.*)$" _ "${_entry}")
        add_module_with_dependencies("${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
    endforeach()
endif()

# Build INTERFACE_TARGET current version
if(INTERFACE_TARGET AND NOT INTERFACE_VERSION)
    add_module_with_dependencies("${INTERFACE_TARGET}" "current")
endif()

# Build INTERFACE_TARGET INTERFACE_VERSION
if(INTERFACE_TARGET AND INTERFACE_VERSION)
    add_module_with_dependencies("${INTERFACE_TARGET}" "${INTERFACE_VERSION}")
endif()
