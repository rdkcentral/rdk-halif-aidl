cmake_minimum_required(VERSION 3.8)

project(Hal
	LANGUAGES NONE
	VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

include(CompileAidl)

if (DEFINED AIDL_BIN)
	get_filename_component(AIDL_BIN ${AIDL_BIN} ABSOLUTE)
	message(STATUS "AIDL_BIN set to ${AIDL_BIN}")
endif()

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

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${AIDL_TARGET}/${AIDL_SRC_VERSION}/CMakeLists.txt)
	message(FATAL_ERROR "${AIDL_TARGET} does not have version `${AIDL_SRC_VERSION}`")
endif()

set(COMMON_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(AUDIO_DECODER_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/audiodecoder)
set(AUDIO_SINK_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/audiosink)
set(VIDEO_DECODER_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/videodecoder)
set(VIDEO_SINK_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/videosink)

add_subdirectory(${AIDL_TARGET}/${AIDL_SRC_VERSION})
