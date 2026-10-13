#** ********************************************************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
# *
# * Copyright 2025 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
# * the License. You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
# * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
# * specific language governing permissions and * limitations under the License.
# *
#** ********************************************************************************************************************

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

function(_collect_module_dependency MODULE VERSION VISITED_IN ORDER_IN VISITED_OUT ORDER_OUT)
    set(_VISITED "${VISITED_IN}")
    set(_ORDER "${ORDER_IN}")
    set(_KEY "${MODULE}:${VERSION}")

    if(_KEY IN_LIST _VISITED)
        set(${VISITED_OUT} "${_VISITED}" PARENT_SCOPE)
        set(${ORDER_OUT} "${_ORDER}" PARENT_SCOPE)
        return()
    endif()

    foreach(_VISITED_KEY IN LISTS _VISITED)
        string(REGEX MATCH "^([^:]+):(.+)$" _ "${_VISITED_KEY}")
        if("${CMAKE_MATCH_1}" STREQUAL "${MODULE}" AND NOT "${CMAKE_MATCH_2}" STREQUAL "${VERSION}")
            message(FATAL_ERROR "Dependency graph requires multiple versions of ${MODULE}: ${CMAKE_MATCH_2} and ${VERSION}")
        endif()
    endforeach()

    list(APPEND _VISITED "${_KEY}")
    resolve_module_dependency("${PROJECT_SOURCE_DIR}/${MODULE}/${VERSION}" _DIRECT_DEPENDENCIES)
    list(LENGTH _DIRECT_DEPENDENCIES _DEPENDENCY_COUNT)
    math(EXPR _REMAINDER "${_DEPENDENCY_COUNT} % 2")
    IF(NOT _REMAINDER EQUAL 0)
        message(FATAL_ERROR "Dependencies for ${_KEY} must be module/version pairs")
    endif()

    if(_DEPENDENCY_COUNT GREATER 0)
        math(EXPR _LAST_INDEX "${_DEPENDENCY_COUNT} - 2")
        foreach(_INDEX RANGE 0 ${_LAST_INDEX} 2)
            math(EXPR _VERSION_INDEX "${_INDEX} + 1")
            list(GET _DIRECT_DEPENDENCIES ${_INDEX} _DEPENDENCY_MODULE)
            list(GET _DIRECT_DEPENDENCIES ${_VERSION_INDEX} _DEPENDENCY_VERSION)
            _collect_module_dependency(
                "${_DEPENDENCY_MODULE}" "${_DEPENDENCY_VERSION}"
                "${_VISITED}" "${_ORDER}" _VISITED _ORDER
            )
        endforeach()
    endif()

    list(APPEND _ORDER "${_KEY}")
    set(${VISITED_OUT} "${_VISITED}" PARENT_SCOPE)
    set(${ORDER_OUT} "${_ORDER}" PARENT_SCOPE)
endfunction()

function(resolve_module_dependency_order MODULE VERSION OUT_VAR)
    set(_VISITED "${MODULE}:${VERSION}")
    set(_ORDER)
    resolve_module_dependency("${PROJECT_SOURCE_DIR}/${MODULE}/${VERSION}" _DIRECT_DEPENDENCIES)
    list(LENGTH _DIRECT_DEPENDENCIES _DEPENDENCY_COUNT)
    math(EXPR _REMAINDER "${_DEPENDENCY_COUNT} % 2")
    if(NOT _REMAINDER EQUAL 0)
        message(FATAL_ERROR "Dependencies for ${MODULE}:${VERSION} must be module/version pairs")
    endif()

    if(_DEPENDENCY_COUNT GREATER 0)
        math(EXPR _LAST_INDEX "${_DEPENDENCY_COUNT} - 2")
        foreach(_INDEX RANGE 0 ${_LAST_INDEX} 2)
            math(EXPR _VERSION_INDEX "${_INDEX} + 1")
            list(GET _DIRECT_DEPENDENCIES ${_INDEX} _DEPENDENCY_MODULE)
            list(GET _DIRECT_DEPENDENCIES ${_VERSION_INDEX} _DEPENDENCY_VERSION)
            _collect_module_dependency(
                "${_DEPENDENCY_MODULE}" "${_DEPENDENCY_VERSION}"
                "${_VISITED}" "${_ORDER}" _VISITED _ORDER
            )
        endforeach()
    endif()

    set(${OUT_VAR} "${_ORDER}" PARENT_SCOPE)
