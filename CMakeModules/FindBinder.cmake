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

# FindBinder — the linux_binder_idl Binder SDK (libbinder + headers).
#
# Search order: pkg-config `binder` (if a .pc is ever shipped), then the
# BINDER_SDK_DIR / BINDER_SDK_INCLUDE_DIR / BINDER_SDK_LIB_SUBDIR variables the
# existing build and Yocto recipes already pass, as variables or environment.
#
# Layouts understood:
#   <sdk>/include/binder_sdk/binder/Binder.h   <sdk>/lib/binder/libbinder.so   (build_binder.sh, linux-binder recipe)
#   <sdk>/include/binder/Binder.h              <sdk>/lib/libbinder.so          (FHS install)
#
# Result: imported target Binder::Binder (links AndroidUtils::AndroidUtils),
# plus Binder_INCLUDE_DIR / Binder_LIBRARY.

include(FindPackageHandleStandardArgs)

find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(PC_Binder QUIET binder)
endif()

find_path(Binder_INCLUDE_DIR
    NAMES binder/Binder.h
    HINTS ${PC_Binder_INCLUDE_DIRS}
          ${BINDER_SDK_INCLUDE_DIR} ENV BINDER_SDK_INCLUDE_DIR
          ${BINDER_SDK_DIR} ENV BINDER_SDK_DIR
    PATH_SUFFIXES include/binder_sdk binder_sdk include)

find_library(Binder_LIBRARY
    NAMES binder
    HINTS ${PC_Binder_LIBRARY_DIRS}
          ${BINDER_SDK_DIR} ENV BINDER_SDK_DIR
    PATH_SUFFIXES ${BINDER_SDK_LIB_SUBDIR} lib/binder lib64/binder lib lib64)

find_package_handle_standard_args(Binder
    REQUIRED_VARS Binder_LIBRARY Binder_INCLUDE_DIR)

if(Binder_FOUND)
    find_package(AndroidUtils REQUIRED)
    if(NOT TARGET Binder::Binder)
        add_library(Binder::Binder UNKNOWN IMPORTED)
        set_target_properties(Binder::Binder PROPERTIES
            IMPORTED_LOCATION "${Binder_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${Binder_INCLUDE_DIR}"
            INTERFACE_COMPILE_OPTIONS "${PC_Binder_CFLAGS_OTHER}"
            INTERFACE_LINK_LIBRARIES "AndroidUtils::AndroidUtils")
    endif()
endif()

mark_as_advanced(Binder_INCLUDE_DIR Binder_LIBRARY)
