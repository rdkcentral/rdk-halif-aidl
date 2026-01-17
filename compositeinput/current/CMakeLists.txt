cmake_minimum_required(VERSION 3.8)
project(CompositeInput LANGUAGES NONE VERSION 1.0)

if (NOT COMMAND compile_aidl)
    message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

set(COMMON_VERSION "current")
set(SRC_DIR com/rdk/hal/compositeinput)
set(COMMON_SRC_DIR ${COMMON_MODULE_PATH}/${COMMON_VERSION}/com/rdk/hal)

set(SRC
    ${SRC_DIR}/ICompositeInputManager.aidl
    ${SRC_DIR}/ICompositeInputPort.aidl
    ${SRC_DIR}/IPortEventListener.aidl
    ${SRC_DIR}/IPortTelemetryListener.aidl
    ${SRC_DIR}/PlatformCapabilities.aidl
    ${SRC_DIR}/PortCapabilities.aidl
    ${SRC_DIR}/PortStatus.aidl
    ${SRC_DIR}/Port.aidl
    ${SRC_DIR}/SignalStatus.aidl
    ${SRC_DIR}/VideoResolution.aidl
    ${SRC_DIR}/PropertyKVPair.aidl
    ${SRC_DIR}/PropertyMetadata.aidl
    ${SRC_DIR}/PortMetrics.aidl
    ${COMMON_SRC_DIR}/PropertyValue.aidl
)

set(INCLUDE_DIRECTORY
    .
    ${COMMON_MODULE_PATH}/${COMMON_VERSION}
)

set(COMPILE_AIDL_ARGV "")
if (DEFINED AIDL_GEN_DIR)
    list(APPEND COMPILE_AIDL_ARGV TARGET_DIRECTORY ${AIDL_GEN_DIR})
endif()

compile_aidl(${SRC} INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY} ${COMPILE_AIDL_ARGV})
