cmake_minimum_required(VERSION 3.8)

project(zh_lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SDL2 REQUIRED)

link_libraries(SDL2 SDL2_ttf)
add_library(graphics graphics.cpp)
add_library(widget widget.cpp)
add_library(button button.cpp)
add_library(slider slider.cpp)
add_library(text_input text_input.cpp)
add_library(text_field text_field.cpp)
add_library(list list.cpp)
add_library(app app.cpp)


add_executable(main main.cpp)
target_link_libraries(widget PUBLIC app)
target_link_libraries(button PUBLIC widget)
target_link_libraries(app PUBLIC widget button list)
target_link_libraries(main button slider text_input text_field list widget app graphics)