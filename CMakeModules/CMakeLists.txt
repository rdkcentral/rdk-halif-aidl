include(GNUInstallDirs)

install(FILES "FindBinder.cmake" DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/Modules")
install(FILES "FindAndroidUtils.cmake" DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/Modules")
install(FILES "${CMAKE_SOURCE_DIR}/contrib/binder.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/")
install(FILES "${CMAKE_SOURCE_DIR}/contrib/utils.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/")
