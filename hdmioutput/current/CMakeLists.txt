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

project(HDMIOutput
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# Dependent module version
set(COMMON_VERSION "current")

# AIDL source directory
set(SRC_DIR com/rdk/hal/hdmioutput)

# AIDL source files
set(SRC
	${SRC_DIR}/AdditionalColorimetryExtension.aidl
	${SRC_DIR}/AFD.aidl
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/Colorimetry.aidl
	${SRC_DIR}/ContentType.aidl
	${SRC_DIR}/ExtendedColorimetry.aidl
	${SRC_DIR}/FreeSync.aidl
	${SRC_DIR}/HDCPProtocolVersion.aidl
	${SRC_DIR}/HDCPStatus.aidl
	${SRC_DIR}/HDMIVersion.aidl
	${SRC_DIR}/HDROutputMode.aidl
	${SRC_DIR}/IHDMIOutput.aidl
	${SRC_DIR}/IHDMIOutputController.aidl
	${SRC_DIR}/IHDMIOutputControllerListener.aidl
	${SRC_DIR}/IHDMIOutputEventListener.aidl
	${SRC_DIR}/IHDMIOutputManager.aidl
	${SRC_DIR}/PixelFormat.aidl
	${SRC_DIR}/PlatformCapabilities.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/PropertyKVPair.aidl
	${SRC_DIR}/ScanInformation.aidl
	${SRC_DIR}/SPDInfoFrame.aidl
	${SRC_DIR}/SPDSource.aidl
	${SRC_DIR}/State.aidl
	${SRC_DIR}/VIC.aidl
)

# AIDL include directories
set(INCLUDE_DIRECTORY
	.
	${COMMON_MODULE_PATH}/${COMMON_VERSION}
)

# Collect optional AIDL generator arguments
set(COMPILE_AIDL_ARGV "")

if (DEFINED AIDL_GEN_DIR)
	list(APPEND COMPILE_AIDL_ARGV TARGET_DIRECTORY ${AIDL_GEN_DIR})
endif()

if (DEFINED AIDL_BIN)
	list(APPEND COMPILE_AIDL_ARGV AIDL_BIN ${AIDL_BIN})
endif()

# Compile the AIDL interface set
compile_aidl(${SRC}
	INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY}
	${COMPILE_AIDL_ARGV}
)

