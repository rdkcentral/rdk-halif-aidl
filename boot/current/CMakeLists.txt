cmake_minimum_required(VERSION 3.8)

project(Boot
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

set(SRC_DIR com/rdk/hal/boot)

set(SRC
	${SRC_DIR}/BootReason.aidl
	${SRC_DIR}/Capabilities.aidl
	${SRC_DIR}/IBoot.aidl
	${SRC_DIR}/PowerSource.aidl
	${SRC_DIR}/ResetType.aidl
)

set(INCLUDE_FLAGS
	-I.
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
