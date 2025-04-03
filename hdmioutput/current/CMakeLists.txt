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

set(INCLUDE_DIRECTORY
	.
	${COMMON_MODULE_PATH}/${COMMON_VERSION}
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

