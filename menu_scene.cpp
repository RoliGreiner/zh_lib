//
// Created by larix on 2026. 05. 17..
//

#include "menu_scene.h"
#include "game_scene.h"
#include "app.h"
#include "button.h"
#include "slider.h"
#include "label.h"

MenuScene::MenuScene(App* app) : Scene(app), size_slider(nullptr), game_scene(nullptr) {
    WidgetScope scope(app, this);

    int center_x = app->Width() / 2;

    new Label(
        app,
        {center_x, 50},
        {app->Width(), 100},
        {50, 200, 200},
        "AMŐBA",
        42);

    auto start_game = [this](bool two_player){
        if (!game_scene)
            return;
        int board_size = size_slider ? size_slider->GetValue() : 15;
        game_scene->StartNewGame(board_size, two_player);
        this->app->SwitchTo(game_scene);
    };

    new Button(
        app,
        {center_x, 280},
        {250, 60},
        {100, 180, 100},
        "Egyjátékos",
        [start_game]{ start_game(false); });

    new Button(
        app,
        {center_x, 360},
        {250, 60},
        {100, 180, 100},
        "Többjátékos",
        [start_game]{ start_game(true); });

    size_slider = CreateSizeSelector(center_x, 460, 15, 30, 15);

    new Button(
        app,
        {center_x, 800},
        {150, 50},
        {255, 100, 100},
        "Kilépés",
        [this]{ this->app->Quit(); });
}