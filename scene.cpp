//
// Created by larix on 2026. 05. 17..
//

#include "scene.h"
#include "app.h"
#include "label.h"
#include "slider.h"
#include <string>

Scene::~Scene() {
    for (Widget* widget : widgets) {
        delete widget;
    }
    widgets.clear();
}

void Scene::AddWidget(Widget* w) {
    widgets.push_back(w);
}

void Scene::ClearWidgets() {
    for (Widget* widget : widgets) {
        delete widget;
    }
    widgets.clear();
    if (app && app->ActiveScene() == this) {
        app->RefreshActiveWidgets();
    }
}

void Scene::Draw() {
    for (Widget* widget : widgets) {
        widget->Draw();
    }
}

Slider* Scene::CreateSizeSelector(int center_x, int y, int min_value, int max_value, int initial) {
    Label* size_label = new Label(
        app,
        {center_x, y},
        {250, 40},
        {255, 255, 255},
        "Pálya méret: " + to_string(initial) + "x" + to_string(initial),
        20);

    Slider* slider = new Slider(
        app,
        {center_x, y + 50},
        {300, 20},
        {100, 100, 255},
        min_value, max_value, initial);

    slider->SetOnValueChange([size_label](int value){
        size_label->SetText("Pálya méret: " + to_string(value) + "x" + to_string(value));
    });

    return slider;
}

Scene::WidgetScope::WidgetScope(App* app, Scene* target) : app(app) {
    previous = app->GetRegistrationTarget();
    app->SetRegistrationTarget(target);
}

Scene::WidgetScope::~WidgetScope() {
    app->SetRegistrationTarget(previous);
}