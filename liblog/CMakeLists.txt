#/**
# * Copyright 2024 Comcast Cable Communications Management, LLC
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
# * SPDX-License-Identifier: Apache-2.0
# */

# **@brief
# * The cmake is used to build the Android liblog module.
# *

cmake_minimum_required (VERSION 3.8)

set(PACKAGE_NAME          "android-liblog")
set(PACKAGE_VERSION       "1.0.0")
set(ANDROID_VERSION       "android-13.0.0_r74")
set(PACKAGE_STRING        "${PACKAGE_NAME} ${PACKAGE_VERSION}")

project(${PACKAGE_NAME} LANGUAGES C CXX)

find_package(PkgConfig)

project (liblog)

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
    message("Set cmake install lib directory")
    set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
    message("cmake install lib dir ${CMAKE_INSTALL_LIBDIR}")
endif ()

if (NOT DEFINED CMAKE_INSTALL_BINDIR)
    message("Set cmake install bin directory")
    set(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
    message("cmake install bin dir ${CMAKE_INSTALL_BINDIR}")
endif ()

if (NOT DEFINED CMAKE_INSTALL_INCDIR)
    message("Set cmake install include directory")
    set(CMAKE_INSTALL_INCDIR ${CMAKE_INSTALL_PREFIX}/include)
    message("cmake install header dir ${CMAKE_INSTALL_INCDIR}")
endif ()

###########################################################
# Set all the path variables
###########################################################
set(ANDROID_DIR "${CMAKE_SOURCE_DIR}/../android")

set(ANDOIRD_LOGGING_DIR ${ANDROID_DIR}/logging)
set(LIBLOG_DIR ${ANDOIRD_LOGGING_DIR}/liblog)

###########################################################
# Android liblog
###########################################################

project(log)

set(LIBLOG_SRCS
    ${LIBLOG_DIR}/log_event_list.cpp
    ${LIBLOG_DIR}/log_event_write.cpp
    ${LIBLOG_DIR}/logger_name.cpp
    ${LIBLOG_DIR}/logger_read.cpp
    ${LIBLOG_DIR}/logger_write.cpp
    ${LIBLOG_DIR}/logprint.cpp
    ${LIBLOG_DIR}/properties.cpp
)

add_library(log SHARED ${LIBLOG_SRCS})

target_compile_options(log PRIVATE
    -Wall -Wextra -std=c++17 -D__linux__ -DLIBLOG_LOG_TAG=1006 -DSNET_EVENT_LOG_TAG=1397638484 -DANDROID_DEBUGGABLE=0
)

target_include_directories(log PRIVATE
    ${LIBLOG_DIR}/include
)

###########################################################
# Install the library
###########################################################
install(TARGETS
    log

    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

###########################################################
# Install the header files
###########################################################
set(HEADER_FILES_DIR
    ${LIBLOG_DIR}/include/android
    ${LIBLOG_DIR}/include/log
)

install(
    DIRECTORY
    ${HEADER_FILES_DIR}

    DESTINATION ${CMAKE_INSTALL_INCDIR}
    FILES_MATCHING
    PATTERN "*.h"   # Specify the pattern to match header files
)