endfunction()

# Uppercase the first letter of the module name.
function(_capitalize_module_name MODULE_NAME OUT_VAR)
    string(SUBSTRING "${MODULE_NAME}" 0 1 FIRST_LETTER)
    string(TOUPPER "${FIRST_LETTER}" FIRST_LETTER)
    string(REGEX REPLACE "^.(.*)" "${FIRST_LETTER}\\1" MODULE_NAME "${MODULE_NAME}")
    set(${OUT_VAR} "${MODULE_NAME}" PARENT_SCOPE)
endfunction()

# Transforms the dependencies into different formats. Takes a list of dependency-version pairs as arguments.
function(_generate_dependency_list CMAKE_STYLE_OUT PKG_CONFIG_STYLE_OUT LIB_NAMES_OUT FIND_DEPS_OUT)
    set(CMAKE_STYLE "Binder::Binder")
    set(PKG_CONFIG_STYLE "binder")
    set(LIB_NAMES "libbinder")
    set(FIND_DEPS "find_dependency(Binder)")

    math(EXPR remainder "(${ARGC} - 4) % 2")
    if(NOT remainder EQUAL 0)
        message(FATAL_ERROR "_generate_dependency_list expects dependency-version pairs, but got an odd number of args")
    endif()
    foreach(dep RANGE 4 "${ARGC}" 2)
        if(${dep} EQUAL ${ARGC})
            break()
        endif()

        math(EXPR dep_ver_index "${dep} + 1")

        list(APPEND PKG_CONFIG_STYLE "rdk-halif-aidl-${ARGV${dep}} = ${ARGV${dep_ver_index}}")
        list(APPEND LIB_NAMES "${ARGV${dep}}-v${ARGV${dep_ver_index}}-cpp")
        _capitalize_module_name("${ARGV${dep}}" _DEP_CAP)
        list(APPEND CMAKE_STYLE "RdkHalifAidl::${_DEP_CAP}")
        list(APPEND FIND_DEPS "find_dependency(RdkHalifAidl${_DEP_CAP})")
    endforeach()

    message(DEBUG "CMake style dependencies: ${CMAKE_STYLE}")
    message(DEBUG "Pkg-config style dependencies: ${PKG_CONFIG_STYLE}")
    message(DEBUG "Library names: ${LIB_NAMES}")

    set(${CMAKE_STYLE_OUT} "${CMAKE_STYLE}" PARENT_SCOPE)
    set(${PKG_CONFIG_STYLE_OUT} "${PKG_CONFIG_STYLE}" PARENT_SCOPE)
    set(${LIB_NAMES_OUT} "${LIB_NAMES}" PARENT_SCOPE)
    set(${FIND_DEPS_OUT} "${FIND_DEPS}" PARENT_SCOPE)
endfunction()

