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
# Bindings live in the source tree, <comp>/<ver>/{include,src}, for every
# version. A released snapshot has them committed; current/ has them gitignored.
# They are generated at BUILD time, never at configure time, by the
# linux_binder_idl toolchain (aidl_ops.py):
#
#   current    regenerated whenever its AIDL, or a dependency's, changes
#   released   compiled as committed; regenerated only by building the
#              halif-generate target (or halif-generate-<comp>-<ver>)
#
# Library type, per component (HALIF_LIBRARY_TYPE, HALIF_LIBRARY_TYPE_<comp>):
#   SHARED (default)   <comp>-v<ver>-cpp          lib<comp>-v<ver>-cpp.so
#   STATIC             <comp>-v<ver>-cpp-static   lib<comp>-v<ver>-cpp.a
#   BOTH               both of the above
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
#   find_package(RdkHalifAidlHdmicec 0.1.0.0 CONFIG)
#   target_link_libraries(app PRIVATE RdkHalifAidl::Hdmicec)
#   pkg-config --cflags --libs rdk-halif-aidl-hdmicec-0.1.0.0

include_guard(GLOBAL)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(_HALIF_TEMPLATES "${CMAKE_CURRENT_LIST_DIR}/templates")

if(NOT TARGET halif-generate)
    add_custom_target(halif-generate
        COMMENT "Regenerated bindings for every node in the plan")
endif()

function(_halif_capitalize in out)
    string(SUBSTRING "${in}" 0 1 head)
    string(SUBSTRING "${in}" 1 -1 tail)
    string(TOUPPER "${head}" head)
    set(${out} "${head}${tail}" PARENT_SCOPE)
endfunction()

# SHARED, STATIC or BOTH for one component.
function(halif_library_type comp out)
    if(DEFINED HALIF_LIBRARY_TYPE_${comp})
        set(type "${HALIF_LIBRARY_TYPE_${comp}}")
    else()
        set(type "${HALIF_LIBRARY_TYPE}")
    endif()
    string(TOUPPER "${type}" type)
    if(type STREQUAL "")
        set(type SHARED)
    endif()
    if(NOT type MATCHES "^(SHARED|STATIC|BOTH)$")
        message(FATAL_ERROR "HALIF_LIBRARY_TYPE for ${comp} is '${type}'; use SHARED, STATIC or BOTH")
    endif()
    set(${out} "${type}" PARENT_SCOPE)
endfunction()

# Every node <comp>@<ver> depends on, directly or not.
function(_halif_closure node out)
    set(seen "")
    set(queue "${node}")
    while(NOT queue STREQUAL "")
        list(POP_FRONT queue n)
        halif_node_deps("${n}" deps)
        foreach(d IN LISTS deps)
            if(NOT d IN_LIST seen)
                list(APPEND seen "${d}")
                list(APPEND queue "${d}")
            endif()
        endforeach()
    endwhile()
    set(${out} "${seen}" PARENT_SCOPE)
endfunction()

# Build-time generation of <comp>/<ver>/{include,src}.
#
# The toolchain is given only this node's directory and those of its
# dependencies as interface roots, so it resolves exactly this (component,
# version) and writes into its directory. Each .aidl yields one .cpp of the
# same relative path, which is what lets the outputs be declared up front.
#
# A current node is generated as part of the normal build; OUT_SOURCES receives
# its .cpp files. A released node only gets the halif-generate-<comp>-<ver>
# target; OUT_SOURCES is left empty.
function(_halif_add_generation comp ver out_sources)
    set(node "${comp}@${ver}")
    set(dir "${HALIF_ROOT}/${comp}/${ver}")
    set(gen_tgt "halif-generate-${comp}-${ver}")

    file(GLOB_RECURSE aidls CONFIGURE_DEPENDS "${dir}/com/*.aidl")
    if(NOT aidls)
        message(FATAL_ERROR "${node}: no .aidl under ${dir}/com")
    endif()

    set(roots -r "${dir}")
    set(inputs ${aidls} "${dir}/interface.yaml")
    _halif_closure("${node}" closure)
    foreach(d IN LISTS closure)
        halif_node_split("${d}" dc dv)
        list(APPEND roots -r "${HALIF_ROOT}/${dc}/${dv}")
        file(GLOB_RECURSE dep_aidls CONFIGURE_DEPENDS "${HALIF_ROOT}/${dc}/${dv}/com/*.aidl")
        list(APPEND inputs ${dep_aidls})
    endforeach()

    set(cpps "")
    foreach(a IN LISTS aidls)
        file(RELATIVE_PATH rel "${dir}" "${a}")
        string(REGEX REPLACE "\\.aidl$" ".cpp" rel "${rel}")
        list(APPEND cpps "${dir}/src/${rel}")
    endforeach()

    if(HALIF_AIDL_OPS)
        set(generate
            COMMAND "${CMAKE_COMMAND}" -E rm -rf "${dir}/src" "${dir}/include"
            COMMAND "${CMAKE_COMMAND}" -E env AIDL_VERSIONING_SKIP_DIR=out,build
                    "${Python3_EXECUTABLE}" "${HALIF_AIDL_OPS}" -g ${roots}
                    -o "${CMAKE_BINARY_DIR}/aidl/${comp}/${ver}" "${comp}")
    else()
        set(generate
            COMMAND "${CMAKE_COMMAND}" -E echo
                "${node}: the linux_binder_idl toolchain was not found (HOST_AIDL_DIR=${HOST_AIDL_DIR}). Run ./build_binder.sh."
            COMMAND "${CMAKE_COMMAND}" -E false)
    endif()

    if(ver STREQUAL "current")
        add_custom_command(
            OUTPUT ${cpps}
            ${generate}
            DEPENDS ${inputs}
            WORKING_DIRECTORY "${HALIF_ROOT}"
            COMMENT "Generating ${node} bindings into ${comp}/${ver}"
            VERBATIM)
        add_custom_target(${gen_tgt} DEPENDS ${cpps})
        set(${out_sources} "${cpps}" PARENT_SCOPE)
    else()
        # Explicit request only: rewrites committed files, so never part of ALL
        # and never a declared output that a clean would delete.
        add_custom_target(${gen_tgt}
            ${generate}
            WORKING_DIRECTORY "${HALIF_ROOT}"
            COMMENT "Regenerating ${node} bindings into ${comp}/${ver}"
            VERBATIM)
        set(${out_sources} "" PARENT_SCOPE)
    endif()
    add_dependencies(halif-generate ${gen_tgt})
