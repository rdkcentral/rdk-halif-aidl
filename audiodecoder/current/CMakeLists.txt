cmake_minimum_required(VERSION 3.8)

project(AudioDecoder
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `audiodecoder` depends on
set(COMMON_VERSION "current")

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
	../../common/${COMMON_VERSION}/com/rdk/hal/State.aidl
	../../common/${COMMON_VERSION}/com/rdk/hal/PropertyValue.aidl
	../../common/${COMMON_VERSION}/com/rdk/hal/AVSource.aidl
	../../common/${COMMON_VERSION}/com/rdk/hal/HALError.aidl
)

set(INCLUDE_FLAGS
	-I.
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
