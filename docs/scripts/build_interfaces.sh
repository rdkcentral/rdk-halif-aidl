#!/usr/bin/env bash
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2025 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#** ******************************************************************************
#
# This script is used to build the interfaces during the interface creation
# Once the top level cmakefile list is corrected, the usefulness of this script may disappear

MY_PATH="$(realpath ${BASH_SOURCE[0]})"
MY_DIR="$(dirname ${MY_PATH})"

if [ -z $VERSION ]; then
    VERSION=current
fi
OUTPUT_DIR=${MY_DIR}/gen

cd ../../
# A/V 
cmake -DAIDL_TARGET=audiodecoder -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=audiosink -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=avbuffer -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=avclock -DAIDL_SRC_VERSION=${VERSION} .
# ##cmake -DAIDL_TARGET=avmixer -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=videodecoder -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=videosink -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=boot -DAIDL_SRC_VERSION=${VERSION} .

# Other
# #cmake -DAIDL_TARGET=broadcast -DAIDL_SRC_VERSION=${VERSION} .
# #cmake -DAIDL_TARGET=cdm -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=cec -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=deepsleep -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=deviceinfo -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=flash -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=hdmiinput -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=hdmioutput -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=indicator -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=panel -DAIDL_SRC_VERSION=${VERSION} .
cmake -DAIDL_TARGET=planecontrol -DAIDL_SRC_VERSION=${VERSION} .