endfunction()

# The library of <dep_node> to link from a library of kind <want> (SHARED or
# STATIC): the same kind when the dependency builds it, otherwise the other.
function(_halif_dep_target dep_node want out)
    halif_node_split("${dep_node}" dc dv)
    get_property(kinds GLOBAL PROPERTY "HALIF_KINDS[${dep_node}]")
    if(want IN_LIST kinds)
        set(kind "${want}")
    else()
        list(GET kinds 0 kind)
    endif()
    if(kind STREQUAL "STATIC")
        set(${out} "${dc}-v${dv}-cpp-static" PARENT_SCOPE)
    else()
        set(${out} "${dc}-v${dv}-cpp" PARENT_SCOPE)
    endif()
endfunction()

function(halif_add_module)
    cmake_parse_arguments(PARSE_ARGV 0 M "" "NAME;VERSION" "DEPENDENCIES")
    set(comp "${M_NAME}")
    set(ver "${M_VERSION}")
    set(node "${comp}@${ver}")
    set(src_dir "${HALIF_ROOT}/${comp}/${ver}")
    set(inc_dir "${src_dir}/include")
    set(cpp_dir "${src_dir}/src")
    set(tgt "${comp}-v${ver}-cpp")
    _halif_capitalize("${comp}" Comp)
    set(pkg "RdkHalifAidl${Comp}")

    halif_library_type("${comp}" type)
    if(type STREQUAL "BOTH")
        set(kinds SHARED STATIC)
    else()
        set(kinds ${type})
    endif()
    set_property(GLOBAL PROPERTY "HALIF_KINDS[${node}]" "${kinds}")

    _halif_add_generation("${comp}" "${ver}" srcs)
    if(NOT srcs)
        file(GLOB_RECURSE srcs CONFIGURE_DEPENDS "${cpp_dir}/*.cpp")
        if(NOT srcs)
            message(FATAL_ERROR "${node}: no sources under ${cpp_dir}")
        endif()
    endif()

    set(inc_install "${CMAKE_INSTALL_INCLUDEDIR}/rdk-halif-aidl/${comp}/${ver}")
    set(src_install "src/rdk-halif-aidl/${comp}/${ver}")
    set(pkg_install "${CMAKE_INSTALL_LIBDIR}/cmake/${pkg}-${ver}")

    set(find_deps "")
    set(pc_requires "")
    set(gen_deps "")
    foreach(dep IN LISTS M_DEPENDENCIES)
        halif_node_split("${dep}" dc dv)
        _halif_capitalize("${dc}" DComp)
        # A dependency is the exact version this snapshot was frozen against:
        # one process holds one version of each component.
        if(dv MATCHES "${_HALIF_VER_RE}")
            string(APPEND find_deps "find_dependency(RdkHalifAidl${DComp} ${dv} EXACT)\n")
        else()
            string(APPEND find_deps "find_dependency(RdkHalifAidl${DComp})\n")
        endif()
        list(APPEND pc_requires "rdk-halif-aidl-${dc}-${dv}")
    endforeach()
    # Generation of this node and of every current dependency, direct or not,
    # finishes before this node compiles. For this node it also keeps a second
    # copy of the generate rule (Makefile generators attach one per consuming
    # target) from running in parallel with the first.
    _halif_closure("${node}" closure)
    foreach(dep IN ITEMS ${node} ${closure})
        if(dep MATCHES "@current$")
            string(REPLACE "@" "-" d "${dep}")
            list(APPEND gen_deps "halif-generate-${d}")
        endif()
    endforeach()

    # Compile once, so the generated sources have one owning target; wrap the
    # objects as each requested library type.
    set(objs "${tgt}-objs")
    add_library(${objs} OBJECT ${srcs})
    target_include_directories(${objs} SYSTEM PRIVATE "${inc_dir}")
    set_target_properties(${objs} PROPERTIES
        CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON POSITION_INDEPENDENT_CODE ON)
    if(gen_deps)
        add_dependencies(${objs} ${gen_deps})
    endif()

    set(targets "")
    foreach(kind IN LISTS kinds)
        if(kind STREQUAL "STATIC")
            set(t "${tgt}-static")
        else()
            set(t "${tgt}")
        endif()
        set(dep_libs "")
        foreach(dep IN LISTS M_DEPENDENCIES)
            _halif_dep_target("${dep}" "${kind}" dl)
            list(APPEND dep_libs "${dl}")
        endforeach()
        add_library(${t} ${kind} $<TARGET_OBJECTS:${objs}>)
        target_link_libraries(${t} PUBLIC Binder::Binder ${dep_libs})
        target_include_directories(${t} SYSTEM PUBLIC
            "$<BUILD_INTERFACE:${inc_dir}>"
            "$<INSTALL_INTERFACE:${inc_install}>")
        set_target_properties(${t} PROPERTIES
            OUTPUT_NAME "${tgt}"
            EXPORT_NAME "${t}"
            CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON POSITION_INDEPENDENT_CODE ON)
        if(kind STREQUAL "SHARED")
            set_target_properties(${t} PROPERTIES INSTALL_RPATH "${HALIF_INSTALL_RPATH}")
        endif()
        add_library(RdkHalifAidl::${t} ALIAS ${t})
        list(APPEND targets ${t})
    endforeach()
    # The objects compile against Binder's headers and the dependencies'.
    target_link_libraries(${objs} PRIVATE Binder::Binder ${dep_libs})
    list(GET targets 0 primary)

    # Install: library, headers, contract + sources, CMake package, pkg-config.
    install(TARGETS ${targets} EXPORT ${pkg}-${ver}Targets
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
    set(HALIF_PRIMARY "${primary}")
    set(HALIF_COMP "${comp}")
    set(HALIF_COMP_CAP "${Comp}")
    set(HALIF_VER "${ver}")
    set(HALIF_FIND_DEPS "${find_deps}")
    set(HALIF_INC_INSTALL "${inc_install}")
    set(HALIF_SRC_INSTALL "${src_install}")
    set(HALIF_LIB_VARS "")
    if("SHARED" IN_LIST kinds)
        string(APPEND HALIF_LIB_VARS "set(${pkg}_SHARED_LIBRARIES RdkHalifAidl::${tgt})\n")
    endif()
    if("STATIC" IN_LIST kinds)
        string(APPEND HALIF_LIB_VARS "set(${pkg}_STATIC_LIBRARIES RdkHalifAidl::${tgt}-static)\n")
    endif()
    configure_package_config_file(
        "${_HALIF_TEMPLATES}/Config.cmake.in"
        "${gen_pkg}/${pkg}Config.cmake"
        INSTALL_DESTINATION "${pkg_install}"
        PATH_VARS HALIF_INC_INSTALL HALIF_SRC_INSTALL)
    set(pkg_files "${gen_pkg}/${pkg}Config.cmake")
    if(ver MATCHES "${_HALIF_VER_RE}")
        # Versions are 0.<major>.<minor>.<bugfix>: the interface's major is
        # CMake's second component. A consumer requesting 0.2.1.0 accepts
        # 0.2.1.0 and later 0.2.x.x, never 0.3.x.x — same major, at or above
        # the minor (wiki: HAL Version Use Cases, cases 2, 3, 8, 9).
        write_basic_package_version_file(
            "${gen_pkg}/${pkg}ConfigVersion.cmake"
            VERSION "${ver}"
            COMPATIBILITY SameMinorVersion)
        list(APPEND pkg_files "${gen_pkg}/${pkg}ConfigVersion.cmake")
    endif()
    install(FILES ${pkg_files} DESTINATION "${pkg_install}")

    # pkg-config. linux_binder_idl ships no binder.pc, so the Binder SDK paths
    # resolved at configure time are written in directly. -l<name> resolves to
    # whichever of the .so / .a this component installs.
    get_filename_component(binder_libdir "${Binder_LIBRARY}" DIRECTORY)
    set(HALIF_TGT "${tgt}")
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
