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

project(Hal LANGUAGES NONE VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
include(build-tools/linux_binder_idl/host/CMakeLists.inc)

# --- 1. Define Known Modules ---
# Based on your logs, here are all the interfaces in your project
set(ALL_MODULES
    audiodecoder
    audiosink
    avbuffer
    avclock
    boot
    cec
    common
    deepsleep
    deviceinfo
    flash
    hdmiinput
    hdmioutput
    indicator
    panel
    planecontrol
    videodecoder
    videosink
)

# --- 2. Setup Variables ---
if (DEFINED AIDL_BIN)
    get_filename_component(AIDL_BIN ${AIDL_BIN} ABSOLUTE)
endif()

if (NOT DEFINED AIDL_SRC_VERSION)
    message(STATUS "AIDL_SRC_VERSION not set, defaulting to `current`")
    set(AIDL_SRC_VERSION "current")
endif()

if (NOT DEFINED AIDL_GEN_DIR)
    set(AIDL_GEN_DIR ${CMAKE_SOURCE_DIR}/gen)
endif()

# ... (Top of file remains the same) ...

# --- 3. Logic: Build ALL Available Versions ---

if ("${AIDL_SRC_VERSION}" STREQUAL "all_available")
    message(STATUS "Mode: Building ALL available versions found on disk")
    
    foreach(MODULE ${ALL_MODULES})
        set(MOD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}")
        
        # 1. Find all subdirectories in the module folder (e.g. '1', '2', 'current')
        file(GLOB CHILDREN RELATIVE ${MOD_ROOT} ${MOD_ROOT}/*)
        
        foreach(VERSION_DIR ${CHILDREN})
            if(IS_DIRECTORY "${MOD_ROOT}/${VERSION_DIR}")
                # Check if it has a CMakeLists.txt (to avoid adding 'src' or 'docs' folders)
                if(EXISTS "${MOD_ROOT}/${VERSION_DIR}/CMakeLists.txt")
                    message(STATUS "  + Adding target: ${MODULE} (Version: ${VERSION_DIR})")
                    add_subdirectory(${MODULE}/${VERSION_DIR})
                endif()
            endif()
        endforeach()
    endforeach()

# --- Fallback: Build Single Global Version (for dev_build.sh) ---
else()
    message(STATUS "Mode: Building specific global version: ${AIDL_SRC_VERSION}")
    
    foreach(MODULE ${ALL_MODULES})
        if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}/${AIDL_SRC_VERSION}/CMakeLists.txt)
            add_subdirectory(${MODULE}/${AIDL_SRC_VERSION})
        else()
             # Ideally silent skip, or warning depending on preference
        endif()
    endforeach()
endif()