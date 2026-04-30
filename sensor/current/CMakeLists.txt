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
cmake_minimum_required(VERSION 3.8)

project(Sensor
    LANGUAGES NONE
    VERSION 1.0)

if (NOT COMMAND compile_aidl)
    message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# Each sensor type is independent and not present on every platform.
# Delegate to the per-sensor build, which exposes ENABLE_SENSOR_MOTION /
# ENABLE_SENSOR_THERMAL options. Platforms that do not ship a sensor type
# can disable it via -DENABLE_SENSOR_MOTION=OFF or
# -DENABLE_SENSOR_THERMAL=OFF.
add_subdirectory(com/rdk/hal/sensor)
