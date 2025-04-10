cmake_minimum_required(VERSION 3.8)

project(AVBuffer
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `avbuffer` depends on
set(AUDIO_DECODER_VERSION "current")
set(COMMON_VERSION "current")
set(VIDEO_DECODER_VERSION "current")

set(SRC_DIR com/rdk/hal/avbuffer)

set(SRC
	${SRC_DIR}/HeapMetrics.aidl
	${SRC_DIR}/IAVBuffer.aidl
	${SRC_DIR}/IAVBufferSpaceListener.aidl
	${SRC_DIR}/Pool.aidl
	${SRC_DIR}/PoolMetrics.aidl
)

set(INCLUDE_DIRECTORY
	.
	${AUDIO_DECODER_MODULE_PATH}/${AUDIO_DECODER_VERSION}
	${VIDEO_DECODER_MODULE_PATH}/${VIDEO_DECODER_VERSION}
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
