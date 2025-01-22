# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright (C) 2024 Sky
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *

# **@brief
# * The cmake is used to build the Android aidl compiler module (aidl generator tool)
# * for host machine.
# *

cmake_minimum_required (VERSION 3.8)

set(PACKAGE_NAME          "aidl-generator-tool")
set(PACKAGE_VERSION       "1.0.0")
set(ANDROID_VERSION       "android-13.0.0_r74")
set(PACKAGE_STRING        "${PACKAGE_NAME} ${PACKAGE_VERSION}")

project(${PACKAGE_NAME} LANGUAGES C CXX)

find_package(PkgConfig)

project (aidl-compiler)

###########################################################
# Set build environment flags
###########################################################
if (NOT DEFINED CMAKE_C_COMPILER)
    message("Set GCC Compiler")
    set(CMAKE_C_COMPILER gcc)
endif ()

if (NOT DEFINED CMAKE_CXX_COMPILER)
    message("Set G++ Compiler")
    set(CMAKE_CXX_COMPILER g++)
endif ()

if (NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
    message("Set PIC Option")
    set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
endif ()

###########################################################
# Set all the variables
###########################################################
if (NOT DEFINED CMAKE_INSTALL_LIBDIR)
    message("Set and create cmake install lib directory")
    set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_LIBDIR})
    message("cmake install lib dir ${CMAKE_INSTALL_LIBDIR}")
endif ()

if (NOT DEFINED CMAKE_INSTALL_BINDIR)
    message("Set and create cmake install bin directory")
    set(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_BINDIR})
    message("cmake install bin dir ${CMAKE_INSTALL_BINDIR}")
endif ()

if (NOT DEFINED CMAKE_INSTALL_INCDIR)
    message("Set and create cmake install include directory")
    set(CMAKE_INSTALL_INCDIR ${CMAKE_INSTALL_PREFIX}/include)
    file(MAKE_DIRECTORY ${CMAKE_INSTALL_INCDIR})
    message("cmake install header dir ${CMAKE_INSTALL_INCDIR}")
endif ()

###########################################################
# Set all the path variables
###########################################################
set(ANDROID_DIR "${CMAKE_SOURCE_DIR}/../android")

set(ANDOIRD_LOGGING_DIR ${ANDROID_DIR}/logging)
set(ANDROID_BASE_DIR ${ANDROID_DIR}/libbase)
set(ANDROID_CORE_DIR ${ANDROID_DIR}/core)
set(ANDROID_FMTLIB_DIR ${ANDROID_DIR}/fmtlib)
set(ANDROID_AIDL_TOOL_DIR ${ANDROID_DIR}/aidl)
set(ANDROID_BUILD_TOOLS_DIR ${ANDROID_DIR}/build-tools/linux-x86)

set(LIBLOG_DIR ${ANDOIRD_LOGGING_DIR}/liblog)
set(LIBBASE_DIR ${ANDROID_BASE_DIR})
set(LIBCUTILS_DIR ${ANDROID_CORE_DIR}/libcutils)
set(LIBFMT_DIR ${ANDROID_FMTLIB_DIR})
set(LIBPROCESSGROUP_DIR ${ANDROID_CORE_DIR}/libprocessgroup)
set(LIBGTEST_DIR ${ANDROID_DIR}/googletest/googletest)
set(AIDL_DIR ${ANDROID_AIDL_TOOL_DIR})

set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

###########################################################
# Android liblog
###########################################################

set(LIBLOG_SRCS
    ${LIBLOG_DIR}/log_event_list.cpp
    ${LIBLOG_DIR}/log_event_write.cpp
    ${LIBLOG_DIR}/logger_name.cpp
    ${LIBLOG_DIR}/logger_read.cpp
    ${LIBLOG_DIR}/logger_write.cpp
    ${LIBLOG_DIR}/logprint.cpp
    ${LIBLOG_DIR}/properties.cpp
)

add_library(log STATIC ${LIBLOG_SRCS})

target_compile_options(log PRIVATE
    -Wall -Wextra -std=c++17 -D__linux__ -DLIBLOG_LOG_TAG=1006 -DSNET_EVENT_LOG_TAG=1397638484 -DANDROID_DEBUGGABLE=0
)

target_include_directories(log PRIVATE
    ${LIBLOG_DIR}/include
)

###########################################################
# Android libbase
###########################################################

