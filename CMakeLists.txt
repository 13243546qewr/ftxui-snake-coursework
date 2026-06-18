cmake_minimum_required(VERSION 3.16)

project(FTXUISnakeCoursework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v5.0.0
)

FetchContent_MakeAvailable(ftxui)

add_executable(ftxui_snake
  src/main.cpp
  src/SnakeGame.cpp
)

target_include_directories(ftxui_snake PRIVATE include)

target_link_libraries(ftxui_snake
  PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
)
