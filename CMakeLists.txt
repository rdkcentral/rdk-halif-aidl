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

cmake_minimum_required(VERSION 3.22)
project(RDK_HAL_AIDL_Modules LANGUAGES CXX C VERSION 0.21.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/")
include(HandleModules)

find_package(Binder REQUIRED)
find_package(AndroidUtils REQUIRED)

add_subdirectory("CMakeModules")

if(NOT INTERFACE_VERSION)
    parse_versions_yaml("${CMAKE_CURRENT_SOURCE_DIR}/versions_current.yaml" COMPONENTS)
    # find_program(
    #     AIDL_EXECUTABLE
    #     NAMES aidl
    #     HINTS ENV PATH "${PROJECT_SOURCE_DIR}/build-tools/linux_binder_idl/build-host"
    #     DOC "aidl executable location"
    # )
    # if(NOT AIDL_EXECUTABLE)
    #     message(FATAL_ERROR "Unable to find the aidl executable")
    # endif()
else()
    parse_versions_yaml("${CMAKE_CURRENT_SOURCE_DIR}/versions_released.yaml" COMPONENTS)
endif()

# Build all current versions
if(NOT INTERFACE_TARGET AND NOT INTERFACE_VERSION)
    foreach(_entry IN LISTS COMPONENTS)
        string(REGEX MATCH "^([^=]+)=(.*)$" _ "${_entry}")
        add_module_with_dependencies("${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
    endforeach()
endif()

# Build all released versions
if(NOT INTERFACE_TARGET AND INTERFACE_VERSION)
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