# Create MODULE_NAMEConfig.cmake and MODULE_NAMEConfigVersion.cmake files for the given module name and version. This is
# necessary to allow other modules to find this module using find_package().
function(_create_cmake_helpers MODULE_NAME MODULE_VERSION MODULE_DEPENDENCIES FIND_DEPENDENCIES SOURCE_LIST HEADER_LIST)
    _capitalize_module_name("${MODULE_NAME}" MODULE_CAPITALIZED_NAME)
    string(TOUPPER "${MODULE_NAME}" MODULE_UPPER_NAME)
    string(PREPEND MODULE_UPPER_NAME "RDK_HALIF_AIDL_")

    set(SRC_FILES)
    foreach(SFILE IN ITEMS ${SOURCE_LIST})
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "\${PACKAGE_PREFIX_DIR}" SRC_FILE "${SFILE}")
        list(APPEND SRC_FILES "${SRC_FILE}")
    endforeach()
    set(HDR_FILES)
    foreach(HFILE IN ITEMS ${HEADER_LIST})
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "\${PACKAGE_PREFIX_DIR}" H_FILE "${HFILE}")
        list(APPEND HEADER_FILES "${H_FILE}")
   endforeach()

   list(JOIN FIND_DEPENDENCIES "\n" FIND_DEPENDENCIES)
   configure_package_config_file(
        "${CMAKE_SOURCE_DIR}/contrib/Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/RdkHalifAidl${MODULE_CAPITALIZED_NAME}Config.cmake"
       INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/RdkHalifAidl${MODULE_CAPITALIZED_NAME}"
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_PREFIX
    )
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/RdkHalifAidl${MODULE_CAPITALIZED_NAME}ConfigVersion.cmake"
        VERSION "${MODULE_VERSION}"
        COMPATIBILITY SameMajorVersion
    )
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/RdkHalifAidl${MODULE_CAPITALIZED_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/RdkHalifAidl${MODULE_CAPITALIZED_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/RdkHalifAidl${MODULE_CAPITALIZED_NAME}"
    )
    install(EXPORT "RdkHalifAidl${MODULE_CAPITALIZED_NAME}Targets"
        NAMESPACE "RdkHalifAidl::"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/RdkHalifAidl${MODULE_CAPITALIZED_NAME}"
    )
endfunction()

# Create MODULE_NAME.pc file for the given module name and version. This is necessary to allow other modules to find
# this module using pkg-config.
function(_create_pkgconfig_helpers MODULE_NAME MODULE_VERSION DEPENDENCIES)
    list(JOIN DEPENDENCIES ", " MODULE_DEPENDENCIES)

    configure_file(
        "${CMAKE_SOURCE_DIR}/contrib/module.pc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/rdk-halif-aidl-${MODULE_NAME}.pc"
        @ONLY
    )
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/rdk-halif-aidl-${MODULE_NAME}.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/"
    )
endfunction()

