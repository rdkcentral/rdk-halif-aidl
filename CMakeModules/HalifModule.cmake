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

# HalifModule — build and package ONE (component, version) node of a plan.
#
#   halif_add_module(NAME <comp> VERSION <ver> DEPENDENCIES <dep@ver ...>)
#
# A released snapshot (<comp>/<ver>/) supplies its committed bindings in
# include/ and src/. A current node (<comp>/current/) carries AIDL only; its
# bindings are generated into ${CMAKE_BINARY_DIR}/gen/<comp>/current at
# configure time, never into the source tree.
#
# Targets (in-tree alias RdkHalifAidl::<name>, same name once installed):
#   <comp>-v<ver>-cpp          shared   lib<comp>-v<ver>-cpp.so
#   <comp>-v<ver>-cpp-static   static   lib<comp>-v<ver>-cpp.a
#
# Installed layout — every path carries the version, so any number of versions
# of one component coexist in one prefix:
#   <libdir>/lib<comp>-v<ver>-cpp.{so,a}
#   <includedir>/rdk-halif-aidl/<comp>/<ver>/com/rdk/hal/...
#   <prefix>/src/rdk-halif-aidl/<comp>/<ver>/{com,src,interface.yaml,.hash}
#   <libdir>/cmake/RdkHalifAidl<Comp>-<ver>/RdkHalifAidl<Comp>{Config,ConfigVersion,Targets}.cmake
#   <libdir>/pkgconfig/rdk-halif-aidl-<comp>-<ver>.pc
#
# Consumers:
#   find_package(RdkHalifAidlHdmicec 0.1.0.0 EXACT CONFIG)
#   target_link_libraries(app PRIVATE RdkHalifAidl::hdmicec-v0.1.0.0-cpp)
#   pkg-config --cflags --libs rdk-halif-aidl-hdmicec-0.1.0.0

include_guard(GLOBAL)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(_HALIF_TEMPLATES "${CMAKE_CURRENT_LIST_DIR}/templates")

function(_halif_capitalize in out)
    string(SUBSTRING "${in}" 0 1 head)
    string(SUBSTRING "${in}" 1 -1 tail)
    string(TOUPPER "${head}" head)
    set(${out} "${head}${tail}" PARENT_SCOPE)
endfunction()

# Generate C++ for <comp>/current from its AIDL into the build tree.
function(_halif_generate_current comp deps out_dir)
    if(NOT HALIF_AIDL_EXECUTABLE)
        message(FATAL_ERROR "${comp}@current needs the aidl compiler; set HALIF_AIDL_EXECUTABLE or HOST_AIDL_DIR")
    endif()
    set(gen "${CMAKE_BINARY_DIR}/gen/${comp}/current")
    set(src "${HALIF_ROOT}/${comp}/current")
    file(GLOB_RECURSE aidls CONFIGURE_DEPENDS "${src}/com/*.aidl")
    if(NOT aidls)
        message(FATAL_ERROR "${comp}@current: no .aidl under ${src}/com")
    endif()
    set(incs "-I${src}")
    foreach(dep IN LISTS deps)
        halif_node_split("${dep}" dc dv)
        list(APPEND incs "-I${HALIF_ROOT}/${dc}/${dv}")
    endforeach()
    file(REMOVE_RECURSE "${gen}")
    file(MAKE_DIRECTORY "${gen}/src" "${gen}/include")
    message(STATUS "Generating ${comp}@current bindings -> ${gen}")
    execute_process(
        COMMAND "${HALIF_AIDL_EXECUTABLE}"
            --lang=cpp --structured --stability=vintf --min_sdk_version=33
            --version=1 --hash=notfrozen
            ${incs}
            -o "${gen}/src" -h "${gen}/include"
            ${aidls}
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
    )
    if(NOT rc EQUAL 0)
        message(FATAL_ERROR "aidl failed for ${comp}@current:\n${out}\n${err}")
    endif()
    set(${out_dir} "${gen}" PARENT_SCOPE)
endfunction()

