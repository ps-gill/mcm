find_package(Qt6 REQUIRED COMPONENTS
        Core
        DBus)

configure_file(
        include/mcm/config.h.in
        ${CMAKE_CURRENT_SOURCE_DIR}/include/mcm/config.h
        @ONLY
)

set(libmcm_SOURCES
        types.cpp
        include/mcm/displayconfig.h
        displayconfig.cpp
        Mcm.cpp
        data/MonitorArrangement.cpp
        data/DataManager.cpp
)

add_library(mcm-core STATIC ${libmcm_SOURCES})
target_link_libraries(mcm-core
        Qt::Core
        Qt::DBus)
