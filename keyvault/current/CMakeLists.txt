cmake_minimum_required(VERSION 3.8)
project(KeyVault LANGUAGES NONE VERSION 1.0)

if (NOT COMMAND compile_aidl)
    message(FATAL_ERROR "Do not invoke module level CMake directly!\nInvoke CMake at root level instead!")
endif()

set(CRYPTOENGINE_VERSION "current")
set(SRC_DIR com/rdk/hal/keyvault)
set(CRYPTOENGINE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../cryptoengine/${CRYPTOENGINE_VERSION}/com/rdk/hal/cryptoengine)

set(SRC
    ${SRC_DIR}/IKeyVault.aidl
    ${SRC_DIR}/IKeyVaultController.aidl
    ${SRC_DIR}/IKeyVaultEventListener.aidl
    ${SRC_DIR}/DerivedKeySpec.aidl
    ${SRC_DIR}/KeyDescriptor.aidl
    ${SRC_DIR}/VaultCapabilities.aidl
    ${SRC_DIR}/VaultState.aidl
    ${CRYPTOENGINE_SRC_DIR}/Algorithm.aidl
    ${CRYPTOENGINE_SRC_DIR}/CryptoConfig.aidl
    ${CRYPTOENGINE_SRC_DIR}/Digest.aidl
    ${CRYPTOENGINE_SRC_DIR}/ICryptoEngineController.aidl
    ${CRYPTOENGINE_SRC_DIR}/KeyType.aidl
    ${CRYPTOENGINE_SRC_DIR}/SecurityLevel.aidl
)

set(INCLUDE_DIRECTORY
    .
    ${CMAKE_CURRENT_SOURCE_DIR}/../../cryptoengine/${CRYPTOENGINE_VERSION}
)

compile_aidl(${SRC} INCLUDE_DIRECTORY ${INCLUDE_DIRECTORY})
