cmake_minimum_required(VERSION 3.8)

project(HDMIInput
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `hdmiinput` depends on
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/hdmiinput)

set(SRC
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/FreeSync.aidl
	${SRC_DIR}/HDCPProtocolVersion.aidl
	${SRC_DIR}/HDCPStatus.aidl
	${SRC_DIR}/HDMIVersion.aidl
	${SRC_DIR}/IHDMIInput.aidl
	${SRC_DIR}/IHDMIInputController.aidl
	${SRC_DIR}/IHDMIInputControllerListener.aidl
	${SRC_DIR}/IHDMIInputEventListener.aidl
	${SRC_DIR}/IHDMIInputManager.aidl
	${SRC_DIR}/PlatformCapabilities.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/PropertyKVPair.aidl
	${SRC_DIR}/SignalState.aidl
	${SRC_DIR}/VIC.aidl
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
