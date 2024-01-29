install(DIRECTORY icons/192x192
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor
        COMPONENT data
)

install(FILES mcm.desktop
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications/
        COMPONENT data
)
