find_package(Qt6 COMPONENTS
        Core
        REQUIRED)

include_directories(../lib/include)

add_executable(mcm
        main.cpp
        Task.cpp
        Task.h
        command/BaseCommand.cpp
        command/ApplyCommand.cpp
        command/DeleteCommand.cpp
        command/ListCommand.cpp
        command/SaveCommand.cpp
        command/Commands.cpp
)

target_link_libraries(mcm
        PRIVATE
        Qt::Core
        mcm-core
)

install(TARGETS mcm
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE  DESTINATION .
        COMPONENT runtime
)
