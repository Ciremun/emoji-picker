cmake_minimum_required(VERSION 3.0.0)
project(emoji_picker VERSION 0.0.1)

if(WIN32)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_VERBOSE_MAKEFILE TRUE)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    set(CMAKE_WIN32_EXECUTABLE ON)
else()
    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
    include(CPack)
endif()

set(platform_dir ${CMAKE_SYSTEM_NAME}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION})
foreach(config DEBUG RELEASE)
    foreach(var CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config} CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config} CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config})
        set(${var} "${CMAKE_BINARY_DIR}/${platform_dir}-${config}")
    endforeach()
endforeach()

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(sources src/main.cpp src/app.cpp src/app.hpp 
src/flowlayout.cpp src/flowlayout.hpp 
src/tab.cpp src/tab.hpp 
src/emojis.hpp 
src/search.cpp src/search.hpp)

if(WIN32)
    set(sources ${sources} src/input_win.cpp src/input_win.hpp)
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
    set(sources ${sources} src/input_X11.cpp src/input_X11.hpp)
endif()

add_executable(emoji_picker ${sources})

if(NOT WIN32)
    target_link_libraries(emoji_picker -lX11 -lXtst)
endif()

target_link_libraries(emoji_picker Qt5::Widgets)
