//
// Created by larix on 2026. 05. 17..
//

#ifndef END_SCENE_H
#define END_SCENE_H

#include "scene.h"
#include "game_master.h"

class Slider;
class Label;
class GameScene;

class EndScene : public Scene {
    Label* result_label;
    Slider* size_slider;
    GameScene* game_scene;

public:
    EndScene(App* app);

    void SetResult(GameMaster::State state);
    void SetGameScene(GameScene* scene) { game_scene = scene; }
};

#endif //END_SCENE_H