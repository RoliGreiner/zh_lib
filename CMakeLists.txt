cmake_minimum_required(VERSION 3.8)

project(zh_lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SDL2 REQUIRED)

add_executable(main
        main.cpp
        graphics.cpp
        widget.cpp
        app.cpp
        scene.cpp
        button.cpp
        slider.cpp
        label.cpp
        container.cpp
        game_master.cpp
        menu_scene.cpp
        game_scene.cpp
        end_scene.cpp
)

target_link_libraries(main SDL2 SDL2_ttf)