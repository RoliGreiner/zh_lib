//
// Created by larix on 2026. 04. 20..
//

#include "widget.h"
#include "app.h"
#include <cstdlib>

Widget::Widget(App* app, Vector2 position, Vector2 size, Color texture, bool transparent)
    : app(app), position(position), size(size), texture(texture), transparent(transparent) {
    if (app) {
        app->RegisterWidget(this);
    }
}

const Theme& Widget::GetTheme() const   { return app->GetTheme(); }
Vector2 Widget::MousePos() const {
    return app->Mouse();
}
bool Widget::Hovered() {
    return UnderMouse(app->Mouse());
}
int Widget::Radius() const {
    return app->GetTheme().radius;
}

void Widget::Draw() {
    if (transparent)
        return;

    Color fill = Resolve(GetTheme().surface);
    int radius = Radius();
    int x = position.x - size.x / 2;
    int y = position.y - size.y / 2;

    FillRoundedBox(x, y, size.x, size.y, radius, GetTheme().border);
    FillRoundedBox(x + BORDER_SIZE, y + BORDER_SIZE,
                   size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2, radius - BORDER_SIZE, fill);
}

void Widget::Interact(event) {}

void Widget::FocusGained() {
    active = true;
}
void Widget::FocusLost() {
    active = false;
}

bool Widget::UnderMouse(Vector2 mouse_position) {
    return abs(mouse_position.x - position.x) <= size.x / 2 &&
           abs(mouse_position.y - position.y) <= size.y / 2;
}
