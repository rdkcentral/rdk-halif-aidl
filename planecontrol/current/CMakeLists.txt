cmake_minimum_required(VERSION 3.8)

project(PlaneControl
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `planecontrol` depends on
set(COMMON_VERSION "current")
set(VIDEO_DECODER_VERSION "current")

set(SRC_DIR com/rdk/hal/planecontrol)
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)
set(VIDEO_DECODER_SRC_DIR ${VIDEO_DECODER_MODULE_PATH}/${VIDEO_DECODER_VERSION}/com/rdk/hal/videodecoder)

set(SRC
	${SRC_DIR}/AspectRatio.aidl
	${SRC_DIR}/IPlaneControl.aidl
	${SRC_DIR}/IPlaneControlListener.aidl
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/PlaneType.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/PropertyKVPair.aidl
	${SRC_DIR}/SourcePlaneMapping.aidl
	${SRC_DIR}/SourceType.aidl
	${VIDEO_DECODER_SRC_DIR}/PixelFormat.aidl
	${VIDEO_DECODER_SRC_DIR}/DynamicRange.aidl
	${COMMON_SRC_DIR}/PropertyValue.aidl
)

set(INCLUDE_DIRECTORY
	.
	${COMMON_MODULE_PATH}/${COMMON_VERSION}
	${VIDEO_DECODER_MODULE_PATH}/${VIDEO_DECODER_VERSION}
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
