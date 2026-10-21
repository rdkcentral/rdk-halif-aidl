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
# build all released versions
# cmake --build build
#
# build all current versions
# cmake -S . -B build -DINTERFACE_RELEASE_FILE=versions_current.yaml
#
# build module in current version
# cmake -S . -B build -DINTERFACE_TARGET=bootreason
#
# build module in release version
# cmake -S . -B build -DINTERFACE_TARGET=bootreason -DINTERFACE_VERSION=0.1.0.0
#
# build all versions from specific yaml file
# cmake -S . -B build -DINTERFACE_RELEASE_FILE=/path/to/versions.yaml
#

cmake_minimum_required(VERSION 3.22)
project(RDK_HAL_AIDL_Modules LANGUAGES CXX C VERSION 0.23.0)

option(BUILD_MODULES_MODE "Set this when calling CMake from within build_modules.sh" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/")

if(BUILD_MODULES_MODE)
    message(STATUS "Build modules mode enabled")
    include(BuildModulesMode)
endif()

include(HandleModules)

find_package(Binder REQUIRED)
find_package(AndroidUtils REQUIRED)

if(NOT INTERFACE_RELEASE_FILE)
    set(INTERFACE_RELEASE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/versions_released.yaml")
endif()
if(NOT EXISTS "${INTERFACE_RELEASE_FILE}")
    message(FATAL_ERROR "Versions file does not exist: ${INTERFACE_RELEASE_FILE}")
endif()
message(STATUS "Using versions file: ${INTERFACE_RELEASE_FILE}")
parse_versions_yaml("${INTERFACE_RELEASE_FILE}" COMPONENTS)

# Build all versions from the manifest
if(NOT INTERFACE_TARGET)
    if(INTERFACE_VERSION)
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
