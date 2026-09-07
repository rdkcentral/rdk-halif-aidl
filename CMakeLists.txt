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

option(BUILD_CURRENT "Build current version of HAL modules" OFF)

if(BUILD_CURRENT)
    find_program(
        AIDL_EXECUTABLE
        NAMES aidl
        HINTS ENV PATH "${PROJECT_SOURCE_DIR}/build-tools/linux_binder_idl/build-host"
        DOC "aidl executable location"
    )
    if(NOT AIDL_EXECUTABLE)
        message(FATAL_ERROR "Unable to find the aidl executable")
    endif()
endif()

add_subdirectory("CMakeModules")

add_subdirectory("common")
add_subdirectory("avclock")
add_subdirectory("compositeinput")
add_subdirectory("deepsleep")
add_subdirectory("deviceinfo")
add_subdirectory("drm")
add_subdirectory("firmwareupdate")
add_subdirectory("hdmicec")
add_subdirectory("hdmiinput")
add_subdirectory("hdmioutput")
add_subdirectory("indicator")
add_subdirectory("sensor")
add_subdirectory("videodecoder")
add_subdirectory("bootreason")
add_subdirectory("audiosink")
add_subdirectory("audiodecoder")
add_subdirectory("audiomixer")
add_subdirectory("avbuffer")
add_subdirectory("panel")
add_subdirectory("planecontrol")
add_subdirectory("videosink")
add_subdirectory("ringbuffer")
add_subdirectory("broadcast")
