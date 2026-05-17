//
// Created by larix on 2026. 04. 20..
//

#include "button.h"

Button::Button(App* app, Vector2 position, Vector2 size, Color texture, string text, function<void()> on_press)
: Widget(app, position, size, texture), text(text), on_press(on_press) {
}

void Button::Draw() {
    Color original = texture;
    if (pressed) {
        texture = { texture.r - 50, texture.g - 50, texture.b - 50};
    }
    DrawFrame({60, 60, 60, 255});
    texture = original;

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