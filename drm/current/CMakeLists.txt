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

project(Drm
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

set(SRC_DIR com/rdk/hal/drm)

set(SRC
	${SRC_DIR}/CryptoSchemes.aidl
	${SRC_DIR}/DecryptArgs.aidl
	${SRC_DIR}/DrmErrors.aidl
	${SRC_DIR}/DrmMetric.aidl
	${SRC_DIR}/DrmMetricGroup.aidl
	${SRC_DIR}/DrmMetricNamedValue.aidl
	${SRC_DIR}/DrmMetricValue.aidl
	${SRC_DIR}/EventType.aidl
	${SRC_DIR}/HdcpLevel.aidl
	${SRC_DIR}/HdcpLevels.aidl
	${SRC_DIR}/ICryptoPlugin.aidl
	${SRC_DIR}/IDrmFactory.aidl
	${SRC_DIR}/IDrmPlugin.aidl
	${SRC_DIR}/IDrmPluginListener.aidl
	${SRC_DIR}/KeyRequest.aidl
	${SRC_DIR}/KeyRequestType.aidl
	${SRC_DIR}/KeySetId.aidl
	${SRC_DIR}/KeyStatus.aidl
	${SRC_DIR}/KeyStatusType.aidl
	${SRC_DIR}/KeyType.aidl
	${SRC_DIR}/KeyValue.aidl
	${SRC_DIR}/Mode.aidl
	${SRC_DIR}/NumberOfSessions.aidl
	${SRC_DIR}/Pattern.aidl
	${SRC_DIR}/ProvideProvisionResponseResult.aidl
	${SRC_DIR}/ProvisionRequest.aidl
	${SRC_DIR}/SecurityLevel.aidl
	${SRC_DIR}/Status.aidl
	${SRC_DIR}/SubSample.aidl
	${SRC_DIR}/SupportedContentType.aidl
	${SRC_DIR}/Uuid.aidl
)

set(INCLUDE_DIRECTORY
	.
)

set(COMPILE_AIDL_ARGV "")

if (DEFINED AIDL_GEN_DIR)
	list(APPEND COMPILE_AIDL_ARGV TARGET_DIRECTORY ${AIDL_GEN_DIR})
endif()

compile_aidl(${SRC}
	INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY}
	${COMPILE_AIDL_ARGV}
)
