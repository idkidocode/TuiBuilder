# TuiBuilder

A simple C++ library for building Terminal User Interfaces (TUIs).

TuiBuilder provides reusable components for creating interactive terminal applications without having to deal with ncurses directly.

## Features

* Simple C++ API
* Built on top of ncurses
* C++17 support
* CMake support
* Reusable UI components
* Lightweight and easy to integrate

## Requirements

* C++17 or newer
* CMake 3.15+
* ncurses

## Building

```bash
git clone https://github.com/idkidocode/TuiBuilder.git
cd TuiBuilder

cmake -B build
cmake --build build
```

## Usage
```cmake
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

See the repository examples for more usage.

## License

See [LICENSE](LICENSE).
