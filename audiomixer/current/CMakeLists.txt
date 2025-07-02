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
# *     http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************

cmake_minimum_required(VERSION 3.8)

project(AudioMixer
    LANGUAGES NONE
    VERSION 1.0)

if (NOT COMMAND compile_aidl)
    message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# Versioned dependency modules
set(AUDIO_DECODER_VERSION "current")
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/audiomixer)
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)
set(AUDIO_DECODER_SRC_DIR ${AUDIO_DECODER_MODULE_PATH}/${AUDIO_DECODER_VERSION}/com/rdk/hal/audiodecoder)

set(SRC
    ${SRC_DIR}/Capabilities.aidl
    ${SRC_DIR}/Input.aidl
    ${SRC_DIR}/ContentType.aidl
    ${SRC_DIR}/IAudioMixer.aidl
    ${SRC_DIR}/IAudioMixerController.aidl
    ${SRC_DIR}/IAudioMixerControllerListener.aidl
    ${SRC_DIR}/IAudioMixerManager.aidl
    ${SRC_DIR}/IAQProcessor.aidl
    ${SRC_DIR}/AQParameter.aidl
    ${SRC_DIR}/IAudioOutputPort.aidl
    ${SRC_DIR}/OutputPortCapabilities.aidl
    ${SRC_DIR}/OutputFormat.aidl
    ${SRC_DIR}/IAudioOutputPortListener.aidl
    ${SRC_DIR}/MixingMode.aidl
    # Add more as you introduce new types
    ${AUDIO_DECODER_SRC_DIR}/Codec.aidl
    # Add other dependencies (e.g., Volume, State) as needed
)

set(INCLUDE_DIRECTORY
    .
    ${COMMON_MODULE_PATH}/${COMMON_VERSION}
    ${AUDIO_DECODER_MODULE_PATH}/${AUDIO_DECODER_VERSION}
)

set(COMPILE_AIDL_ARGV "")

if (DEFINED AIDL_GEN_DIR)
    list(APPEND COMPILE_AIDL_ARGV TARGET_DIRECTORY ${AIDL_GEN_DIR})
endif()

if (DEFINED AIDL_BIN)
    list(APPEND COMPILE_AIDL_ARGV AIDL_BIN ${AIDL_BIN})
endif()

compile_aidl(${SRC}
    INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY}
    ${COMPILE_AIDL_ARGV}
)
