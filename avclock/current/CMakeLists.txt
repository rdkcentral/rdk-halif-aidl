cmake_minimum_required(VERSION 3.8)

project(AVClock
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `avclock` depends on
set(COMMON_VERSION "current")
set(AUDIO_DECODER_VERSION "current")
set(AUDIO_SINK_VERSION "current")
set(VIDEO_DECODER_VERSION "current")
set(VIDEO_SINK_VERSION "current")

set(SRC_DIR com/rdk/hal/avclock)

set(SRC
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/ClockMode.aidl
	${SRC_DIR}/ClockTime.aidl
	${SRC_DIR}/IAVClock.aidl
	${SRC_DIR}/IAVClockController.aidl
	${SRC_DIR}/IAVClockControllerListener.aidl
	${SRC_DIR}/IAVClockEventListener.aidl
	${SRC_DIR}/IAVClockManager.aidl
	${SRC_DIR}/Property.aidl
	../../common/${COMMON_VERSION}/com/rdk/hal/HALError.aidl
	../../audiosink/${AUDIO_SINK_VERSION}/com/rdk/hal/audiosink/IAudioSink.aidl
	../../videosink/${VIDEO_SINK_VERSION}/com/rdk/hal/videosink/IVideoSink.aidl
)

set(INCLUDE_FLAGS
	-I.
	-I../../audiodecoder/${AUDIO_DECODER_VERSION}
	-I../../audiosink/${AUDIO_SINK_VERSION}
	-I../../videodecoder/${VIDEO_DECODER_VERSION}
	-I../../videosink/${VIDEO_SINK_VERSION}
	-I../../common/${COMMON_VERSION}
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