set(LIBBASE_SRCS
    ${LIBBASE_DIR}/abi_compatibility.cpp
    ${LIBBASE_DIR}/chrono_utils.cpp
    ${LIBBASE_DIR}/cmsg.cpp
    ${LIBBASE_DIR}/file.cpp
    ${LIBBASE_DIR}/hex.cpp
    ${LIBBASE_DIR}/logging.cpp
    ${LIBBASE_DIR}/mapped_file.cpp
    ${LIBBASE_DIR}/parsebool.cpp
    ${LIBBASE_DIR}/parsenetaddress.cpp
    ${LIBBASE_DIR}/posix_strerror_r.cpp
    ${LIBBASE_DIR}/process.cpp
    ${LIBBASE_DIR}/properties.cpp
    ${LIBBASE_DIR}/stringprintf.cpp
    ${LIBBASE_DIR}/strings.cpp
    ${LIBBASE_DIR}/threads.cpp
    ${LIBBASE_DIR}/test_utils.cpp
    ${LIBBASE_DIR}/errors_unix.cpp
)

add_library(base STATIC ${LIBBASE_SRCS})

target_compile_options(base PRIVATE
    -Wall -Wextra -std=c++17 -D__linux__ -D_XOPEN_SOURCE=600 -D_FILE_OFFSET_BITS=64
)

target_include_directories(base PRIVATE
    ${LIBBASE_DIR}/include
    ${LIBLOG_DIR}/include
    ${LIBFMT_DIR}/include
)

target_link_libraries(base PRIVATE log)

###########################################################
# Android libcutils_sockets
###########################################################

set(LIBCUTILS_SOCKETS_SRCS
    ${LIBCUTILS_DIR}/sockets.cpp
    ${LIBCUTILS_DIR}/socket_inaddr_any_server_unix.cpp
    ${LIBCUTILS_DIR}/socket_local_client_unix.cpp
    ${LIBCUTILS_DIR}/socket_local_server_unix.cpp
    ${LIBCUTILS_DIR}/socket_network_client_unix.cpp
    ${LIBCUTILS_DIR}/sockets_unix.cpp
)

add_library(cutils_sockets STATIC ${LIBCUTILS_SOCKETS_SRCS})

target_include_directories(cutils_sockets PRIVATE
    ${LIBCUTILS_DIR}/include
)

target_compile_options(cutils_sockets PRIVATE
    -Wall -Wextra -std=c++17 -D__linux__
)

target_link_libraries(cutils_sockets PRIVATE log)

###########################################################
# Android libcutils
###########################################################

#project(cutils)

set(LIBCUTILS_SRCS
    ${LIBCUTILS_DIR}/socket_inaddr_any_server_unix.cpp
    ${LIBCUTILS_DIR}/socket_local_client_unix.cpp
    ${LIBCUTILS_DIR}/socket_local_server_unix.cpp
    ${LIBCUTILS_DIR}/socket_network_client_unix.cpp
    ${LIBCUTILS_DIR}/sockets_unix.cpp
    ${LIBCUTILS_DIR}/ashmem-host.cpp
    ${LIBCUTILS_DIR}/fs_config.cpp
    ${LIBCUTILS_DIR}/trace-host.cpp
    ${LIBCUTILS_DIR}/config_utils.cpp
    ${LIBCUTILS_DIR}/canned_fs_config.cpp
    ${LIBCUTILS_DIR}/iosched_policy.cpp
    ${LIBCUTILS_DIR}/load_file.cpp
    ${LIBCUTILS_DIR}/native_handle.cpp
    ${LIBCUTILS_DIR}/properties.cpp
    ${LIBCUTILS_DIR}/record_stream.cpp
    ${LIBCUTILS_DIR}/strlcpy.c
    ${LIBCUTILS_DIR}/threads.cpp
    ${LIBCUTILS_DIR}/fs.cpp
    ${LIBCUTILS_DIR}/hashmap.cpp
    ${LIBCUTILS_DIR}/multiuser.cpp
    ${LIBCUTILS_DIR}/str_parms.cpp
)

add_library(cutils STATIC ${LIBCUTILS_SRCS})

target_compile_options(cutils PRIVATE
    -Wall -Wextra -std=c++17 -D__linux__ -Wno-psabi
)

target_include_directories(cutils PRIVATE
    ${LIBCUTILS_DIR}/include
    ${LIBLOG_DIR}/include
    ${LIBBASE_DIR}/include
    ${LIBPROCESSGROUP_DIR}/include
)

target_link_libraries(cutils PRIVATE log base cutils_sockets dl)

###########################################################
# Android AIDL generator
###########################################################

message("Build aidl compiler")

# Android FMT
add_library(fmt STATIC ${LIBFMT_DIR}/src/format.cc)

