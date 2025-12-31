# CMake script to stage SDK files to out/ directory
# Called as post-build step by custom target

message(STATUS "Staging SDK to ${OUT_DIR}...")

# Stage module libraries
file(MAKE_DIRECTORY "${OUT_DIR}/lib")
file(GLOB_RECURSE MODULE_LIBS "${BUILD_DIR}/**/lib*-vcurrent-cpp.so*")
foreach(lib ${MODULE_LIBS})
    file(COPY "${lib}" DESTINATION "${OUT_DIR}/lib")
endforeach()
list(LENGTH MODULE_LIBS NUM_LIBS)
message(STATUS "  Staged ${NUM_LIBS} module libraries")

# Stage module headers (preserving directory structure)
file(MAKE_DIRECTORY "${OUT_DIR}/include")
file(GLOB MODULE_DIRS "${STABLE_DIR}/generated/*/current/include")
foreach(inc_dir ${MODULE_DIRS})
    if(EXISTS "${inc_dir}")
        file(GLOB_RECURSE HEADERS "${inc_dir}/*.h")
        foreach(header ${HEADERS})
            file(RELATIVE_PATH rel_path "${inc_dir}" "${header}")
            get_filename_component(dest_dir "${OUT_DIR}/include/${rel_path}" DIRECTORY)
            file(MAKE_DIRECTORY "${dest_dir}")
            file(COPY "${header}" DESTINATION "${dest_dir}")
        endforeach()
    endif()
endforeach()

# Count staged files
file(GLOB_RECURSE STAGED_HEADERS "${OUT_DIR}/include/**/*.h")
list(LENGTH STAGED_HEADERS NUM_HEADERS)
message(STATUS "  Staged ${NUM_HEADERS} module headers")

message(STATUS "✓ SDK staging complete - ready for deployment")
