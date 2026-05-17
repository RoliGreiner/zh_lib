//
// Created by larix on 2026. 05. 17..
//

#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "scene.h"

class Slider;
class GameScene;

class MenuScene : public Scene {
    Slider* size_slider;
    GameScene* game_scene;

public:
    MenuScene(App* app);

    void SetGameScene(GameScene* scene) { game_scene = scene; }
};

#endif //MENU_SCENE_H