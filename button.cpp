//
// Created by larix on 2026. 04. 20..
//

#include "button.h"

Button::Button(Vector2 position, Vector2 size, Color texture, string text, function<void()> on_press)
: Widget(position, size, texture) {
    this->text = text;
    this->on_press = on_press;
}

void Button::Draw() {
    //keret
    gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
            << color(60, 60, 60)
            << box(size.x, size.y);

    //belseje
    gout << move_to(position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE)
            << (pressed ? color(texture.r - 50, texture.g - 50, texture.b - 50) : color(texture.r, texture.g, texture.b))
            << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);

    //szüveg
    gout << color(0, 0, 0)
         << move_to(position.x - gout.twidth(text) / 2, position.y - (gout.cascent() + gout.cdescent()) / 2)
         << genv::text(text);
}

void Button::Interact(event ev) {
    if (on_press && ev.button == btn_left) {
        pressed = true;
        on_press();
    }
    if (pressed && ev.button == -btn_left) {
        pressed = false;
    }
}
