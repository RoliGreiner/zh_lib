//
// Created by larix on 2026. 05. 15..
//

#ifndef APP_H
#define APP_H

#include "widget.h"
#include <vector>

using namespace std;

class Scene;

class App {
    int width;
    int height;
    int default_font_size;
    bool quit_requested = false;

    vector<Scene*> scenes;
    Scene* active_scene;
    Scene* previous_scene;

    Scene* registration_target;
    vector<Widget*> active_widgets;

public:
    App(int width = 1200, int height = 1000, int font_size = 20);
    ~App();

    int Width() const { return width; }
    int Height() const { return height; }
    int FontSize() const { return default_font_size; }

    void AddScene(Scene* scene);
    void SwitchTo(Scene* scene);

    Scene* ActiveScene() const { return active_scene; }
    Scene* PreviousScene() const { return previous_scene; }

    void RegisterWidget(Widget* widget);

    void SetRegistrationTarget(Scene* target) { registration_target = target; }
    Scene* GetRegistrationTarget() const { return registration_target; }

    void RefreshActiveWidgets();

    void Start();
    void Quit();
    void ClearWindow();
    void Refresh();
    void EventLoop();
};

#endif // APP_H