//
// Created by larix on 2026. 05. 17..
//

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"
#include "game_master.h"
#include <vector>

using namespace std;

class Container;
class Label;
class EndScene;

class GameScene : public Scene {
    GameMaster game;

    vector<vector<Container*>> board_cells;

    Label* turn_label;
    EndScene* end_scene;

    bool two_player;

    void HandleCellClick(int row, int column);
    void BuildBoard(int board_size);
    void UpdateTurnIndicator();
    void PlaceMarkAt(int row, int column, char mark);

public:
    GameScene(App* app);

    void StartNewGame(int board_size, bool two_player);
    void SetEndScene(EndScene* scene) { end_scene = scene; }
};

#endif //GAME_SCENE_H