//
// Created by larix on 2026. 04. 20..
//

#include "button.h"

Button::Button(App* app, Vector2 position, Vector2 size, string text, function<void()> on_press, Color color_override)
    : Widget(app, position, size, color_override) {
    this->text = text;
    this->on_press = on_press;
}

void Button::Draw() {
    Color base = Resolve(GetTheme().accent);
    Color fill;
    if (IsThemeColor(texture)) {
        fill = pressed ? GetTheme().accent_pressed : (Hovered() ? GetTheme().accent_hover : base);
    } else {
        fill = pressed ? Darken(base, 38) : (Hovered() ? Lighten(base, 26) : base);
    }

    int radius = Radius();
    int x = position.x - size.x / 2;
    int y = position.y - size.y / 2;

    FillRoundedBox(x, y, size.x, size.y, radius, GetTheme().border);
    FillRoundedBox(x + BORDER_SIZE, y + BORDER_SIZE, size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2, radius - BORDER_SIZE, fill);

    Color text_color = GetTheme().text_on_accent;
    gout << color(text_color.r, text_color.g, text_color.b)
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
