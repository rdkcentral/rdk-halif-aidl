cmake_minimum_required(VERSION 3.8)

project(VideoDecoder
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `videodecoder` depends on
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/videodecoder)
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)

set(SRC
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/Codec.aidl
	${SRC_DIR}/CodecCapabilities.aidl
	${SRC_DIR}/CodecLevel.aidl
	${SRC_DIR}/CodecProfile.aidl
	${SRC_DIR}/CSDVideoFormat.aidl
	${SRC_DIR}/DynamicRange.aidl
	${SRC_DIR}/ErrorCode.aidl
	${SRC_DIR}/FrameMetadata.aidl
	${SRC_DIR}/IVideoDecoder.aidl
	${SRC_DIR}/IVideoDecoderController.aidl
	${SRC_DIR}/IVideoDecoderControllerListener.aidl
	${SRC_DIR}/IVideoDecoderEventListener.aidl
	${SRC_DIR}/IVideoDecoderManager.aidl
	${SRC_DIR}/OperationalMode.aidl
	${SRC_DIR}/PixelFormat.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/PropertyKVPair.aidl
	${SRC_DIR}/ScanType.aidl
	${COMMON_SRC_DIR}/PropertyValue.aidl
	${COMMON_SRC_DIR}/AVSource.aidl
	${COMMON_SRC_DIR}/State.aidl
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
