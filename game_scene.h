//
// Created by larix on 2026. 05. 17..
//

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"
#include "game_master.h"
#include "ai_player.h"
#include <vector>

using namespace std;

class Container;
class Label;
class EndScene;
class MenuScene;

class GameScene : public Scene {
    GameMaster game;
    AIPlayer ai;

    vector<vector<Container*>> board_cells;

    Label* turn_label;
    EndScene* end_scene;
    MenuScene* menu_scene;

    bool two_player;

    void HandleCellClick(int row, int column);
    void ApplyMove(int row, int column);
    void TriggerAIMove();
    void BuildBoard(int board_size);
    void UpdateTurnIndicator();
    void PlaceMarkAt(int row, int column, char mark);
    bool CheckGameEnd();

public:
    GameScene(App* app);

    void StartNewGame(int board_size, bool two_player);
    void SetEndScene(EndScene* scene) { end_scene = scene; }
    void SetMenuScene(MenuScene* scene) { menu_scene = scene; }
};

#endif //GAME_SCENE_H