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

project(AudioSink
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `audiosink` depends on
set(AUDIO_DECODER_VERSION "current")
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/audiosink)
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)
set(AUDIO_DECODER_SRC_DIR ${AUDIO_DECODER_MODULE_PATH}/${AUDIO_DECODER_VERSION}/com/rdk/hal/audiodecoder)

set(SRC
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/ContentType.aidl
	${SRC_DIR}/ErrorCode.aidl
	${SRC_DIR}/IAudioSink.aidl
	${SRC_DIR}/IAudioSinkController.aidl
	${SRC_DIR}/IAudioSinkControllerListener.aidl
	${SRC_DIR}/IAudioSinkEventListener.aidl
	${SRC_DIR}/IAudioSinkManager.aidl
	${SRC_DIR}/PlatformCapabilities.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/Volume.aidl
	${SRC_DIR}/VolumeRamp.aidl
	${AUDIO_DECODER_SRC_DIR}/FrameMetadata.aidl
	${AUDIO_DECODER_SRC_DIR}/Codec.aidl
	${COMMON_SRC_DIR}/PropertyValue.aidl	#TODO: Remove common fields.
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
