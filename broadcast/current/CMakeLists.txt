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

# TODO: `demux` module is still referecing Android related code and IBroadcastManager relays on `demux`
message(FATAL_ERROR "`Broadcast` module is not ready yet. Do not use it!")

project(Broadcast
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `broadcast` depends on
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/broadcast)

set(SRC
	${SRC_DIR}/IBroadcastManager.aidl
	${SRC_DIR}/frontend/AtscCapabilities.aidl
	${SRC_DIR}/frontend/AtscTuneParameters.aidl
	${SRC_DIR}/frontend/Bandwidth.aidl
	${SRC_DIR}/frontend/Capabilities.aidl
	${SRC_DIR}/frontend/CodingRate.aidl
	${SRC_DIR}/frontend/DvbCAnnex.aidl
	${SRC_DIR}/frontend/DvbCCapabilities.aidl
	${SRC_DIR}/frontend/DvbCTuneParameters.aidl
	${SRC_DIR}/frontend/DvbTCapabilities.aidl
	${SRC_DIR}/frontend/DvbTStandard.aidl
	${SRC_DIR}/frontend/DvbTTuneParameters.aidl
	${SRC_DIR}/frontend/FrontendType.aidl
	${SRC_DIR}/frontend/GuardInterval.aidl
	${SRC_DIR}/frontend/IFrontend.aidl
	${SRC_DIR}/frontend/IFrontendController.aidl
	${SRC_DIR}/frontend/IFrontendControllerListener.aidl
	${SRC_DIR}/frontend/IFrontendListener.aidl
	${SRC_DIR}/frontend/Modulation.aidl
	${SRC_DIR}/frontend/SignalInfoProperty.aidl
	${SRC_DIR}/frontend/SignalInfoValue.aidl
	${SRC_DIR}/frontend/State.aidl
	${SRC_DIR}/frontend/TransmissionMode.aidl
	${SRC_DIR}/frontend/TuneParameters.aidl
	${SRC_DIR}/frontend/TuneStatus.aidl
	${SRC_DIR}/demux/DataPacket.aidl
	${SRC_DIR}/demux/DemuxFilterParameters.aidl
	${SRC_DIR}/demux/FilterType.aidl
	${SRC_DIR}/demux/IDemux.aidl
	${SRC_DIR}/demux/IFilter.aidl
	${SRC_DIR}/demux/ISoftwareSinkListener.aidl
	${SRC_DIR}/demux/Mpeg2TsDemuxFilterParameters.aidl
	${SRC_DIR}/demux/SoftwareSink.aidl
	${SRC_DIR}/demux/SoftwareSource.aidl
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
