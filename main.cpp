#include <SDL2/SDL.h>   // pulls in SDL_main.h, which renames main -> SDL_main on Windows
#include "app.h"

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    Theme theme = Theme::Midnight();

    App app(670, 580, 18, theme);
    app.Start();

    return 0;
}
