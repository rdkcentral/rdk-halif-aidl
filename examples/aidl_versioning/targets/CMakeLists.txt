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

cmake_minimum_required(VERSION 3.8)

execute_process(COMMAND pwd OUTPUT_VARIABLE WORKING_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
if (DEFINED LINUX_BINDER_AIDL_ROOT)
    file(REAL_PATH ${LINUX_BINDER_AIDL_ROOT} LINUX_BINDER_AIDL_ROOT BASE_DIRECTORY ${WORKING_DIR})
else()
    file(REAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../build-tools/linux_binder_idl/" LINUX_BINDER_AIDL_ROOT BASE_DIRECTORY ${WORKING_DIR})
endif()

# Set the root directory to look for AIDL Interfaces
if (NOT DEFINED INTERFACES_ROOT_DIRS)
    file(REAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../" INTERFACES_ROOT_DIRS BASE_DIRECTORY ${WORKING_DIR})
endif()

include(${LINUX_BINDER_AIDL_ROOT}/CMakeLists.inc)

#if (NOT DEFINED INTERFACE_TARGET)
#    set(INTERFACE_TARGET "ALL")
#endif()
#
#if (NOT DEFINED INTERFACE_VERSION)
#    set (INTERFACE_VERSION "ALL")
#endif()

message(STATUS "Interface Target: ${INTERFACE_TARGET} Version: ${INTERFACE_VERSION}")

#target_build_interfaces_libraries(${INTERFACE_TARGET} ${INTERFACE_VERSION})
target_build_interfaces_libraries()
