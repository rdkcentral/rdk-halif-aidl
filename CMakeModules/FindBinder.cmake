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
include(CMakeFindDependencyMacro)

find_dependency(AndroidUtils REQUIRED)

# First try pkg-config
find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_check_modules(PC_Binder QUIET binder)
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
    set(Binder_COMPILE_OPTIONS ${PC_Binder_CFLAGS_OTHER})
    set(Binder_LINK_OPTIONS ${PC_Binder_LDFLAGS_OTHER})
endif()

# Lastly, modern target-style
if(Binder_FOUND AND NOT TARGET Binder::Binder)
    add_library(Binder::Binder UNKNOWN IMPORTED)
    set_target_properties(
        Binder::Binder PROPERTIES
        IMPORTED_LOCATION "${Binder_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${Binder_INCLUDE_DIR}"
        INTERFACE_COMPILE_OPTIONS "${Binder_COMPILE_OPTIONS}"
        INTERFACE_LINK_LIBRARIES "AndroidUtils::AndroidUtils"
        INTERFACE_LINK_OPTIONS "${Binder_LINK_OPTIONS}"
    )
endif()
