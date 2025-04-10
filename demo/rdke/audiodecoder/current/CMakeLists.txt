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
	${SRC_DIR}/IAudioDecoder.aidl
	${SRC_DIR}/IAudioDecoderController.aidl
	${SRC_DIR}/IAudioDecoderControllerListener.aidl
	${SRC_DIR}/IAudioDecoderEventListener.aidl
	${SRC_DIR}/IAudioDecoderManager.aidl
	${SRC_DIR}/PCMFormat.aidl
	${SRC_DIR}/Property.aidl
	${COMMON_SRC_DIR}/State.aidl
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
