#!/usr/bin/env bash

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

# Helper script to build intended interfaces libraries from auto generated stubs &
# proxies from defined AIDL Interfaces.
# 
# Usage:
#   ./build_interfaces.sh
#       Compiles libraries for ALL interfaces of ALL versions
#   ./build_interfaces.sh <interface_name> <versions>
#       Compiles libraries for given interfaces of given versions
#
#   interface name can be ALL or the specific interface name.
#   versions can be
#       ALL: compiles for all versions
#       CURRENT: compiles for current version
#       LATEST: compiles for latest version
#       specific version: compiles for specific version only.
#           specific version must be used only for specific interface name.
#
# Note:
#   current setup only supports below cases:
#       1. Compiling all interfaces of all versions
#       2. Compiling specific interface of specific version.

source install_binder.sh

targets=$1
version=$2

TARGET_CMAKE_DIR=`pwd`/targets/
TARGET_CMAKE_BUILD_DIR=$TARGET_CMAKE_DIR/out/

if [ -z $targets ]; then
    targets="all"
fi

if [ -z $version ]; then
    version="all"
fi

echo "Building stubs and proxies for $targets interface/s of $version version/s"

echo "CMake location for building interfaces: $TARGET_CMAKE_DIR"

cmake -S$TARGET_CMAKE_DIR -B$TARGET_CMAKE_BUILD_DIR -DINTERFACE_TARGET=$targets -DINTERFACE_VERSION=$version
cmake --build $TARGET_CMAKE_BUILD_DIR

