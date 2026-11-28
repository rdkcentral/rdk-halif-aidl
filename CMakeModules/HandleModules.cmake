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

        list(APPEND PKG_CONFIG_STYLE "rdk-halif-aidl-${ARGV${dep}}-${ARGV${dep_ver_index}}")
        list(APPEND LIB_NAMES "${ARGV${dep}}-v${ARGV${dep_ver_index}}-cpp")
        _capitalize_module_name("${ARGV${dep}}" _DEP_CAP)
        list(APPEND CMAKE_STYLE "RdkHalifAidl::${_DEP_CAP}-v${ARGV${dep_ver_index}}")
        set(_DEP_PACKAGE_NAME "RdkHalifAidl${_DEP_CAP}")
        set(_DEP_PACKAGE_PATH "\${CMAKE_CURRENT_LIST_DIR}/../RdkHalifAidl${_DEP_CAP}-${ARGV${dep_ver_index}}")
        if("${ARGV${dep_ver_index}}" STREQUAL "current")
            list(APPEND FIND_DEPS "find_dependency(${_DEP_PACKAGE_NAME} CONFIG PATHS \"${_DEP_PACKAGE_PATH}\")")
        else()
            list(APPEND FIND_DEPS "find_dependency(${_DEP_PACKAGE_NAME} ${ARGV${dep_ver_index}} EXACT CONFIG PATHS \"${_DEP_PACKAGE_PATH}\")")
        endif()
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
        string(REPLACE
            "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/src"
            "\${PACKAGE_PREFIX_DIR}/src/${MODULE_NAME}/${MODULE_VERSION}"
            SRC_FILE "${SFILE}"
        )
        list(APPEND SRC_FILES "${SRC_FILE}")
    endforeach()
    set(HEADER_FILES)
    foreach(HFILE IN ITEMS ${HEADER_LIST})
        string(REPLACE
            "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/include"
            "\${PACKAGE_PREFIX_DIR}/include/${MODULE_NAME}/${MODULE_VERSION}"
            H_FILE "${HFILE}"
        )
        list(APPEND HEADER_FILES "${H_FILE}")
   endforeach()

   list(JOIN FIND_DEPENDENCIES "\n" FIND_DEPENDENCIES)
   set(MODULE_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/RdkHalifAidl${MODULE_CAPITALIZED_NAME}-${MODULE_VERSION}")
   set(MODULE_CMAKE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/cmake/RdkHalifAidl${MODULE_CAPITALIZED_NAME}-${MODULE_VERSION}")
   file(MAKE_DIRECTORY "${MODULE_CMAKE_OUTPUT_DIR}")
   configure_package_config_file(
        "${CMAKE_SOURCE_DIR}/contrib/Config.cmake.in"
        "${MODULE_CMAKE_OUTPUT_DIR}/RdkHalifAidl${MODULE_CAPITALIZED_NAME}Config.cmake"
        INSTALL_DESTINATION "${MODULE_CMAKE_INSTALL_DIR}"
        PATH_VARS CMAKE_INSTALL_DATADIR CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_PREFIX
    )
    write_basic_package_version_file(
        "${MODULE_CMAKE_OUTPUT_DIR}/RdkHalifAidl${MODULE_CAPITALIZED_NAME}ConfigVersion.cmake"
        VERSION "${MODULE_VERSION}"
        COMPATIBILITY SameMinorVersion
    )
    install(FILES
        "${MODULE_CMAKE_OUTPUT_DIR}/RdkHalifAidl${MODULE_CAPITALIZED_NAME}Config.cmake"
        "${MODULE_CMAKE_OUTPUT_DIR}/RdkHalifAidl${MODULE_CAPITALIZED_NAME}ConfigVersion.cmake"
        DESTINATION "${MODULE_CMAKE_INSTALL_DIR}"
    )
    install(EXPORT "RdkHalifAidl${MODULE_CAPITALIZED_NAME}-v${MODULE_VERSION}Targets"
        NAMESPACE "RdkHalifAidl::"
        DESTINATION "${MODULE_CMAKE_INSTALL_DIR}"
        FILE "RdkHalifAidl${MODULE_CAPITALIZED_NAME}Targets.cmake"
    )
endfunction()

# Create MODULE_NAME.pc file for the given module name and version. This is necessary to allow other modules to find
# this module using pkg-config.
function(_create_pkgconfig_helpers MODULE_NAME MODULE_VERSION DEPENDENCIES)
    list(JOIN DEPENDENCIES ", " MODULE_DEPENDENCIES)

    configure_file(
        "${CMAKE_SOURCE_DIR}/contrib/module.pc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/rdk-halif-aidl-${MODULE_NAME}-${MODULE_VERSION}.pc"
        @ONLY
    )
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/rdk-halif-aidl-${MODULE_NAME}-${MODULE_VERSION}.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/"
    )
endfunction()

# Add a "versioned" module. Takes the module name, the version and a list of dependency-version pairs. Source and
# headers will be searched for in the "src" and "include" directories of the current directory.
#
# Files that do not exist yet because a build step produces them (see add_current()) are passed explicitly with
# GENERATED_SOURCES and GENERATED_HEADERS instead of being globbed, and GENERATOR_TARGET names the target that
# produces them.
function(add_versioned)
    cmake_parse_arguments(
        PARSE_ARGV 0 MODULE "" "NAME;VERSION;GENERATOR_TARGET" "DEPENDENCIES;GENERATED_SOURCES;GENERATED_HEADERS"
    )

    set(TARGET_NAME "${MODULE_NAME}-v${MODULE_VERSION}-cpp")
    add_library("${TARGET_NAME}")
    # Find relevant files
    if(MODULE_GENERATOR_TARGET)
        set(SRCS ${MODULE_GENERATED_SOURCES})
        set(HDRS ${MODULE_GENERATED_HEADERS})
        set_source_files_properties(${SRCS} ${HDRS} PROPERTIES GENERATED TRUE)
        add_dependencies("${TARGET_NAME}" "${MODULE_GENERATOR_TARGET}")
    else()
        file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/src/*.cpp")
        file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/include/*.h")
    endif()

    target_sources("${TARGET_NAME}" PRIVATE ${SRCS} PUBLIC "$<BUILD_INTERFACE:${HDRS}>")
    target_include_directories("${TARGET_NAME}"
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${MODULE_NAME}/${MODULE_VERSION}>"
    )

    # Set relevant compile options
    _capitalize_module_name("${MODULE_NAME}" _MODULE_CAPITALIZED_NAME)
    set(_MODULE_VERSIONED_EXPORT_NAME "${_MODULE_CAPITALIZED_NAME}-v${MODULE_VERSION}")

    add_library(
        "RdkHalifAidl::${_MODULE_VERSIONED_EXPORT_NAME}"
        ALIAS "${TARGET_NAME}"
    )

    set_target_properties(
        "${TARGET_NAME}" PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON
        EXPORT_NAME "${_MODULE_VERSIONED_EXPORT_NAME}"
    )
    message(DEBUG "Adding module ${MODULE_NAME} version ${MODULE_VERSION} with dependencies: ${MODULE_DEPENDENCIES}")

    _generate_dependency_list(CMAKE_DEPENDENCIES PKG_CONFIG_DEPENDENCIES LIB_DEPENDENCIES FIND_DEPS ${MODULE_DEPENDENCIES})

    # Link to binder and the given dependencies
    target_link_libraries("${TARGET_NAME}" PUBLIC ${CMAKE_DEPENDENCIES})

    # Export the full dependency closure so downstream consumers can resolve
    # every dependency directly from the module's CMake and pkg-config metadata.
    resolve_module_dependency_order("${MODULE_NAME}" "${MODULE_VERSION}" TRANSITIVE_DEPENDENCIES)
    set(TRANSITIVE_DEPENDENCY_PAIRS)
    foreach(DEPENDENCY IN LISTS TRANSITIVE_DEPENDENCIES)
        string(REGEX MATCH "^([^:]+):(.+)$" _ "${DEPENDENCY}")
        if(NOT _)
            message(FATAL_ERROR "Invalid dependency entry '${DEPENDENCY}', expected module:version")
        endif()
        list(APPEND TRANSITIVE_DEPENDENCY_PAIRS "${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
    endforeach()
    _generate_dependency_list(
        EXPORTED_CMAKE_DEPENDENCIES
        EXPORTED_PKG_CONFIG_DEPENDENCIES
        EXPORTED_LIB_DEPENDENCIES
        EXPORTED_FIND_DEPS
        ${TRANSITIVE_DEPENDENCY_PAIRS}
    )

    # Create helpers for downstream consumers
    _create_cmake_helpers(
        "${MODULE_NAME}" "${MODULE_VERSION}" "${EXPORTED_CMAKE_DEPENDENCIES}"
        "${EXPORTED_FIND_DEPS}" "${SRCS}" "${HDRS}"
    )
    _create_pkgconfig_helpers(
        "${MODULE_NAME}" "${MODULE_VERSION}" "${EXPORTED_PKG_CONFIG_DEPENDENCIES}"
    )

    # Install the library, headers and source files
    install(TARGETS "${TARGET_NAME}"
        EXPORT "RdkHalifAidl${_MODULE_CAPITALIZED_NAME}-v${MODULE_VERSION}Targets"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${MODULE_NAME}/${MODULE_VERSION}"
        FILES_MATCHING PATTERN "*.h"
    )
    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/${MODULE_VERSION}/src/"
        DESTINATION "src/${MODULE_NAME}/${MODULE_VERSION}"
        FILES_MATCHING PATTERN "*.cpp"
    )
endfunction()

# Work out the C++ files that aidl emits for the given AIDL files, as paths relative to the module directory. aidl
# writes "<Name>.cpp", "<Name>.h" and the binder stub and proxy headers "Bn<Base>.h" and "Bp<Base>.h" for every type,
# where <Base> is <Name> without the "I" prefix for interfaces. Listing them is what lets the build track the outputs.
function(_aidl_generated_files INTERFACE_DIR AIDL_FILES SOURCES_OUT HEADERS_OUT RELATIVE_OUT)
    set(_sources)
    set(_headers)
    set(_relative)
    foreach(_aidl IN LISTS AIDL_FILES)
        file(RELATIVE_PATH _rel "${INTERFACE_DIR}" "${_aidl}")
        get_filename_component(_dir "${_rel}" DIRECTORY)
        get_filename_component(_name "${_rel}" NAME_WLE)
        file(READ "${_aidl}" _text)
        set(_base "${_name}")
        if(_text MATCHES "(^|\n)[ \t]*(@[A-Za-z]+[ \t]+)*(oneway[ \t]+)?interface[ \t]+${_name}[^A-Za-z0-9_]"
           AND _name MATCHES "^I[A-Z]")
            string(SUBSTRING "${_name}" 1 -1 _base)
        endif()
        list(APPEND _relative "src/${_dir}/${_name}.cpp")
        list(APPEND _sources "${INTERFACE_DIR}/src/${_dir}/${_name}.cpp")
        foreach(_header IN ITEMS "${_name}.h" "Bn${_base}.h" "Bp${_base}.h")
            list(APPEND _relative "include/${_dir}/${_header}")
            list(APPEND _headers "${INTERFACE_DIR}/include/${_dir}/${_header}")
        endforeach()
    endforeach()
    list(SORT _relative)
    set(${SOURCES_OUT} "${_sources}" PARENT_SCOPE)
    set(${HEADERS_OUT} "${_headers}" PARENT_SCOPE)
    set(${RELATIVE_OUT} "${_relative}" PARENT_SCOPE)
endfunction()

# Determine the version and hash that the generated getInterfaceVersion() and getInterfaceHash() report.
#
# A release freezes an interface by writing the contract hash to ".hash" and a positive integer "version:" to
# interface.yaml. Without them the interface is not frozen: version 1 and hash "notfrozen". Pinning a version on a
# contract without a hash is invalid.
function(_aidl_interface_identity module interface_dir out_version out_hash)
    set(_version 1)
    set(_hash "notfrozen")

    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${interface_dir}/interface.yaml")
    if(EXISTS "${interface_dir}/.hash")
        file(READ "${interface_dir}/.hash" _hash)
        string(STRIP "${_hash}" _hash)
        set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${interface_dir}/.hash")
    endif()

    file(STRINGS "${interface_dir}/interface.yaml" _yaml_lines REGEX "^[ \t]+version:")
    if(_yaml_lines)
        list(GET _yaml_lines 0 _version_line)
        string(REGEX REPLACE "^[ \t]+version:[ \t]*([^ \t#]*).*$" "\\1" _version "${_version_line}")
        if(NOT _version MATCHES "^[1-9][0-9]*$")
            message(FATAL_ERROR "interface.yaml 'version' of ${module} must be a positive integer, got '${_version}'")
        endif()
        if(_hash STREQUAL "notfrozen")
            message(FATAL_ERROR "interface.yaml 'version: ${_version}' is set on ${module} but the contract is not "
                "frozen: a pinned version requires a .hash")
        endif()
    endif()

    set(${out_version} "${_version}" PARENT_SCOPE)
    set(${out_hash} "${_hash}" PARENT_SCOPE)
endfunction()

# Add a "current" module, i.e. a module that is build from "current" sources and with "current" dependencies. Source and
# headers are generated with the "aidl" transpiler into the "src" and "include" directories of the module's "current"
# directory, at build time, by a command that is re-run whenever one of its inputs changes. It removes the previous
# output first, so files of AIDL types that no longer exist do not linger.
#
# The target "<module>-aidl-gen" generates the bindings without compiling them, for anything that needs only the files.
function(add_current)
    cmake_parse_arguments(PARSE_ARGV 0 MODULE "" "NAME" "DEPENDENCIES")

    set(DEPS)
    set(DEP_AIDL_FILES)
    foreach(dep IN LISTS MODULE_DEPENDENCIES)
        list(APPEND AIDL_INTERFACE_INCLUDES "-I${PROJECT_SOURCE_DIR}/${dep}/current")
        list(APPEND DEPS "${dep}" "current")
        file(GLOB_RECURSE _dep_aidl CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/${dep}/current/com/*.aidl")
        list(APPEND DEP_AIDL_FILES ${_dep_aidl})
    endforeach()

    set(INTERFACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}/current")

    file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${INTERFACE_DIR}/com/*.aidl")
    if(NOT SRCS)
        message(FATAL_ERROR "No AIDL files found for ${MODULE_NAME} in ${INTERFACE_DIR}/com")
    endif()

    message(STATUS "Bindings for ${MODULE_NAME} are generated at build time")

    _aidl_interface_identity("${MODULE_NAME}" "${INTERFACE_DIR}" EMIT_VERSION EMIT_HASH)
    _aidl_generated_files("${INTERFACE_DIR}" "${SRCS}" GENERATED_SOURCES GENERATED_HEADERS GENERATED_RELATIVE)

    # The manifest is only rewritten when its content changes. As a dependency of the command, it makes removing or
    # renaming an AIDL file, or freezing the interface, regenerate the bindings, which a dependency on the AIDL files
    # cannot do.
    set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/aidl-gen")
    set(MANIFEST "${GEN_DIR}/${MODULE_NAME}.outputs")
    list(JOIN GENERATED_RELATIVE "\n" _manifest_content)
    file(CONFIGURE OUTPUT "${MANIFEST}"
        CONTENT "version=${EMIT_VERSION}\nhash=${EMIT_HASH}\n${_manifest_content}\n" @ONLY)

    set(DOC_INJECT_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/scripts/aidl_comment_inject.py")

    set(GENERATOR_DEPENDS ${SRCS} ${DEP_AIDL_FILES} "${INTERFACE_DIR}/interface.yaml" "${MANIFEST}"
        "${DOC_INJECT_SCRIPT}")
    if(IS_ABSOLUTE "${AIDL_EXECUTABLE}")
        list(APPEND GENERATOR_DEPENDS "${AIDL_EXECUTABLE}")
    endif()

    add_custom_command(
        OUTPUT ${GENERATED_SOURCES} ${GENERATED_HEADERS}
        COMMAND "${CMAKE_COMMAND}" -E rm -rf "${INTERFACE_DIR}/src" "${INTERFACE_DIR}/include"
        COMMAND "${AIDL_EXECUTABLE}"
            --version=${EMIT_VERSION}
            --hash=${EMIT_HASH}
            --min_sdk_version=33
            --lang=cpp
            --structured
            --stability=vintf
            -o "${INTERFACE_DIR}/src"
            --header_out "${INTERFACE_DIR}/include"
            ${AIDL_INTERFACE_INCLUDES}
            "-I${INTERFACE_DIR}" ${SRCS}
        COMMAND python3 "${DOC_INJECT_SCRIPT}" --repo-root "${CMAKE_CURRENT_SOURCE_DIR}" --version current "${MODULE_NAME}"
        DEPENDS ${GENERATOR_DEPENDS}
        COMMENT "Generating C++ bindings for ${MODULE_NAME}"
        VERBATIM
    )
    add_custom_target("${MODULE_NAME}-aidl-gen" DEPENDS ${GENERATED_SOURCES} ${GENERATED_HEADERS})

    add_versioned(
        NAME "${MODULE_NAME}" VERSION "current" DEPENDENCIES ${DEPS}
        GENERATED_SOURCES ${GENERATED_SOURCES} GENERATED_HEADERS ${GENERATED_HEADERS}
        GENERATOR_TARGET "${MODULE_NAME}-aidl-gen"
    )
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
                DOC "aidl executable location"
            )
            if(NOT AIDL_EXECUTABLE)
                message(FATAL_ERROR "Unable to find the aidl executable required by ${module}:current")
            endif()
        endif()

        list(LENGTH _direct_dependencies _dependency_count)
        math(EXPR _remainder "${_dependency_count} % 2")
        if(NOT _remainder EQUAL 0)
            message(FATAL_ERROR "Dependencies for ${module}:current must be module/version pairs")
        endif()

        # Transitive closure: AIDL imports and link dependencies need every upstream module (e.g. common).
        set(_dependency_modules)
        resolve_module_dependency_order("${module}" "current" _transitive_dependencies)
        foreach(_entry IN LISTS _transitive_dependencies)
            string(REGEX MATCH "^([^:]+):(.+)$" _ "${_entry}")
            if(NOT CMAKE_MATCH_2 STREQUAL "current")
                message(FATAL_ERROR "Current module ${module} depends on non-current dependency ${CMAKE_MATCH_1}@${CMAKE_MATCH_2}")
            endif()
            list(APPEND _dependency_modules "${CMAKE_MATCH_1}")
        endforeach()
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

function(resolve_module_dependency interface_file_path out_var)
    get_filename_component(_version "${interface_file_path}" NAME)
    file(STRINGS "${interface_file_path}/interface.yaml" _yaml_lines)
    set(_in_imports FALSE)
    set(_dependencies)
    foreach(_line IN LISTS _yaml_lines)
        if(_line MATCHES "^  imports:[ \t]*$")
            set(_in_imports TRUE)
        elseif(_in_imports)
            if(_line MATCHES "^    -[ \t]*([^@ \t]+)@([^ \t]+)[ \t]*$")
                if(NOT _version STREQUAL "current" AND CMAKE_MATCH_2 STREQUAL "current")
                    message(FATAL_ERROR "Released module ${interface_file_path} depends on current dependency ${CMAKE_MATCH_1}@${CMAKE_MATCH_2}")
                endif()
                list(PREPEND _dependencies "${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
            elseif(NOT _line MATCHES "^[ \t]*$")
                set(_in_imports FALSE)
            endif()
        endif()
    endforeach()

    set(${out_var} "${_dependencies}" PARENT_SCOPE)
endfunction()
