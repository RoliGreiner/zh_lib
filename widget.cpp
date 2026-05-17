//
// Created by larix on 2026. 04. 20..
//

#include "widget.h"
#include "app.h"

Widget::Widget(App* app, Vector2 position, Vector2 size, Color texture, bool transparent)
: app(app), position(position), size(size), texture(texture), transparent(transparent) {
    if (app) {
        app->RegisterWidget(this);
    }
}

void Widget::DrawFrame(Color border_color) {
    gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
         << color(border_color.r, border_color.g, border_color.b)
         << box(size.x, size.y);

    gout << move_to(position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE)
         << color(texture.r, texture.g, texture.b)
         << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);
}

void Widget::Draw() {
    if (!transparent) {
        DrawFrame({60, 60, 60, 255});
    }
}

void Widget::Interact(event ev) {
}

bool Widget::UnderMouse(Vector2 mouse_position) {
    return abs(mouse_position.x - position.x) <= size.x / 2 &&
           abs(mouse_position.y - position.y) <= size.y / 2;
}