cmake_minimum_required(VERSION 3.8)

project(PlaneControl
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `planecontrol` depends on
set(COMMON_VERSION "current")
set(VIDEO_DECODER_VERSION "current")

set(SRC_DIR com/rdk/hal/planecontrol)

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
	../../videodecoder/${VIDEO_DECODER_VERSION}/com/rdk/hal/videodecoder/PixelFormat.aidl
	../../videodecoder/${VIDEO_DECODER_VERSION}/com/rdk/hal/videodecoder/DynamicRange.aidl
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