# Add a "versioned" module. Takes the module name, the version and a list of dependency-version pairs. Source and
# headers will be searched for in the "src" and "include" directories of the current directory.
function(add_versioned)
    cmake_parse_arguments(PARSE_ARGV 0 MODULE "" "NAME;VERSION" "DEPENDENCIES")

    set(TARGET_NAME "${MODULE_NAME}-v${MODULE_VERSION}-cpp")
    set(SHARED_TARGET_NAME "${TARGET_NAME}-shared")
    add_library("${TARGET_NAME}" STATIC)
    add_library("${SHARED_TARGET_NAME}" SHARED)
    # Find relevant files
    file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/src/*.cpp")
    file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/include/*.h")

    foreach(LIBRARY_TARGET IN ITEMS "${TARGET_NAME}" "${SHARED_TARGET_NAME}")
        target_sources("${LIBRARY_TARGET}" PRIVATE ${SRCS} PUBLIC "$<BUILD_INTERFACE:${HDRS}>")
        target_include_directories("${LIBRARY_TARGET}"
            PUBLIC
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/include>"
                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )
    endforeach()

    # Set relevant compile options
    _capitalize_module_name("${MODULE_NAME}" _MODULE_CAPITALIZED_NAME)

    add_library(
        "RdkHalifAidl::${_MODULE_CAPITALIZED_NAME}"
        ALIAS "${TARGET_NAME}"
    )
    add_library(
        "RdkHalifAidl::${_MODULE_CAPITALIZED_NAME}Shared"
        ALIAS "${SHARED_TARGET_NAME}"
    )

    set_target_properties(
        "${TARGET_NAME}" PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON
        EXPORT_NAME "${_MODULE_CAPITALIZED_NAME}"
    )
    set_target_properties(
        "${SHARED_TARGET_NAME}" PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON
        EXPORT_NAME "${_MODULE_CAPITALIZED_NAME}Shared"
    )
    set_target_properties(
        "${SHARED_TARGET_NAME}" PROPERTIES
        OUTPUT_NAME "${TARGET_NAME}"
    )

    message(DEBUG "Adding module ${MODULE_NAME} version ${MODULE_VERSION} with dependencies: ${MODULE_DEPENDENCIES}")

    _generate_dependency_list(CMAKE_DEPENDENCIES PKG_CONFIG_DEPENDENCIES LIB_DEPENDENCIES FIND_DEPS ${MODULE_DEPENDENCIES})

    # Link to binder and the given dependencies
    target_link_libraries("${TARGET_NAME}" PUBLIC ${CMAKE_DEPENDENCIES})
    target_link_libraries("${SHARED_TARGET_NAME}" PUBLIC ${CMAKE_DEPENDENCIES})

    # Create helpers for downstream consumers
    _create_cmake_helpers("${MODULE_NAME}" "${MODULE_VERSION}" "${CMAKE_DEPENDENCIES}" "${FIND_DEPS}" "${SRCS}" "${HDRS}")
    _create_pkgconfig_helpers(${MODULE_NAME} "${MODULE_VERSION}" "${PKG_CONFIG_DEPENDENCIES}")

    # Install the library, headers and source files
    install(TARGETS "${TARGET_NAME}" "${SHARED_TARGET_NAME}"
        EXPORT "RdkHalifAidl${_MODULE_CAPITALIZED_NAME}Targets"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h"
    )
    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/src/"
        FILES_MATCHING PATTERN "*.cpp"
    )
endfunction()

# Add a "current" module, i.e. a module that is build from "current" sources and with "current" dependencies. Source and
# headers will be searched for in the "src" and "include" directories of the current directory after having been generated with the "aidl" transpiler
function(add_current)
    cmake_parse_arguments(PARSE_ARGV 0 MODULE "" "NAME" "DEPENDENCIES")

    set(DEPS)
    foreach(dep IN LISTS MODULE_DEPENDENCIES)
        list(APPEND AIDL_INTERFACE_INCLUDES "-I${PROJECT_SOURCE_DIR}/${dep}/current")
        list(APPEND DEPS "${dep}" "current")
    endforeach()

    set(INTERFACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/current")

    file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${INTERFACE_DIR}/com/*.aidl")

    message(STATUS "Generate source and header files for: ${MODULE_NAME}")

    execute_process(
        COMMAND ${AIDL_EXECUTABLE}
        --version=1
        --hash=notfrozen
        --min_sdk_version=33
        --lang=cpp
        --structured
        --stability=vintf
        -o ${INTERFACE_DIR}/src
        --header_out ${INTERFACE_DIR}/include
        ${AIDL_INTERFACE_INCLUDES}
        -I${INTERFACE_DIR} ${SRCS}
        RESULT_VARIABLE gen_result
    )

    if(NOT gen_result EQUAL 0)
        message(FATAL_ERROR "AIDL generation failed for ${MODULE_NAME}; check the aidl output above.")
    endif()

    file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/current/src/*.cpp")
    if(NOT SOURCE_FILES)
         message(FATAL_ERROR "Source generation completed but no C++ files found in ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/current/src")
    endif()

    add_versioned(NAME "${MODULE_NAME}" VERSION "current" DEPENDENCIES ${DEPS})
endfunction()

function(_add_module_target module version)
    set(_target_name "${module}-v${version}-cpp")
    if(TARGET "${_target_name}")
        return()
    endif()

    resolve_module_dependency("${PROJECT_SOURCE_DIR}/${module}/${version}" _direct_dependencies)
    if(version STREQUAL "current")
        if(NOT AIDL_EXECUTABLE)
            find_program(
                AIDL_EXECUTABLE
                NAMES aidl
                HINTS ENV PATH "${PROJECT_SOURCE_DIR}/build-tools/linux_binder_idl/build-host"
                DOC "aidl executable location"
            )
            if(NOT AIDL_EXECUTABLE)
                message(FATAL_ERROR "Unable to find the aidl executable required by ${module}:current")
            endif()
        endif()

        set(_dependency_modules)
        list(LENGTH _direct_dependencies _dependency_count)
        math(EXPR _remainder "${_dependency_count} % 2")
        if(NOT _remainder EQUAL 0)
            message(FATAL_ERROR "Dependencies for ${module}:current must be module/version pairs")
        endif()
        if(_dependency_count GREATER 0)
            math(EXPR _last_index "${_dependency_count} - 2")
            foreach(_index RANGE 0 ${_last_index} 2)
                math(EXPR _version_index "${_index} + 1")
                list(GET _direct_dependencies ${_index} _dependency_module)
                list(GET _direct_dependencies ${_version_index} _dependency_version)
                if(NOT _dependency_version STREQUAL "current")
                    message(FATAL_ERROR "Current module ${module} imports non-current dependency ${_dependency_module}@${_dependency_version}")
                endif()
                list(APPEND _dependency_modules "${_dependency_module}")
            endforeach()
        endif()
        add_current(NAME "${module}" DEPENDENCIES ${_dependency_modules})
    else()
        add_versioned(NAME "${module}" VERSION "${version}" DEPENDENCIES ${_direct_dependencies})
    endif()
endfunction()

function(add_module_with_dependencies module version)
    resolve_module_dependency_order("${module}" "${version}" _dependency_order)
    foreach(_dependency IN LISTS _dependency_order)
        string(REGEX MATCH "^([^:]+):(.+)$" _ "${_dependency}")
        if(NOT _)
            message(FATAL_ERROR "Invalid dependency entry '${_dependency}', expected module:version")
        endif()
        _add_module_target("${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
    endforeach()
    _add_module_target("${module}" "${version}")
endfunction()

# Parses the `components:` map of a versions yaml into <out_var>, a list of "name=version" entries.
function(parse_versions_yaml yaml_file out_var)
    file(STRINGS "${yaml_file}" _lines)
    set(_in_components FALSE)
    set(_result)
    foreach(_line IN LISTS _lines)
        if(_line MATCHES "^components:[ \t]*$")
            set(_in_components TRUE)
        elseif(_in_components)
            if(_line MATCHES "^[ \t]+([^:# \t]+):[ \t]*([^# \t]+)[ \t]*(#.*)?$")
                list(APPEND _result "${CMAKE_MATCH_1}=${CMAKE_MATCH_2}")
            elseif(NOT _line MATCHES "^[ \t]*(#.*)?$")
                set(_in_components FALSE)
            endif()
        endif()
    endforeach()
    set(${out_var} "${_result}" PARENT_SCOPE)
endfunction()

#   parse_versions_yaml("${CMAKE_CURRENT_SOURCE_DIR}/versions_current.yaml" COMPONENTS)
#   foreach(_entry IN LISTS COMPONENTS)
#       string(REGEX MATCH "^([^=]+)=(.*)$" _ "${_entry}")
#       # CMAKE_MATCH_1 = name, CMAKE_MATCH_2 = version
#   endforeach()

function(resolve_module_dependency interface_file_path out_var)
    file(STRINGS "${interface_file_path}/interface.yaml" _yaml_lines)
    set(_in_imports FALSE)
    set(_dependencies)
    foreach(_line IN LISTS _yaml_lines)
        if(_line MATCHES "^  imports:[ \t]*$")
            set(_in_imports TRUE)
        elseif(_in_imports)
            if(_line MATCHES "^    -[ \t]*([^@ \t]+)@([^ \t]+)[ \t]*$")
                list(PREPEND _dependencies "${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
            elseif(NOT _line MATCHES "^[ \t]*$")
                set(_in_imports FALSE)
            endif()
        endif()
    endforeach()

    set(${out_var} "${_dependencies}" PARENT_SCOPE)
endfunction()