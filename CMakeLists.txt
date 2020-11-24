cmake_minimum_required(VERSION 3.5)

project(emoji_picker)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(emoji_picker src/main.cpp src/app.cpp src/app.hpp 
src/input.cpp src/input.hpp
src/FlowLayout.cpp src/FlowLayout.hpp)

target_link_libraries(emoji_picker Qt5::Widgets)
