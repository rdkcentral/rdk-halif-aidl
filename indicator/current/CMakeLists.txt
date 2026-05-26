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
cmake_minimum_required(VERSION 3.8)

# 1. Define the Interface Identity
set(INTERFACE_TARGET indicator)
set(INTERFACE_VERSION current)

# 2. Trigger the Build
# This function (from CMakeLists.inc) will:
#   a. Run 'aidl_ops -g' to generate the C++ code
#   b. Find the generated files in 'stable/generated/indicator/src/current'
#   c. Create the library target 'indicator-vcurrent-cpp'
target_build_interfaces_libraries()