cmake_minimum_required(VERSION 3.8)

# TODO: `demux` module is still referecing Android related code and IBroadcastManager relays on `demux`
message(FATAL_ERROR "`Broadcast` module is not ready yet. Do not use it!")

project(Broadcast
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `broadcast` depends on
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/broadcast)

set(SRC
	${SRC_DIR}/IBroadcastManager.aidl
	${SRC_DIR}/frontend/AtscCapabilities.aidl
	${SRC_DIR}/frontend/AtscTuneParameters.aidl
	${SRC_DIR}/frontend/Bandwidth.aidl
	${SRC_DIR}/frontend/Capabilities.aidl
	${SRC_DIR}/frontend/CodingRate.aidl
	${SRC_DIR}/frontend/DvbCAnnex.aidl
	${SRC_DIR}/frontend/DvbCCapabilities.aidl
	${SRC_DIR}/frontend/DvbCTuneParameters.aidl
	${SRC_DIR}/frontend/DvbTCapabilities.aidl
	${SRC_DIR}/frontend/DvbTStandard.aidl
	${SRC_DIR}/frontend/DvbTTuneParameters.aidl
	${SRC_DIR}/frontend/FrontendType.aidl
	${SRC_DIR}/frontend/GuardInterval.aidl
	${SRC_DIR}/frontend/IFrontend.aidl
	${SRC_DIR}/frontend/IFrontendController.aidl
	${SRC_DIR}/frontend/IFrontendControllerListener.aidl
	${SRC_DIR}/frontend/IFrontendListener.aidl
	${SRC_DIR}/frontend/Modulation.aidl
	${SRC_DIR}/frontend/SignalInfoProperty.aidl
	${SRC_DIR}/frontend/SignalInfoValue.aidl
	${SRC_DIR}/frontend/TransmissionMode.aidl
	${SRC_DIR}/frontend/TuneParameters.aidl
	${SRC_DIR}/frontend/TuneStatus.aidl
	${SRC_DIR}/demux/DataPacket.aidl
	${SRC_DIR}/demux/DemuxFilterParameters.aidl
	${SRC_DIR}/demux/FilterType.aidl
	${SRC_DIR}/demux/IDemux.aidl
	${SRC_DIR}/demux/IFilter.aidl
	${SRC_DIR}/demux/ISoftwareSinkListener.aidl
	${SRC_DIR}/demux/Mpeg2TsDemuxFilterParameters.aidl
	${SRC_DIR}/demux/SoftwareSink.aidl
	${SRC_DIR}/demux/SoftwareSource.aidl
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
