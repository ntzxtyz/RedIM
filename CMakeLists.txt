cmake_minimum_required(VERSION 3.20)
project(RedIM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(-g)
include_directories(include)
find_package(Qt5 COMPONENTS Gui Widgets Network REQUIRED)

add_executable(RedIM main.cpp Connection.hpp)
target_link_libraries(RedIM
        Qt5::Gui Qt5::Network Qt5::Widgets
        )

