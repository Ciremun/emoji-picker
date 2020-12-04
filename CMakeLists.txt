cmake_minimum_required(VERSION 3.0.0)
project(emoji_picker VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    set(CMAKE_WIN32_EXECUTABLE ON)
    set(SOURCES ${SOURCES} src/input_win.cpp)
    set(HEADERS ${HEADERS} src/input_win.hpp)
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
    set(SOURCES ${SOURCES} src/input_X11.cpp)
    set(HEADERS ${HEADERS} src/input_X11.hpp)
endif()

set(platform_dir ${CMAKE_SYSTEM_NAME}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION})
foreach(config DEBUG RELEASE)
    foreach(var CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config} CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config} CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config})
        set(${var} "${CMAKE_BINARY_DIR}/${platform_dir}-${config}")
    endforeach()
endforeach()

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES ${SOURCES} src/main.cpp src/app.cpp src/flowlayout.cpp src/tab.cpp src/search.cpp src/search_tab.cpp)
set(HEADERS ${HEADERS} src/app.hpp src/flowlayout.hpp src/tab.hpp src/emojis.hpp src/search.hpp src/search_tab.hpp)

add_executable(emoji_picker ${SOURCES} ${HEADERS})

if(NOT WIN32)
    target_link_libraries(emoji_picker -lX11 -lXtst)
endif()

target_link_libraries(emoji_picker Qt5::Widgets)
