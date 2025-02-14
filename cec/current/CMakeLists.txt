cmake_minimum_required(VERSION 3.8)

project(HdmiCec
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `cec` depends on
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/hdmicec)
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)

set(SRC
	${SRC_DIR}/IHdmiCec.aidl
	${SRC_DIR}/IHdmiCecController.aidl
	${SRC_DIR}/IHdmiCecControllerListener.aidl
	${SRC_DIR}/IHdmiCecEventListener.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/SendMessageStatus.aidl
	${COMMON_SRC_DIR}/State.aidl
	${COMMON_SRC_DIR}/PropertyValue.aidl
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
