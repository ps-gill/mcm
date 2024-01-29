cmake_minimum_required(VERSION 3.22)

project(mcm
    LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include(GNUInstallDirs)

set(MCM_VERSION_MAJOR "0")
set(MCM_VERSION_MINOR "1")
set(MCM_VERSION_PATCH "0")
set(MCM_VERSION "${MCM_VERSION_MAJOR}.${MCM_VERSION_MINOR}.${MCM_VERSION_PATCH}")

add_subdirectory(src)
add_subdirectory(dist)
