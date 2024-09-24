cmake_minimum_required(VERSION 3.8)

project(Panel
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `panel` depends on
set(COMMON_VERSION "current")
set(VIDEO_DECODER_VERSION "current")

set(SRC_DIR com/rdk/hal/panel)

set(SRC
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/IFactoryPanel.aidl
	${SRC_DIR}/IPanelOutput.aidl
	${SRC_DIR}/IPanelOutputListener.aidl
	${SRC_DIR}/PanelType.aidl
	${SRC_DIR}/PictureModeConfiguration.aidl
	${SRC_DIR}/PQParameter.aidl
	${SRC_DIR}/PQParameterCapabilities.aidl
	${SRC_DIR}/PQParameterConfiguration.aidl
	${SRC_DIR}/WhiteBalance2PointSettings.aidl
	${SRC_DIR}/WhiteBalanceMultiPointSettings.aidl
	../../common/${COMMON_VERSION}/com/rdk/hal/AVSource.aidl
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
