#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
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
#** ******************************************************************************

# FindAndroidUtils — libutils from the linux_binder_idl Binder SDK.
# Same search inputs as FindBinder. Result: AndroidUtils::AndroidUtils.

include(FindPackageHandleStandardArgs)

find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(PC_AndroidUtils QUIET utils)
endif()

find_path(AndroidUtils_INCLUDE_DIR
    NAMES utils/RefBase.h
    HINTS ${PC_AndroidUtils_INCLUDE_DIRS}
          ${BINDER_SDK_INCLUDE_DIR} ENV BINDER_SDK_INCLUDE_DIR
          ${BINDER_SDK_DIR} ENV BINDER_SDK_DIR
    PATH_SUFFIXES include/binder_sdk binder_sdk include)

find_library(AndroidUtils_LIBRARY
    NAMES utils
    HINTS ${PC_AndroidUtils_LIBRARY_DIRS}
          ${BINDER_SDK_DIR} ENV BINDER_SDK_DIR
    PATH_SUFFIXES ${BINDER_SDK_LIB_SUBDIR} lib/binder lib64/binder lib lib64)

find_package_handle_standard_args(AndroidUtils
    REQUIRED_VARS AndroidUtils_LIBRARY)

if(AndroidUtils_FOUND AND NOT TARGET AndroidUtils::AndroidUtils)
    add_library(AndroidUtils::AndroidUtils UNKNOWN IMPORTED)
    set_target_properties(AndroidUtils::AndroidUtils PROPERTIES
        IMPORTED_LOCATION "${AndroidUtils_LIBRARY}"
        INTERFACE_COMPILE_OPTIONS "${PC_AndroidUtils_CFLAGS_OTHER}")
    if(AndroidUtils_INCLUDE_DIR)
        set_target_properties(AndroidUtils::AndroidUtils PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${AndroidUtils_INCLUDE_DIR}")
    endif()
endif()

mark_as_advanced(AndroidUtils_INCLUDE_DIR AndroidUtils_LIBRARY)
