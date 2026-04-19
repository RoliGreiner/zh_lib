cmake_minimum_required(VERSION 3.8)

project(zh_lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SDL2 REQUIRED)

link_libraries(SDL2 SDL2_ttf)
add_library(graphics graphics.cpp)
add_library(widget widget.cpp)


add_executable(main main.cpp)
target_link_libraries(main graphics widget)