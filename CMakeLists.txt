cmake_minimum_required(VERSION 3.8)

project(Hal
	LANGUAGES NONE
	VERSION 1.0)

if (DEFINED AIDL_BIN)
	get_filename_component(AIDL_BIN ${AIDL_BIN} ABSOLUTE)
	if (NOT EXISTS ${AIDL_BIN} OR (EXISTS ${AIDL_BIN} AND IS_DIRECTORY ${AIDL_BIN}))
		unset(AIDL_BIN CACHE)
		unset(AIDL_BIN)
	endif()
endif()

if (NOT AIDL_BIN)
	# NOTE: For some reason while using cmake in docker, the `find_program()` will always
	# locate the `aidl` file/binary at the current directory first, even '.' is not in the
	# PATH variable. The behaviour is different from outside of docker
	find_program(AIDL_BIN "aidl")
endif()

if (NOT AIDL_BIN)
	message(FATAL_ERROR "`aidl` not found")
endif()
message(STATUS "AIDL_BIN set to ${AIDL_BIN}")

if (NOT DEFINED AIDL_TARGET)
	message(FATAL_ERROR "AIDL_TARGET must be defined")
elseif (NOT IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${AIDL_TARGET})
	message(FATAL_ERROR "Module `${AIDL_TARGET}` not found")
endif()
message(STATUS "AIDL_TARGET set to ${AIDL_TARGET}")

if (NOT DEFINED AIDL_SRC_VERSION)
    message(STATUS "Setting AIDL_SRC_VERSION to `current`")
    set(AIDL_SRC_VERSION "current")
endif()
message(STATUS "AIDL_SRC_VERSION set to ${AIDL_SRC_VERSION}")

if (NOT DEFINED AIDL_GEN_DIR)
    message(STATUS "Setting AIDL_GEN_DIR to default value")
    set(AIDL_GEN_DIR ${CMAKE_SOURCE_DIR}/${AIDL_TARGET}/gen/${AIDL_SRC_VERSION})
endif()
message(STATUS "AIDL_GEN_DIR set to ${AIDL_GEN_DIR}")

set(AIDL_FLAGS
	--min_sdk_version=33
	--lang=cpp
	--structured
	--stability=vintf
	-h ${AIDL_GEN_DIR}/h
	-o ${AIDL_GEN_DIR}/cpp
)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${AIDL_TARGET}/${AIDL_SRC_VERSION}/CMakeLists.txt)
	message(FATAL_ERROR "${AIDL_TARGET} does not have version `${AIDL_SRC_VERSION}`")
endif()
add_subdirectory(${AIDL_TARGET}/${AIDL_SRC_VERSION})
