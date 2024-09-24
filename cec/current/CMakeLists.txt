cmake_minimum_required(VERSION 3.8)

project(HdmiCec
	LANGUAGES NONE
	VERSION 1.0)

if (NOT DEFINED AIDL_BIN)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `cec` depends on
set(COMMON_VERSION "current")

set(SRC_DIR com/rdk/hal/hdmicec)

set(SRC
	${SRC_DIR}/IHdmiCec.aidl
	${SRC_DIR}/IHdmiCecController.aidl
	${SRC_DIR}/IHdmiCecControllerListener.aidl
	${SRC_DIR}/IHdmiCecEventListener.aidl
	${SRC_DIR}/Property.aidl
	${SRC_DIR}/SendMessageStatus.aidl
	../../common/${COMMON_VERSION}/com/rdk/hal/State.aidl
	../../common/${COMMON_VERSION}/com/rdk/hal/PropertyValue.aidl
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
