//
// Created by larix on 2026. 05. 17..
//

#include "game_scene.h"
#include "end_scene.h"
#include "menu_scene.h"
#include "app.h"
#include "container.h"
#include "label.h"
#include "button.h"
#include <algorithm>

GameScene::GameScene(App* app)
: Scene(app), game(15), ai('O'), turn_label(nullptr), end_scene(nullptr), menu_scene(nullptr), two_player(true) {
}

void GameScene::StartNewGame(int board_size, bool two_player_mode) {
    two_player = two_player_mode;
    game.Reset(board_size);
    BuildBoard(board_size);
    UpdateTurnIndicator();
}

void GameScene::BuildBoard(int board_size) {
    ClearWidgets();
    board_cells.clear();
    turn_label = nullptr;

    WidgetScope scope(app, this);

    const int right_panel_width = 220;
    int available_width = app->Width() - right_panel_width - 60;
    int available_height = app->Height() - 80;
    int cell_size = min(available_width / board_size, available_height / board_size);

    int board_pixel = cell_size * board_size;
    int board_left = 30;
    int board_top = (app->Height() - board_pixel) / 2;

    board_cells.assign(board_size, vector<Container*>(board_size, nullptr));
    for (int row = 0; row < board_size; row++) {
        for (int column = 0; column < board_size; column++) {
            int cell_x = board_left + column * cell_size + cell_size / 2;
            int cell_y = board_top  + row * cell_size + cell_size / 2;

            Container* cell = new Container(
                app,
                {cell_x, cell_y},
                {cell_size, cell_size},
                {255, 255, 255},
                {200, 60, 60});
            cell->SetOnClick([this, row, column]{ HandleCellClick(row, column); });
            board_cells[row][column] = cell;
        }
    }

    int panel_x = app->Width() - right_panel_width / 2 - 20;

    turn_label = new Label(
        app,
        {panel_x, 80},
        {200, 50},
        {255, 255, 255},
        "X jön",
        28);

    new Button(
        app,
        {panel_x, app->Height() - 100},
        {180, 50},
        {240, 220, 220},
        "Főmenü",
        [this]{
            if (menu_scene)
                this->app->SwitchTo(menu_scene);
        });
}

void GameScene::PlaceMarkAt(int row, int column, char mark) {
    if (!board_cells[row][column])
        return;

    Container* cell = board_cells[row][column];
    string mark_text(1, mark);

    Label* mark_label = new Label(
        app,
        {0, 0},
        {0, 0},
        {255, 255, 255},
        mark_text,
        max(10, int(cell->GetSize().y * 0.7)),
        true);
    cell->AttachWidget(mark_label);
}

void GameScene::ApplyMove(int row, int column) {
    char player = game.CurrentPlayer();
    if (!game.TryMove(row, column))
        return;
    PlaceMarkAt(row, column, player);
}

bool GameScene::CheckGameEnd() {
    if (game.GetState() == GameMaster::State::Playing)
        return false;

    if (end_scene) {
        end_scene->SetResult(game.GetState());
        app->SwitchTo(end_scene);
    }
    return true;
}

void GameScene::TriggerAIMove() {
    int row, column;
    if (!ai.ChooseMove(game, row, column))
        return;
    ApplyMove(row, column);
}

void GameScene::HandleCellClick(int row, int column) {
    ApplyMove(row, column);

    if (CheckGameEnd())
        return;

    if (!two_player && game.CurrentPlayer() == 'O') {
        TriggerAIMove();
        if (CheckGameEnd())
            return;
    }

    UpdateTurnIndicator();
}

void GameScene::UpdateTurnIndicator() {
    if (!turn_label)
        return;

    turn_label->SetText(game.CurrentPlayer() == 'X' ? "X jön" : "O jön");
}