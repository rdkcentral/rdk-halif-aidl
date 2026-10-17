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

# HalifResolve — decide WHAT to build.
#
# Inputs are the two files the repository already carries:
#
#   versions_*.yaml                 default: <ver>
#                                   components: {<comp>: <ver>}
#   <comp>/<ver>/interface.yaml     imports: [- <dep>@<ver>]
#
# The manifest pins TOP-LEVEL versions only. A dependency is built at the
# version its dependent's interface.yaml imports — the version the snapshot was
# frozen against — so two versions of one component coexist in one plan when
# two dependents import different ones. The plan is keyed by (component, version).
#
# Entry point:
#
#   halif_resolve_plan(MANIFEST <path|""> COMPONENTS <list> OUT_PLAN <var>)
#
#   COMPONENTS entries are "<comp>" or "<comp>:<ver>". Empty COMPONENTS means
#   every component the manifest pins; with no manifest either, every component
#   in the tree. A component with no version anywhere resolves to the manifest
#   default, or to its latest released snapshot when there is no manifest.
#
#   OUT_PLAN receives "<comp>@<ver>" nodes in build order (dependencies first).
#   halif_node_deps(<node> <var>) returns a node's direct dependencies.
#   halif_node_split(<node> <comp_var> <ver_var>) splits a node.

include_guard(GLOBAL)
if(POLICY CMP0174)
    cmake_policy(SET CMP0174 NEW)   # an empty single-value argument stays defined and empty
endif()

