//
// Created by larix on 2026. 05. 15..
//

#include "app.h"
#include "button.h"
#include "list.h"
#include "label.h"
// #include "slider.h"
// #include "text_input.h"
// #include "text_field.h"

#include "graphics.hpp"

using namespace genv;
using namespace std;

App::App(int width, int height, int font_size)
: width(width), height(height), default_font_size(font_size), list_a(nullptr), list_b(nullptr) {
    gout.open(width, height);
    gout << font("LiberationMono-Regular.ttf", 20);
    gout << refresh;

    list_a = new List(this, {100, 100}, {150, 30}, {255, 255, 255},
                      {"egy", "kettő", "hat"});

    list_b = new List(this, {300, 100}, {150, 30}, {255, 255, 255},
                      {"alma", "körte", "banán", "málna"});

    new Button(this, {100, 50}, {100, 50}, {255, 255, 255}, "jobbra",
               [this]{ MoveItem(list_b, list_a); });

    new Button(this, {300, 50}, {100, 50}, {255, 255, 255}, "balra",
               [this]{ MoveItem(list_a, list_b); });

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

void App::MoveItem(Widget* from, Widget* to) {
    string item = dynamic_cast<List *>(from)->GetValue();
    if (!item.empty()) {
        dynamic_cast<List *>(to)->AddItem(item);
        dynamic_cast<List *>(from)->RemoveCurrent();
    }
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
            for (int i = 0; i < (int)widgets.size(); i++) {
                if (widgets[i]->UnderMouse({ev.pos_x, ev.pos_y})) {
                    focus = i;
                    break;
                }
            }
        }

        if (focus != -1) {
            widgets[focus]->Interact(ev);
        }

        if (ev.keycode == key_left) {
            MoveItem(list_b, list_a);
        }
        if (ev.keycode == key_right) {
            MoveItem(list_a, list_b);
        }

        Refresh();
    }
}

void App::Start() {
    EventLoop();
}