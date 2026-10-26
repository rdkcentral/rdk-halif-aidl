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
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************
cmake_minimum_required(VERSION 3.8)

project(SensorHAL
    LANGUAGES NONE
    VERSION 1.0)

# This file is intended to be included from the repo's root CMake invocation,
# where the 'compile_aidl' macro/function is defined.
if (NOT COMMAND compile_aidl)
    message(FATAL_ERROR "Do not invoke module-level CMake directly!\nInvoke CMake at root level so 'compile_aidl' is available.")
endif()

# ---------------------------------------------------------------------------------------
# Options to enable/disable individual sensor HALs
# ---------------------------------------------------------------------------------------
option(ENABLE_SENSOR_MOTION  "Build Motion Sensor HAL AIDL"  ON)
option(ENABLE_SENSOR_THERMAL "Build Thermal Policy HAL AIDL" ON)

# ---------------------------------------------------------------------------------------
# Optional configuration (forwarded to submodules via cache vars if needed)
# - AIDL_GEN_DIR: output directory for generated sources
# - AIDL_BIN:     path to a specific aidl tool binary
# These are typically consumed by the submodule CMakeLists via COMPILE_AIDL_ARGV.
# ---------------------------------------------------------------------------------------
if (DEFINED AIDL_GEN_DIR)
    set(AIDL_GEN_DIR "${AIDL_GEN_DIR}" CACHE PATH "AIDL generated source directory")
endif()

if (DEFINED AIDL_BIN)
    set(AIDL_BIN "${AIDL_BIN}" CACHE FILEPATH "Path to the 'aidl' compiler binary")
endif()

# ---------------------------------------------------------------------------------------
# Subdirectories
# Expect layout:
#   sensor/
#     CMakeLists.txt (this file)
#     motion/CMakeLists.txt
#     thermal/CMakeLists.txt
# ---------------------------------------------------------------------------------------

# Helper to safely add subdir if enabled and present
function(_sensor_add_subdir name)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${name}/CMakeLists.txt")
        add_subdirectory("${name}")
    else()
        message(FATAL_ERROR "Expected submodule directory '${name}' not found under ${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
endfunction()

if (ENABLE_SENSOR_MOTION)
    _sensor_add_subdir(motion)
endif()

if (ENABLE_SENSOR_THERMAL)
    _sensor_add_subdir(thermal)
endif()

