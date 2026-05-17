//
// Created by larix on 2026. 05. 17..
//

#include "end_scene.h"
#include "game_scene.h"
#include "app.h"
#include "button.h"
#include "slider.h"
#include "label.h"
#include "menu_scene.h"

EndScene::EndScene(App* app)
: Scene(app), result_label(nullptr), menu_scene(nullptr) {
    WidgetScope scope(app, this);

    int center_x = app->Width() / 2;

    new Label(
        app,
        {center_x, 80},
        {app->Width(), 160},
        {50, 200, 200},
        "JÁTÉK VÉGE",
        50);

    result_label = new Label(
        app,
        {center_x, 200},
        {app->Width(), 80},
        {255, 215, 0},
        "",
        32);

    new Button(
        app,
        {center_x, 360},
        {250, 60},
        {100, 180, 100},
        "Főmenü",
        [this]{
            if (menu_scene)
                this->app->SwitchTo(menu_scene);
        });

    new Button(
        app,
        {center_x, 800},
        {200, 50},
        {255, 100, 100},
        "Kilépés",
        [this]{ this->app->Quit(); });
}

void EndScene::SetResult(GameMaster::State state) {
    if (!result_label)
        return;
    switch (state) {
        case GameMaster::State::XWon:
            result_label->SetText("X nyert!");
            break;
        case GameMaster::State::OWon:
            result_label->SetText("O nyert!");
            break;
        case GameMaster::State::Draw:
            result_label->SetText("Döntetlen");
            break;
        default:
            result_label->SetText("");
            break;
    }
}