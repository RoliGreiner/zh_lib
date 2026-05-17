#include "app.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "end_scene.h"

int main() {
    App app(1200, 1000);

    MenuScene* menu = new MenuScene(&app);
    GameScene* game = new GameScene(&app);
    EndScene* end = new EndScene(&app);

    app.AddScene(menu);
    app.AddScene(game);
    app.AddScene(end);

    menu->SetGameScene(game);
    game->SetEndScene(end);
    game->SetMenuScene(menu);
    end->SetMenuScene(menu);

    app.SwitchTo(menu);
    app.Start();

    return 0;
}