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

project(AVClock
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `avclock` depends on
set(COMMON_VERSION "current")
set(AUDIO_DECODER_VERSION "current")
set(AUDIO_SINK_VERSION "current")
set(VIDEO_DECODER_VERSION "current")
set(VIDEO_SINK_VERSION "current")

set(SRC_DIR com/rdk/hal/avclock)
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)
set(AUDIO_SINK_SRC_DIR ${AUDIO_SINK_MODULE_PATH}/${AUDIO_SINK_VERSION}/com/rdk/hal/audiosink)
set(VIDEO_SINK_SRC_DIR ${VIDEO_SINK_MODULE_PATH}/${VIDEO_SINK_VERSION}/com/rdk/hal/videosink)

set(SRC
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/ClockMode.aidl
	${SRC_DIR}/ClockTime.aidl
	${SRC_DIR}/IAVClock.aidl
	${SRC_DIR}/IAVClockController.aidl
	${SRC_DIR}/IAVClockControllerListener.aidl
	${SRC_DIR}/IAVClockEventListener.aidl
	${SRC_DIR}/IAVClockManager.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/State.aidl
	${AUDIO_SINK_SRC_DIR}/IAudioSink.aidl
	${VIDEO_SINK_SRC_DIR}/IVideoSink.aidl
)

set(INCLUDE_DIRECTORY
	.
	${AUDIO_DECODER_MODULE_PATH}/${AUDIO_DECODER_VERSION}
	${AUDIO_SINK_MODULE_PATH}/${AUDIO_SINK_VERSION}
	${VIDEO_DECODER_MODULE_PATH}/${VIDEO_DECODER_VERSION}
	${VIDEO_SINK_MODULE_PATH}/${VIDEO_SINK_VERSION}
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
