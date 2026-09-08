cmake_minimum_required(VERSION 3.15)
project(TuiBuilder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

file(GLOB_RECURSE TUIBUILDER_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(TuiBuilder STATIC ${TUIBUILDER_SOURCES})

target_include_directories(TuiBuilder PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(TuiBuilder PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(TuiBuilder PUBLIC ${CURSES_LIBRARIES})