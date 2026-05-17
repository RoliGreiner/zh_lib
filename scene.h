//
// Created by larix on 2026. 05. 17..
//

#ifndef SCENE_H
#define SCENE_H

#include "widget.h"
#include <vector>

using namespace std;

class App;
class Slider;

class Scene {
protected:
    App* app;
    vector<Widget*> widgets;

    Slider* CreateSizeSelector(int center_x, int y, int min_value, int max_value, int initial);

public:
    Scene(App* app) : app(app) {}
    virtual ~Scene();

    void AddWidget(Widget* w);
    void ClearWidgets();
    vector<Widget*> Widgets() { return widgets; }

    virtual void Draw();

protected:
    struct WidgetScope {
        App* app;
        Scene* previous;
        WidgetScope(App* app, Scene* target);
        ~WidgetScope();
    };
};

#endif //SCENE_H