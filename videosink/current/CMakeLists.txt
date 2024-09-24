cmake_minimum_required(VERSION 3.8)

project(VideoSink
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `videosink` depends on
set(COMMON_VERSION "current")
set(VIDEO_DECODER_VERSION "current")

set(SRC_DIR com/rdk/hal/videosink)

set(SRC
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/IVideoSink.aidl
	${SRC_DIR}/IVideoSinkController.aidl
	${SRC_DIR}/IVideoSinkControllerListener.aidl
	${SRC_DIR}/IVideoSinkEventListener.aidl
	${SRC_DIR}/IVideoSinkManager.aidl
	${SRC_DIR}/Property.aidl
	../../videodecoder/${VIDEO_DECODER_VERSION}/com/rdk/hal/videodecoder/FrameMetadata.aidl
	../../videodecoder/${VIDEO_DECODER_VERSION}/com/rdk/hal/videodecoder/IVideoDecoder.aidl
	../../common/${COMMON_VERSION}/com/rdk/hal/PropertyValue.aidl
)

set(INCLUDE_FLAGS
	-I.
	-I../../common/${COMMON_VERSION}
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
