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

project(Hal
	LANGUAGES NONE
	VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

include(CompileAidl)

if (DEFINED AIDL_BIN)
	get_filename_component(AIDL_BIN ${AIDL_BIN} ABSOLUTE)
	message(STATUS "AIDL_BIN set to ${AIDL_BIN}")
endif()

if (NOT DEFINED AIDL_TARGET)
	message(FATAL_ERROR "AIDL_TARGET must be defined")
elseif (NOT IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${AIDL_TARGET})
	message(FATAL_ERROR "Module `${AIDL_TARGET}` not found")
endif()
message(STATUS "AIDL_TARGET set to ${AIDL_TARGET}")

if (NOT DEFINED AIDL_SRC_VERSION)
    message(STATUS "Setting AIDL_SRC_VERSION to `current`")
    set(AIDL_SRC_VERSION "current")
endif()
message(STATUS "AIDL_SRC_VERSION set to ${AIDL_SRC_VERSION}")

if (NOT DEFINED AIDL_GEN_DIR)
    message(STATUS "Setting AIDL_GEN_DIR to default [${CMAKE_SOURCE_DIR}/gen/${AIDL_TARGET}/${AIDL_SRC_VERSION}]]")
    set(AIDL_GEN_DIR ${CMAKE_SOURCE_DIR}/gen/${AIDL_TARGET}/${AIDL_SRC_VERSION})
endif()
message(STATUS "AIDL_GEN_DIR set to ${AIDL_GEN_DIR}")

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${AIDL_TARGET}/${AIDL_SRC_VERSION}/CMakeLists.txt)
	message(FATAL_ERROR "${AIDL_TARGET} does not have version `${AIDL_SRC_VERSION}`")
endif()

set(COMMON_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(AUDIO_DECODER_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/audiodecoder)
set(AUDIO_SINK_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/audiosink)
set(AV_BUFFER_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/avbuffer)
set(AVCLOCK_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/avclock)
set(VIDEO_DECODER_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/videodecoder)
set(VIDEO_SINK_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/videosink)

add_subdirectory(${AIDL_TARGET}/${AIDL_SRC_VERSION})
