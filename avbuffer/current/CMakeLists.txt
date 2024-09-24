cmake_minimum_required(VERSION 3.8)

project(AVBuffer
	LANGUAGES NONE
	VERSION 1.0)

# version of other modules that `avbuffer` depends on
if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

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

set(INCLUDE_FLAGS
	-I.
	-I../../common/${COMMON_VERSION}
	-I../../audiodecoder/${AUDIO_DECODER_VERSION}
	-I../../videodecoder/${VIDEO_DECODER_VERSION}
)

foreach(SRC_FILE IN ITEMS ${SRC})
	message(STATUS "== ${SRC_FILE} ==")
	execute_process(
		COMMAND ${AIDL_BIN} ${AIDL_FLAGS} ${INCLUDE_FLAGS} ${SRC_FILE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		OUTPUT_VARIABLE OUTPUT
		ERROR_VARIABLE ERROR
		RESULT_VARIABLE RESULT
	)

	if(RESULT EQUAL 0)
		message(STATUS "Command succeeded with output:\n${OUTPUT}")
	else()
		message(WARNING "Command failed with error:\n${ERROR}")
	endif()
endforeach()
