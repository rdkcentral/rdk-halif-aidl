cmake_minimum_required(VERSION 3.8)

project(Boot
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

set(SRC_DIR com/rdk/hal/boot)

set(SRC
	${SRC_DIR}/BootReason.aidl
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/IBoot.aidl
	${SRC_DIR}/PowerSource.aidl
	${SRC_DIR}/ResetType.aidl
)

set(INCLUDE_DIRECTORY
	.
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
