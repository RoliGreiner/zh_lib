//
// Created by larix on 2026. 05. 15..
//

#include "graphics.hpp"
#include "app.h"
#include "scene.h"

using namespace genv;
using namespace std;

App::App(int width, int height, int font_size)
: width(width), height(height), default_font_size(font_size),
  active_scene(nullptr), previous_scene(nullptr), registration_target(nullptr) {
    gout.open(width, height);
    gout << font("LiberationMono-Regular.ttf", default_font_size);
    gout << refresh;
}

App::~App() {
    for (Scene* scene : scenes) {
        delete scene;
    }
    scenes.clear();
}

void App::AddScene(Scene* scene) {
    scenes.push_back(scene);
}

void App::SwitchTo(Scene* scene) {
    previous_scene = active_scene;
    active_scene = scene;

    RefreshActiveWidgets();
    Refresh();
}

void App::RefreshActiveWidgets() {
    if (active_scene) {
        active_widgets = active_scene->Widgets();
    } else {
        active_widgets.clear();
    }
}

void App::RegisterWidget(Widget* widget) {
    Scene* target = registration_target ? registration_target : active_scene;
    if (target) {
        target->AddWidget(widget);
        if (target == active_scene) {
            active_widgets.push_back(widget);
        }
    }
}

void App::ClearWindow() {
    gout << move_to(0, 0) << color(50, 50, 50) << box(width, height);
}

void App::Refresh() {
    ClearWindow();
    if (active_scene) active_scene->Draw();
    gout << refresh;
}

void App::EventLoop() {
    event ev;
    int focus = -1;
    bool slider_dragging = false;
    Refresh();

    while (gin >> ev && ev.keycode != key_escape && !quit_requested) {
        if (!active_scene) continue;

        if (ev.button == btn_left) {
            focus = -1;
            for (size_t i = 0; i < active_widgets.size(); i++) {
                if (active_widgets[i]->UnderMouse({ev.pos_x, ev.pos_y})) {
                    focus = static_cast<int>(i);
                    break;
                }
            }
        }
        if (ev.button == -btn_left) {
            slider_dragging = false;
        }

        bool needs_redraw = false;
        if (focus != -1 && focus < static_cast<int>(active_widgets.size())) {
            if (ev.type == ev_mouse) {
                if (ev.button == btn_left || ev.button == -btn_left) {
                    active_widgets[focus]->Interact(ev);
                    if (ev.button == btn_left)
                        slider_dragging = true;
                    needs_redraw = true;
                } else if (ev.button == 0 && slider_dragging) {
                    active_widgets[focus]->Interact(ev);
                    needs_redraw = true;
                }
            } else if (ev.type == ev_key) {
                active_widgets[focus]->Interact(ev);
                needs_redraw = true;
            }
        }

        if (needs_redraw)
            Refresh();
    }
}

void App::Start() {
    EventLoop();
}

void App::Quit() {
    quit_requested = true;
}