cmake_minimum_required(VERSION 3.8)

project(zh_lib CXX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find SDL2. The MinGW dev packages ship a CMake config, and so do modern
# Linux distros, so find_package works for both native and cross builds.
find_package(SDL2 REQUIRED)

# SDL2_ttf ships a CMake config in the MinGW packages and on newer distros.
# Older Linux distros only provide a bare library, so we fall back to that.
find_package(SDL2_ttf QUIET)

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
        check_box.cpp
        spin_box.cpp
        progress_bar.cpp
)

# --- Link SDL2 -------------------------------------------------------------
# SDL2main (the Windows entry-point shim) must be linked BEFORE SDL2, because
# it's a static archive that references SDL_* symbols living in SDL2, and the
# linker only resolves an archive's references against libraries that come
# AFTER it on the command line.
if(TARGET SDL2::SDL2main)
    target_link_libraries(main SDL2::SDL2main)
endif()

if(TARGET SDL2::SDL2)
    target_link_libraries(main SDL2::SDL2)
else()
    # Very old SDL2 without a CMake config.
    target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(main ${SDL2_LIBRARIES})
endif()

# --- Link SDL2_ttf ---------------------------------------------------------
if(TARGET SDL2_ttf::SDL2_ttf)
    target_link_libraries(main SDL2_ttf::SDL2_ttf)
else()
    # Fallback for distros that don't ship an SDL2_ttf CMake config.
    find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf REQUIRED)
    target_link_libraries(main ${SDL2_TTF_LIBRARY})
endif()

# --- Windows / cross-compile only ------------------------------------------
# WIN32 is true when building with the MinGW toolchain file.
if(WIN32)
    # The MinGW SDL packages nest their headers under include/SDL2, and the
    # imported targets only put that inner folder on the search path. Add the
    # parent include/ dir so that #include <SDL2/SDL.h> and <SDL2/SDL_ttf.h>
    # resolve (matching how your code and the system SDL2 are laid out).
    if(DEFINED MINGW_SDL_ROOT)
        target_include_directories(main PRIVATE ${MINGW_SDL_ROOT}/include)
    endif()

    # Bake the GCC runtime into the .exe so friends don't need extra MinGW
    # DLLs (libstdc++-6.dll, libgcc_s_seh-1.dll, libwinpthread-1.dll).
    # If this ever fails to link, swap it for:
    #   -static-libgcc -static-libstdc++
    # (and the script-copied DLLs will cover the rest).
    target_link_options(main PRIVATE -static)

    # Copy SDL2.dll, SDL2_ttf.dll and their dependencies (freetype, zlib, ...)
    # next to the built main.exe so it runs on a clean Windows machine.
    if(DEFINED MINGW_SDL_ROOT)
        file(GLOB SDL_RUNTIME_DLLS "${MINGW_SDL_ROOT}/bin/*.dll")
        foreach(dll ${SDL_RUNTIME_DLLS})
            add_custom_command(TARGET main POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${dll}" "$<TARGET_FILE_DIR:main>"
                    COMMENT "Bundling ${dll}")
        endforeach()
    endif()

    # Optional: uncomment to hide the console window when friends double-click
    # the .exe (you lose std::cout output, useful to keep while debugging).
    # target_link_options(main PRIVATE -mwindows)
endif()
