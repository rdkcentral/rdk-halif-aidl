cmake_minimum_required(VERSION 3.8)

project(HDMIOutput
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `hdmioutput` depends on
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/hdmioutput)

set(SRC
	${SRC_DIR}/AdditionalColorimetryExtension.aidl
	${SRC_DIR}/AFD.aidl
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/Colorimetry.aidl
	${SRC_DIR}/ContentType.aidl
	${SRC_DIR}/ExtendedColorimetry.aidl
	${SRC_DIR}/HDCPProtocolVersion.aidl
	${SRC_DIR}/HDCPStatus.aidl
	${SRC_DIR}/HDMIVersion.aidl
	${SRC_DIR}/HDROutputMode.aidl
	${SRC_DIR}/IHDMIOutput.aidl
	${SRC_DIR}/IHDMIOutputController.aidl
	${SRC_DIR}/IHDMIOutputControllerListener.aidl
	${SRC_DIR}/IHDMIOutputEventListener.aidl
	${SRC_DIR}/IHDMIOutputManager.aidl
	${SRC_DIR}/PixelFormat.aidl
	${SRC_DIR}/PlatformCapabilities.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/PropertyKVPair.aidl
	${SRC_DIR}/SPDInfoFrame.aidl
	${SRC_DIR}/SPDSource.aidl
	${SRC_DIR}/VIC.aidl
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
