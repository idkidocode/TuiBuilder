# Getting Started With TuiBuilder

To get started with TuiBuilder you must add it to cmake
```cmake
#Adding TuiBuilder to cmake

cmake_minimum_required(VERSION 3.15)
project(TuiBuilderExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    TuiBuilder
    GIT_REPOSITORY https://github.com/idkidocode/TuiBuilder.git
    GIT_TAG main
)
FetchContent_MakeAvailable(TuiBuilder)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE TuiBuilder)
```