get_filename_component(HALIF_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(_HALIF_VER_RE "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$")

function(halif_node_split node out_comp out_ver)
    string(REPLACE "@" ";" pair "${node}")
    list(GET pair 0 c)
    list(GET pair 1 v)
    set(${out_comp} "${c}" PARENT_SCOPE)
    set(${out_ver} "${v}" PARENT_SCOPE)
endfunction()

function(halif_node_deps node out)
    get_property(deps GLOBAL PROPERTY "HALIF_DEPS[${node}]")
    set(${out} "${deps}" PARENT_SCOPE)
endfunction()

# Every component directory: one that has a current/interface.yaml.
function(halif_all_components out)
    file(GLOB files RELATIVE "${HALIF_ROOT}" "${HALIF_ROOT}/*/current/interface.yaml")
    set(comps "")
    foreach(f IN LISTS files)
        string(REGEX REPLACE "/current/interface.yaml$" "" c "${f}")
        list(APPEND comps "${c}")
    endforeach()
    list(SORT comps)
    set(${out} "${comps}" PARENT_SCOPE)
endfunction()

# Released snapshots of a component, ascending. A snapshot is a directory named
# X.Y.Z.W that carries an interface.yaml.
function(halif_released_versions comp out)
    file(GLOB dirs LIST_DIRECTORIES true "${HALIF_ROOT}/${comp}/*")
    set(vers "")
    foreach(d IN LISTS dirs)
        get_filename_component(v "${d}" NAME)
        if(v MATCHES "${_HALIF_VER_RE}" AND EXISTS "${d}/interface.yaml")
            list(APPEND vers "${v}")
        endif()
    endforeach()
    list(SORT vers COMPARE NATURAL)
    set(${out} "${vers}" PARENT_SCOPE)
endfunction()

# Parse a versions manifest. out_pins receives "<comp>@<ver>" entries; a
# component listed with no version takes the manifest default.
function(halif_read_manifest path out_default out_pins)
    if(NOT EXISTS "${path}")
        message(FATAL_ERROR "HALIF_VERSIONS_FILE not found: ${path}")
    endif()
    file(STRINGS "${path}" lines)
    set(default "current")
    set(pins "")
    set(in_map FALSE)
    foreach(line IN LISTS lines)
        string(REGEX REPLACE "#.*$" "" line "${line}")
        if(line MATCHES "^[ \t]*$")
            continue()
        elseif(line MATCHES "^default:[ \t]*([^ \t]+)")
            set(default "${CMAKE_MATCH_1}")
            set(in_map FALSE)
        elseif(line MATCHES "^components:[ \t]*$")
            set(in_map TRUE)
        elseif(in_map AND line MATCHES "^[ \t]+([A-Za-z0-9_]+):[ \t]*([^ \t]*)")
            list(APPEND pins "${CMAKE_MATCH_1}@${CMAKE_MATCH_2}")
        elseif(NOT line MATCHES "^[ \t]")
            set(in_map FALSE)
        endif()
    endforeach()
    set(resolved "")
    foreach(p IN LISTS pins)
        if(p MATCHES "@$")
            string(APPEND p "${default}")
        endif()
        list(APPEND resolved "${p}")
    endforeach()
    set(${out_default} "${default}" PARENT_SCOPE)
    set(${out_pins} "${resolved}" PARENT_SCOPE)
endfunction()

# Direct sibling dependencies of <comp>@<ver> from its interface.yaml. Imports
# that are not a component of this tree (toolchain-provided AIDL such as
# android.hardware.common.*) are the generator's concern and are skipped.
function(halif_imports comp ver out)
    set(f "${HALIF_ROOT}/${comp}/${ver}/interface.yaml")
    file(STRINGS "${f}" lines)
    set(deps "")
    set(in_imports FALSE)
    foreach(line IN LISTS lines)
        string(REGEX REPLACE "#.*$" "" line "${line}")
        if(line MATCHES "^[ \t]*imports:[ \t]*$")
            set(in_imports TRUE)
        elseif(in_imports AND line MATCHES "^[ \t]*-[ \t]*([A-Za-z0-9_.]+)@([^ \t]+)")
            if(IS_DIRECTORY "${HALIF_ROOT}/${CMAKE_MATCH_1}")
                list(APPEND deps "${CMAKE_MATCH_1}@${CMAKE_MATCH_2}")
            endif()
        elseif(in_imports AND NOT line MATCHES "^[ \t]*-")
            set(in_imports FALSE)
        endif()
    endforeach()
    set(${out} "${deps}" PARENT_SCOPE)
endfunction()

# Fail unless <comp>@<ver> names a snapshot that exists in the tree.
function(_halif_check_node node origin)
    halif_node_split("${node}" comp ver)
    if(NOT IS_DIRECTORY "${HALIF_ROOT}/${comp}")
        message(FATAL_ERROR "${origin}: '${comp}' is not a component of this tree")
    endif()
    if(ver STREQUAL "current")
        if(NOT EXISTS "${HALIF_ROOT}/${comp}/current/interface.yaml")
            message(FATAL_ERROR "${origin}: ${comp} has no current/ interface")
        endif()
        return()
    endif()
    halif_released_versions("${comp}" released)
    if(NOT ver IN_LIST released)
        string(REPLACE ";" " " avail "${released}")
        message(FATAL_ERROR "${origin}: ${comp}@${ver} is not a released snapshot (released: ${avail}; or 'current')")
    endif()
    if(NOT IS_DIRECTORY "${HALIF_ROOT}/${comp}/${ver}/src" OR NOT IS_DIRECTORY "${HALIF_ROOT}/${comp}/${ver}/include")
        message(FATAL_ERROR "${origin}: ${comp}@${ver} carries no generated bindings (include/, src/)")
    endif()
endfunction()

function(halif_resolve_plan)
    cmake_parse_arguments(PARSE_ARGV 0 R "" "MANIFEST;OUT_PLAN" "COMPONENTS")
    if(NOT DEFINED R_MANIFEST)
        set(R_MANIFEST "")
    endif()

    # 1. Manifest → top-level pins.
    set(default "")
    set(pins "")
    if(NOT "${R_MANIFEST}" STREQUAL "")
        halif_read_manifest("${R_MANIFEST}" default pins)
    endif()

    # 2. Selection → seed nodes. COMPONENTS may arrive as one argument holding
    # a ;-list (a -D cache value) or as several arguments; treat both as a list.
    string(REPLACE "\\;" ";" items "${R_COMPONENTS}")
    if(items STREQUAL "")
        if(NOT pins STREQUAL "")
            foreach(p IN LISTS pins)
                halif_node_split("${p}" c v)
                list(APPEND items "${c}")
            endforeach()
        else()
            halif_all_components(items)
        endif()
    endif()

    set(seed "")
    foreach(item IN LISTS items)
        if(item MATCHES "^([A-Za-z0-9_]+):(.+)$")
            set(c "${CMAKE_MATCH_1}")
            set(v "${CMAKE_MATCH_2}")
        else()
            set(c "${item}")
            set(v "")
            foreach(p IN LISTS pins)
                if(p MATCHES "^${c}@(.+)$")
                    set(v "${CMAKE_MATCH_1}")
                endif()
            endforeach()
            if(v STREQUAL "")
                if(NOT default STREQUAL "")
                    set(v "${default}")
                else()
                    halif_released_versions("${c}" released)
                    if(released STREQUAL "")
                        set(v "current")
                    else()
                        list(GET released -1 v)
                    endif()
                endif()
            endif()
        endif()
        _halif_check_node("${c}@${v}" "HALIF_COMPONENTS")
        list(APPEND seed "${c}@${v}")
    endforeach()
    list(REMOVE_DUPLICATES seed)

    # 3. Closure over imports, keyed by (component, version).
    set(nodes "${seed}")
    set(queue "${seed}")
    while(NOT queue STREQUAL "")
        list(POP_FRONT queue node)
        halif_node_split("${node}" c v)
        halif_imports("${c}" "${v}" deps)
        foreach(dep IN LISTS deps)
            halif_node_split("${dep}" dc dv)
            if(NOT v STREQUAL "current" AND dv STREQUAL "current")
                message(WARNING "${c}@${v} is a released snapshot but imports ${dep}; its interface.yaml needs refreezing")
            endif()
            _halif_check_node("${dep}" "${c}@${v} imports")
            if(NOT dep IN_LIST nodes)
                list(APPEND nodes "${dep}")
                list(APPEND queue "${dep}")
            endif()
        endforeach()
        set_property(GLOBAL PROPERTY "HALIF_DEPS[${node}]" "${deps}")
    endwhile()

    # 4. Topological order (Kahn), alphabetical among ready nodes.
    set(remaining "${nodes}")
    set(ordered "")
    while(NOT remaining STREQUAL "")
        set(ready "")
        foreach(node IN LISTS remaining)
            halif_node_deps("${node}" deps)
            set(blocked FALSE)
            foreach(dep IN LISTS deps)
                if(NOT dep IN_LIST ordered)
                    set(blocked TRUE)
                endif()
            endforeach()
            if(NOT blocked)
                list(APPEND ready "${node}")
            endif()
        endforeach()
        if(ready STREQUAL "")
            string(REPLACE ";" " " cyc "${remaining}")
            message(FATAL_ERROR "dependency cycle among: ${cyc}")
        endif()
        list(SORT ready)
        list(APPEND ordered ${ready})
        list(REMOVE_ITEM remaining ${ready})
    endwhile()

    set(${R_OUT_PLAN} "${ordered}" PARENT_SCOPE)
endfunction()
