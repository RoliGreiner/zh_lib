cmake_minimum_required(VERSION 3.8)

project(zh_lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SDL2 REQUIRED)

add_executable(main
        main.cpp
        graphics.cpp
        widget.cpp
        app.cpp
        button.cpp
        slider.cpp
        text_input.cpp
        text_field.cpp
        list.cpp
        label.cpp
        container.cpp
)

target_link_libraries(main SDL2 SDL2_ttf)