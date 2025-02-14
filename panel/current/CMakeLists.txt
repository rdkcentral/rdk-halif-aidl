cmake_minimum_required(VERSION 3.8)

project(Panel
	LANGUAGES NONE
	VERSION 1.0)

if (NOT COMMAND compile_aidl)
	message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

# version of other modules that `panel` depends on
set(COMMON_VERSION "current")
set(VIDEO_DECODER_VERSION "current")

set(SRC_DIR com/rdk/hal/panel)
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)

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
	${COMMON_SRC_DIR}/AVSource.aidl
)

set(INCLUDE_DIRECTORY
	.
	${COMMON_MODULE_PATH}/${COMMON_VERSION}
	${VIDEO_DECODER_MODULE_PATH}/${VIDEO_DECODER_VERSION}
)

set(COMPILE_AIDL_ARGV "")

if (DEFINED AIDL_GEN_DIR)
	list(APPEND COMPILE_AIDL_ARGV TARGET_DIRECTORY ${AIDL_GEN_DIR})
endif()

if (DEFINED AIDL_BIN)
	list(APPEND COMPILE_AIDL_ARGV AIDL_BIN ${AIDL_BIN})
endif()

compile_aidl(${SRC}
	INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY}
	${COMPILE_AIDL_ARGV}
)
