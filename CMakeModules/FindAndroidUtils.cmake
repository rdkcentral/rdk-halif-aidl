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

include(FindPackageHandleStandardArgs)

# First try pkg-config
find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_check_modules(PC_AndroidUtils QUIET utils)
endif()

# Utils
find_library(
    AndroidUtils_LIBRARY
    NAMES utils
    HINTS ${PC_AndroidUtils_LIBRARY_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/out/target/lib/binder"
)
find_package_handle_standard_args(
    AndroidUtils
    REQUIRED_VARS AndroidUtils_LIBRARY
    VERSION_VAR AndroidUtils_VERSION
)

if(AndroidUtils_FOUND)
    set(AndroidUtils_LIBRARIES ${AndroidUtils_LIBRARY})
    set(AndroidUtils_DEFINITIONS ${PC_AndroidUtils_CFLAGS_OTHER})
endif()

if(AndroidUtils_FOUND AND NOT TARGET AndroidUtils::AndroidUtils)
    add_library(AndroidUtils::AndroidUtils UNKNOWN IMPORTED)
    set_target_properties(
        AndroidUtils::AndroidUtils PROPERTIES
        IMPORTED_LOCATION "${AndroidUtils_LIBRARY}"
        INTERFACE_COMPILE_DEFINITIONS "${PC_AndroidUtils_CFLAGS_OTHER}"
    )
endif()