target_include_directories(fmt PRIVATE
    ${LIBFMT_DIR}/include
)

target_compile_options(fmt PRIVATE
    "-fno-exceptions"
    "-UNDEBUG"
)

# Android GTEST
add_library(gtest STATIC ${LIBGTEST_DIR}/src/gtest-all.cc)

target_include_directories(gtest PRIVATE
    ${LIBGTEST_DIR}
    ${LIBGTEST_DIR}/include
)

target_link_libraries(gtest PRIVATE pthread)

find_package(FLEX)
find_package(BISON)

set(FLEX_FOUND "True")
set(FLEX_EXECUTABLE "/usr/bin/flex")

set(FLEX_OUT "${GENERATED_DIR}/aidl_language_l.cpp")
set(FLEX_SRC "${AIDL_DIR}/aidl_language_l.ll")

FLEX_TARGET(lexer ${FLEX_SRC} ${FLEX_OUT})

set(BISON_FOUND "True")
set(BISON_EXECUTABLE "${ANDROID_BUILD_TOOLS_DIR}/bin/bison")

set(BISON_OUT       "${GENERATED_DIR}/aidl_language_y.cpp")
set(BISON_DEFINES   "${GENERATED_DIR}/aidl_language_y.h")
set(BISON_SRC       "${AIDL_DIR}/aidl_language_y.yy")

BISON_TARGET(parser ${BISON_SRC} ${BISON_OUT}
    COMPILE_FLAGS   "-d"
    DEFINES_FILE    ${BISON_DEFINES}
)

set(AIDL_COMMON_SRCS
    ${AIDL_DIR}/aidl_checkapi.cpp
    ${AIDL_DIR}/aidl_const_expressions.cpp
    ${AIDL_DIR}/aidl_dumpapi.cpp
    ${AIDL_DIR}/aidl_language.cpp
    ${AIDL_DIR}/aidl_to_cpp_common.cpp
    ${AIDL_DIR}/aidl_to_cpp.cpp
    ${AIDL_DIR}/aidl_to_java.cpp
    ${AIDL_DIR}/aidl_to_ndk.cpp
    ${AIDL_DIR}/aidl_to_rust.cpp
    ${AIDL_DIR}/aidl_typenames.cpp
    ${AIDL_DIR}/aidl.cpp
    ${AIDL_DIR}/ast_java.cpp
    ${AIDL_DIR}/check_valid.cpp
    ${AIDL_DIR}/code_writer.cpp
    ${AIDL_DIR}/comments.cpp
    ${AIDL_DIR}/diagnostics.cpp
    ${AIDL_DIR}/generate_aidl_mappings.cpp
    ${AIDL_DIR}/generate_cpp.cpp
    ${AIDL_DIR}/generate_java_binder.cpp
    ${AIDL_DIR}/generate_java.cpp
    ${AIDL_DIR}/generate_ndk.cpp
    ${AIDL_DIR}/generate_rust.cpp
    ${AIDL_DIR}/import_resolver.cpp
    ${AIDL_DIR}/io_delegate.cpp
    ${AIDL_DIR}/location.cpp
    ${AIDL_DIR}/logging.cpp
    ${AIDL_DIR}/options.cpp
    ${AIDL_DIR}/parser.cpp
    ${AIDL_DIR}/permission.cpp
    ${AIDL_DIR}/preprocess.cpp
)

add_library(aidl-common STATIC
    ${AIDL_COMMON_SRCS}
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS})

target_include_directories(aidl-common PRIVATE
    ${AIDL_DIR}
    ${LIBLOG_DIR}/include
    ${LIBBASE_DIR}/include
    ${LIBFMT_DIR}/include
    ${LIBGTEST_DIR}/include
    ${GENERATED_DIR}
)

target_compile_options(aidl-common PRIVATE
    -O0 -g -fpermissive -Wall -Wextra -std=c++17 -D__linux__
)

target_link_libraries(aidl-common PRIVATE
    base
    cutils
    gtest
    fmt
)

add_executable(aidl ${AIDL_DIR}/main.cpp)

target_include_directories(aidl PRIVATE
    ${AIDL_DIR}
    ${LIBLOG_DIR}/include
    ${LIBBASE_DIR}/include
    ${LIBFMT_DIR}/include
)

target_compile_options(aidl PRIVATE
    -O0 -g -fpermissive -Wall -Wextra -std=c++17 -D__linux__
)

target_link_libraries(aidl PRIVATE
    aidl-common
    base
    log
)

###########################################################
# Install the binary
###########################################################
install(
    TARGETS
    aidl

    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
