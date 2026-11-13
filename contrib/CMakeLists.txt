include(GNUInstallDirs)

foreach(_pc_file IN ITEMS binder utils)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/${_pc_file}.pc"
        "${CMAKE_CURRENT_BINARY_DIR}/${_pc_file}.pc"
        @ONLY
    )
    install(
        FILES "${CMAKE_CURRENT_BINARY_DIR}/${_pc_file}.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
    )
endforeach()