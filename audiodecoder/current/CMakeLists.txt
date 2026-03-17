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

project(AudioDecoder
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `audiodecoder` depends on
set(COMMON_VERSION "current")
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)

set(SRC_DIR com/rdk/hal/audiodecoder)

set(SRC
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/ChannelType.aidl
	${SRC_DIR}/Codec.aidl
	${SRC_DIR}/CSDAudioFormat.aidl
	${SRC_DIR}/ErrorCode.aidl
	${SRC_DIR}/FrameMetadata.aidl
	${SRC_DIR}/FrameType.aidl
	${SRC_DIR}/IAudioDecoder.aidl
	${SRC_DIR}/IAudioDecoderController.aidl
	${SRC_DIR}/IAudioDecoderControllerListener.aidl
	${SRC_DIR}/IAudioDecoderEventListener.aidl
	${SRC_DIR}/IAudioDecoderManager.aidl
	${SRC_DIR}/PCMFormat.aidl
	${SRC_DIR}/PCMMetadata.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/State.aidl
	${COMMON_SRC_DIR}/PropertyValue.aidl
	${COMMON_SRC_DIR}/AVSource.aidl
	${COMMON_SRC_DIR}/HALError.aidl
)

set(INCLUDE_DIRECTORY
	.
	${COMMON_MODULE_PATH}/${COMMON_VERSION}
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
