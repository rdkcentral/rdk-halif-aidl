cmake_minimum_required(VERSION 3.8)
project(CryptoEngine LANGUAGES NONE VERSION 1.0)

if (NOT COMMAND compile_aidl)
    message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

set(SRC_DIR com/rdk/hal/cryptoengine)

set(SRC
    ${SRC_DIR}/ICryptoEngine.aidl
    ${SRC_DIR}/ICryptoEngineController.aidl
    ${SRC_DIR}/ICryptoOperation.aidl
    ${SRC_DIR}/CryptoConfig.aidl
    ${SRC_DIR}/EngineCapabilities.aidl
    ${SRC_DIR}/Algorithm.aidl
    ${SRC_DIR}/BlockMode.aidl
    ${SRC_DIR}/Digest.aidl
    ${SRC_DIR}/EcCurve.aidl
    ${SRC_DIR}/KeyDerivation.aidl
    ${SRC_DIR}/KeyPurpose.aidl
    ${SRC_DIR}/KeyType.aidl
    ${SRC_DIR}/PaddingMode.aidl
    ${SRC_DIR}/SecurityLevel.aidl
)

set(INCLUDE_DIRECTORY
    .
)

compile_aidl(${SRC} INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY})
