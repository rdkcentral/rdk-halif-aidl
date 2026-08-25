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

        list(APPEND CMAKE_STYLE "${ARGV${dep}}-v${ARGV${dep_ver_index}}-cpp")
        list(APPEND PKG_CONFIG_STYLE "rdk-halif-${ARGV${dep}} = ${ARGV${dep_ver_index}}")
        list(APPEND LIB_NAMES "${ARGV${dep}}-v${ARGV${dep_ver_index}}-cpp")
        _capitalize_module_name("${ARGV${dep}}" _DEP_CAP)
        list(APPEND FIND_DEPS "find_dependency(RdkHalif${_DEP_CAP})")
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
    string(PREPEND MODULE_UPPER_NAME "RDK_HALIF_")

    set(SRC_FILES)
    foreach(SFILE IN ITEMS ${SOURCE_LIST})
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "\${PACKAGE_PREFIX_DIR}" SRC_FILE "${SFILE}")
        list(APPEND SRC_FILES "${SRC_FILE}")
    endforeach()
    set(HDR_FILES)
    foreach(HFILE IN ITEMS "${HEADER_LIST}")
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "\${PACKAGE_PREFIX_DIR}" H_FILE "${HFILE}")
        list(APPEND HEADER_FILES "${H_FILE}")
   endforeach()

   list(JOIN FIND_DEPENDENCIES "\n" FIND_DEPENDENCIES)
   configure_package_config_file(
        "${CMAKE_SOURCE_DIR}/contrib/Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/RdkHalif${MODULE_CAPITALIZED_NAME}Config.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_FULL_DATADIR}/cmake/RdkHalif${MODULE_CAPITALIZED_NAME}"
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_PREFIX
    )
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/RdkHalif${MODULE_CAPITALIZED_NAME}ConfigVersion.cmake"
        VERSION "${MODULE_VERSION}"
        COMPATIBILITY SameMajorVersion
    )
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/RdkHalif${MODULE_CAPITALIZED_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/RdkHalif${MODULE_CAPITALIZED_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_FULL_DATADIR}/cmake/RdkHalif${MODULE_CAPITALIZED_NAME}"
    )
    install(EXPORT "RdkHalif${MODULE_CAPITALIZED_NAME}Targets"
        NAMESPACE "RdkHalif::"
        DESTINATION "${CMAKE_INSTALL_FULL_DATADIR}/cmake/RdkHalif${MODULE_CAPITALIZED_NAME}"
    )
endfunction()

# Create MODULE_NAME.pc file for the given module name and version. This is necessary to allow other modules to find
# this module using pkg-config.
function(_create_pkgconfig_helpers MODULE_NAME MODULE_VERSION DEPENDENCIES)
    list(JOIN DEPENDENCIES ", " MODULE_DEPENDENCIES)

    configure_file(
        "${CMAKE_SOURCE_DIR}/contrib/module.pc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/rdk-halif-${MODULE_NAME}.pc"
        @ONLY
    )
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/rdk-halif-${MODULE_NAME}.pc"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig/"
    )
endfunction()

# Add a "versioned" module. Takes the module name, the version and a list of dependency-version pairs. Source and
# headers will be searched for in the "src" and "include" directories of the current directory.
function(add_versioned)
    cmake_parse_arguments(PARSE_ARGV 0 MODULE "" "NAME;VERSION" "DEPENDENCIES")

    set(TARGET_NAME "${MODULE_NAME}-v${MODULE_VERSION}-cpp")
    add_library("${TARGET_NAME}" STATIC)

    # Find relevant files
    file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

    # Set sources
    target_sources("${TARGET_NAME}" PRIVATE ${SRCS} PUBLIC "$<BUILD_INTERFACE:${HDRS}>")
    target_include_directories("${TARGET_NAME}"
        PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )

    # Set relevant compile options
    _capitalize_module_name("${MODULE_NAME}" _MODULE_CAPITALIZED_NAME)
    set_target_properties(
        "${TARGET_NAME}" PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON
        EXPORT_NAME "${_MODULE_CAPITALIZED_NAME}"
    )

    message(DEBUG "Adding module ${MODULE_NAME} version ${MODULE_VERSION} with dependencies: ${MODULE_DEPENDENCIES}")

    _generate_dependency_list(CMAKE_DEPENDENCIES PKG_CONFIG_DEPENDENCIES LIB_DEPENDENCIES FIND_DEPS ${MODULE_DEPENDENCIES})

    # Link to binder and the given dependencies
    target_link_libraries("${TARGET_NAME}" PUBLIC ${CMAKE_DEPENDENCIES})

    # Create helpers for downstream consumers
    _create_cmake_helpers("${MODULE_NAME}" "${MODULE_VERSION}" "${CMAKE_DEPENDENCIES}" "${FIND_DEPS}" "${SRCS}" "${HDRS}")
    _create_pkgconfig_helpers(${MODULE_NAME} "${MODULE_VERSION}" "${PKG_CONFIG_DEPENDENCIES}")

    # Install the library, headers and source files
    install(TARGETS "${TARGET_NAME}"
        EXPORT "RdkHalif${_MODULE_CAPITALIZED_NAME}Targets"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}"
    )
    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
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
        string(APPEND AIDL_GEN_TARGET_DEPS "-I${PROJECT_SOURCE_DIR}/${dep}/current ")
        list(APPEND DEPS "${dep}" "current")
    endforeach()
    if(AIDL_GEN_TARGET_DEPS)
        string(REPLACE " " ";" AIDL_INTERFACE_INCLUDES ${AIDL_GEN_TARGET_DEPS})
    endif()

    set(INTERFACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

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

    file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    if(NOT SOURCE_FILES)
         message(FATAL_ERROR "Source generation completed but no C++ files found in ${CMAKE_CURRENT_SOURCE_DIR}/src")
    endif()

    add_versioned(NAME "${MODULE_NAME}" VERSION "current" DEPENDENCIES ${DEPS})
endfunction()
