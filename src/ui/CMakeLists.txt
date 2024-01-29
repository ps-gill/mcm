find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(../lib/include)

add_executable(mcm-ui main.cpp)
target_link_libraries(mcm-ui
        PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        mcm-core
)
