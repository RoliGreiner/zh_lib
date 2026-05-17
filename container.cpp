//
// Created by larix on 2026. 05. 17..
//

#include "container.h"

Container::Container(App* app, Vector2 position, Vector2 size, Color texture, Color locked_color, Widget* initial, bool transparent)
: Widget(app, position, size, texture, transparent) {
    this->held = nullptr;
    this->locked = false;
    this->locked_border_color = locked_color;  //piros keret zárólt állapotban
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
        Color border = locked ? locked_border_color : Color{60, 60, 60, 255};

        gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
             << color(border.r, border.g, border.b)
             << box(size.x, size.y);

        gout << move_to(position.x - size.x / 2 + BORDER_SIZE,
                        position.y - size.y / 2 + BORDER_SIZE)
             << color(texture.r, texture.g, texture.b)
             << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);
    }
}

void Container::Interact(event ev) {
}

Widget* Container::AttachWidget(Widget* widget) {
    Widget* old = held;
    held = widget;
    if (held) {
        FitHeldToSelf();
    }
    return old;
}

Widget* Container::DetachWidget() {
    if (locked)
        return nullptr;

    Widget* content = held;
    held = nullptr;
    return content;
}