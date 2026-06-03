//
// Created by larix on 2026. 05. 21..
//

#include "check_box.h"

CheckBox::CheckBox(App *app, Vector2 position, Vector2 size, Color texture, bool state, bool transparent)
: Widget(app, position, size, texture, transparent) {
    checked = state;
}

void CheckBox::Draw() {
    if (!transparent) {
        gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
             << color(0, 0, 0)
             << box(size.x, size.y);

        gout << move_to(position.x - size.x / 2 + BORDER_SIZE,
                        position.y - size.y / 2 + BORDER_SIZE)
             << color(texture.r, texture.g, texture.b)
             << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);

        if (checked) {
            gout << color(0, 0, 0)
                 << move_to(position.x - size.x / 2, position.y - size.y / 2)
                 << line_to(position.x + size.x / 2, position.y + size.y / 2)
                 << move_to(position.x + size.x / 2, position.y - size.y / 2)
                 << line_to(position.x - size.x / 2, position.y + size.y / 2);
        }
    }
}

void CheckBox::Interact(event ev) {
    if (ev.button == btn_left) {
        checked = !checked;
    }
}
