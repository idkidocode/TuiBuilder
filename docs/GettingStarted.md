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

## Menu Builder
To use the menu build you can create a class like this

```c++
TuiBuilder::MenuBuilder menu;
```

You will need to run some functions to set up the menu

```c++
menu.SetOptions({"Option 1", "Option 2", "Option 3"}); //Text Options
meun.SetActions({
    []() { /* action 1 */},
    []() { /* action 2 */},
    []() { /* action 3 */},
}); //Functions that run when the corresponding option is selected
```

There are also some optional settings

```c++
menu.SetEndChar("q"); //Will change what button is used to exit the menu, default is 'q'
```

The Main loop for runing the menu is:
```c++
menuBuilder.Init(); //Initialize the menu(ncurses)
    menuBuilder.Update(); //Update the menu and wait for user input
menuBuilder.End(); //End the menu
```