function(halif_add_module)
    cmake_parse_arguments(PARSE_ARGV 0 M "" "NAME;VERSION" "DEPENDENCIES")
    set(comp "${M_NAME}")
    set(ver "${M_VERSION}")
    set(src_dir "${HALIF_ROOT}/${comp}/${ver}")
    set(tgt "${comp}-v${ver}-cpp")
    _halif_capitalize("${comp}" Comp)
    set(pkg "RdkHalifAidl${Comp}")

    if(ver STREQUAL "current")
        _halif_generate_current("${comp}" "${M_DEPENDENCIES}" gen_dir)
        set(inc_dir "${gen_dir}/include")
        set(cpp_dir "${gen_dir}/src")
    else()
        set(inc_dir "${src_dir}/include")
        set(cpp_dir "${src_dir}/src")
    endif()
    file(GLOB_RECURSE srcs CONFIGURE_DEPENDS "${cpp_dir}/*.cpp")
    if(NOT srcs)
        message(FATAL_ERROR "${comp}@${ver}: no sources under ${cpp_dir}")
    endif()

    set(inc_install "${CMAKE_INSTALL_INCLUDEDIR}/rdk-halif-aidl/${comp}/${ver}")
    set(src_install "src/rdk-halif-aidl/${comp}/${ver}")
    set(pkg_install "${CMAKE_INSTALL_LIBDIR}/cmake/${pkg}-${ver}")

    # Dependency targets, one list per linkage.
    set(dep_shared "")
    set(dep_static "")
    set(find_deps "")
    set(pc_requires "")
    foreach(dep IN LISTS M_DEPENDENCIES)
        halif_node_split("${dep}" dc dv)
        _halif_capitalize("${dc}" DComp)
        list(APPEND dep_shared "${dc}-v${dv}-cpp")
        list(APPEND dep_static "${dc}-v${dv}-cpp-static")
        if(dv MATCHES "${_HALIF_VER_RE}")
            string(APPEND find_deps "find_dependency(RdkHalifAidl${DComp} ${dv} EXACT)\n")
        else()
            string(APPEND find_deps "find_dependency(RdkHalifAidl${DComp})\n")
        endif()
        list(APPEND pc_requires "rdk-halif-aidl-${dc}-${dv}")
    endforeach()

    # Compile once; wrap the objects as shared and static.
    add_library(${tgt}-objs OBJECT ${srcs})
    target_include_directories(${tgt}-objs PRIVATE "${inc_dir}")
    target_link_libraries(${tgt}-objs PRIVATE Binder::Binder ${dep_shared})
    set_target_properties(${tgt}-objs PROPERTIES
        CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON POSITION_INDEPENDENT_CODE ON)

    add_library(${tgt} SHARED $<TARGET_OBJECTS:${tgt}-objs>)
    add_library(${tgt}-static STATIC $<TARGET_OBJECTS:${tgt}-objs>)
    target_link_libraries(${tgt} PUBLIC Binder::Binder ${dep_shared})
    target_link_libraries(${tgt}-static PUBLIC Binder::Binder ${dep_static})
    foreach(t IN ITEMS ${tgt} ${tgt}-static)
        target_include_directories(${t} SYSTEM PUBLIC
            "$<BUILD_INTERFACE:${inc_dir}>"
            "$<INSTALL_INTERFACE:${inc_install}>")
        set_target_properties(${t} PROPERTIES
            OUTPUT_NAME "${tgt}"
            EXPORT_NAME "${t}"
            CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON POSITION_INDEPENDENT_CODE ON)
        add_library(RdkHalifAidl::${t} ALIAS ${t})
    endforeach()

    # Install: library, headers, contract + sources, CMake package, pkg-config.
    install(TARGETS ${tgt} ${tgt}-static EXPORT ${pkg}-${ver}Targets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
    install(DIRECTORY "${inc_dir}/" DESTINATION "${inc_install}"
        FILES_MATCHING PATTERN "*.h")
    install(DIRECTORY "${cpp_dir}/" DESTINATION "${src_install}/src"
        FILES_MATCHING PATTERN "*.cpp")
    install(DIRECTORY "${src_dir}/com/" DESTINATION "${src_install}/com"
        FILES_MATCHING PATTERN "*.aidl")
    install(FILES "${src_dir}/interface.yaml" DESTINATION "${src_install}")
    if(EXISTS "${src_dir}/.hash")
        install(FILES "${src_dir}/.hash" DESTINATION "${src_install}")
    endif()
    install(EXPORT ${pkg}-${ver}Targets
        NAMESPACE RdkHalifAidl::
        FILE "${pkg}Targets.cmake"
        DESTINATION "${pkg_install}")

    set(gen_pkg "${CMAKE_BINARY_DIR}/pkg/${comp}-${ver}")
    set(HALIF_PKG "${pkg}")
    set(HALIF_TGT "${tgt}")
    set(HALIF_COMP "${comp}")
    set(HALIF_COMP_CAP "${Comp}")
    set(HALIF_VER "${ver}")
    set(HALIF_FIND_DEPS "${find_deps}")
    set(HALIF_INC_INSTALL "${inc_install}")
    set(HALIF_SRC_INSTALL "${src_install}")
    configure_package_config_file(
        "${_HALIF_TEMPLATES}/Config.cmake.in"
        "${gen_pkg}/${pkg}Config.cmake"
        INSTALL_DESTINATION "${pkg_install}"
        PATH_VARS HALIF_INC_INSTALL HALIF_SRC_INSTALL)
    set(pkg_files "${gen_pkg}/${pkg}Config.cmake")
    if(ver MATCHES "${_HALIF_VER_RE}")
        # Pre-baseline 0.<generation>.<minor>.<patch>: the generation (CMake's
        # minor) is the breaking digit, so same-minor is the compatible range.
        write_basic_package_version_file(
            "${gen_pkg}/${pkg}ConfigVersion.cmake"
            VERSION "${ver}"
            COMPATIBILITY SameMinorVersion)
        list(APPEND pkg_files "${gen_pkg}/${pkg}ConfigVersion.cmake")
    endif()
    install(FILES ${pkg_files} DESTINATION "${pkg_install}")

    # pkg-config. linux_binder_idl ships no binder.pc, so the Binder SDK paths
    # resolved at configure time are written in directly.
    get_filename_component(binder_libdir "${Binder_LIBRARY}" DIRECTORY)
    set(HALIF_PC_REQUIRES "")
    if(pc_requires)
        string(REPLACE ";" " " HALIF_PC_REQUIRES "${pc_requires}")
    endif()
    set(HALIF_PC_BINDER_CFLAGS "-I${Binder_INCLUDE_DIR}")
    set(HALIF_PC_BINDER_LIBS "-L${binder_libdir} -lbinder -lutils")
    configure_file("${_HALIF_TEMPLATES}/module.pc.in"
        "${gen_pkg}/rdk-halif-aidl-${comp}-${ver}.pc" @ONLY)
    install(FILES "${gen_pkg}/rdk-halif-aidl-${comp}-${ver}.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
endfunction()
