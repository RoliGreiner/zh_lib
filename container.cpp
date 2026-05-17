//
// Created by larix on 2026. 05. 17..
//

#include "container.h"

Container::Container(App* app, Vector2 position, Vector2 size, Color texture, Color locked_color, Widget* initial, bool transparent)
: Widget(app, position, size, texture, transparent), held(nullptr), locked(false), locked_border_color(locked_color) {
    if (initial) {
        AttachWidget(initial);
    }
}

void Container::FitHeldToSelf() {
    if (!held)
        return;
    held->position = position;
    held->size = { size.x - 2 * BORDER_SIZE, size.y - 2 * BORDER_SIZE };
}

void Container::Draw() {
    if (!transparent) {
        DrawFrame(locked ? locked_border_color : Color{60, 60, 60, 255});
    }
}

void Container::Interact(event ev) {
    if (on_click && ev.button == btn_left) {
        on_click();
    }
}

Widget* Container::AttachWidget(Widget* widget) {
    Widget* old = held;
    held = widget;
    if (held)
        FitHeldToSelf();
    return old;
}

Widget* Container::DetachWidget() {
    if (locked)
        return nullptr;
    Widget* content = held;
    held = nullptr;
    return content;
}