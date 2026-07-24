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
    pkg_check_modules(PC_Binder QUIET binder)
    pkg_check_modules(PC_BinderUtils QUIET utils) # TODO: Name is too generic
endif()

# Binder
find_path(
    Binder_INCLUDE_DIR
    NAMES binder/Binder.h
    HINTS ${PC_Binder_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/out/build/include/binder_sdk"
    PATH_SUFFIXES binder
)
find_library(
    Binder_LIBRARY
    NAMES binder
    HINTS ${PC_Binder_LIBRARY_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/out/target/lib/binder"
)
find_package_handle_standard_args(
    Binder
    REQUIRED_VARS Binder_INCLUDE_DIR Binder_LIBRARY
    VERSION_VAR Binder_VERSION
)
if(Binder_FOUND)
    set(Binder_LIBRARIES ${Binder_LIBRARY})
    set(Binder_INCLUDE_DIRS ${Binder_INCLUDE_DIR})
    set(Binder_DEFINITIONS ${PC_Binder_CFLAGS_OTHER})
endif()

# Utils
find_path(
    BinderUtils_INCLUDE_DIR
    NAMES utils/misc.h
    HINTS ${PC_BinderUtils_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/out/build/include/binder_sdk"
    PATH_SUFFIXES utils
)
find_library(
    BinderUtils_LIBRARY
    NAMES utils
    HINTS ${PC_BinderUtils_LIBRARY_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/out/target/lib/binder"
)
find_package_handle_standard_args(
    BinderUtils
    REQUIRED_VARS BinderUtils_INCLUDE_DIR BinderUtils_LIBRARY
    VERSION_VAR BinderUtils_VERSION
)
if(Binder_FOUND)
    set(BinderUtils_LIBRARIES ${BinderUtils_LIBRARY})
    set(BinderUtils_INCLUDE_DIRS ${BinderUtils_INCLUDE_DIR})
    set(BinderUtils_DEFINITIONS ${PC_BinderUtils_CFLAGS_OTHER})
endif()

# Lastly, modern target-style
if(Binder_FOUND AND NOT TARGET Binder::Binder)
    add_library(Binder::Binder UNKNOWN IMPORTED)
    set_target_properties(
        Binder::Binder PROPERTIES
        IMPORTED_LOCATION "${Binder_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${Binder_INCLUDE_DIR}"
        INTERFACE_COMPILE_DEFINITIONS "${PC_Binder_CFLAGS_OTHER}"
    )
endif()
if(BinderUtils_FOUND AND NOT TARGET Binder::Utils)
    add_library(Binder::Utils UNKNOWN IMPORTED)
    set_target_properties(
        Binder::Utils PROPERTIES
        IMPORTED_LOCATION "${BinderUtils_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${BinderUtils_INCLUDE_DIR}"
        INTERFACE_COMPILE_DEFINITIONS "${PC_BinderUtils_CFLAGS_OTHER}"
    )
endif()
