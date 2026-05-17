//
// Created by larix on 2026. 05. 15..
//

#include "graphics.hpp"
#include "app.h"

using namespace genv;
using namespace std;

App::App(int width, int height, int font_size)
: width(width), height(height), default_font_size(font_size), list_a(nullptr), list_b(nullptr) {
    gout.open(width, height);
    gout << font("LiberationMono-Regular.ttf", 20);
    gout << refresh;

    //widgetek



    new Label(this, {width / 2, height / 2}, {200, 40}, {255, 255, 255}, "Hello", 16);

    ClearWindow();
    Refresh();
}

App::~App() {
    for (Widget* widget : widgets) {
        delete widget;
    }
    widgets.clear();
}

void App::RegisterWidget(Widget* w) {
    widgets.push_back(w);
}

void App::ClearWindow() {
    gout << move_to(0, 0) << color(255, 255, 255) << box(width, height);
}

void App::Refresh() {
    for (Widget* widget : widgets) {
        widget->Draw();
    }
    gout << refresh;
}

void App::EventLoop() {
    event ev;
    int focus = -1;
    while (gin >> ev && ev.keycode != key_escape) {
        ClearWindow();

        if (ev.button == btn_left) {
            focus = -1;
            for (size_t i = 0; i < widgets.size(); i++) {
                if (widgets[i]->UnderMouse({ev.pos_x, ev.pos_y})) {
                    focus = i;
                    break;
                }
            }
        }

        if (focus != -1) {
            widgets[focus]->Interact(ev);
        }

        Refresh();
    }
}

void App::Start() {
    EventLoop();
}