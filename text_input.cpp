//
// Created by larix on 2026. 04. 20..
//

#include "text_input.h"

TextInput::TextInput(Vector2 position, Vector2 size, Color texture, string ghost_text, bool transparent)
: Widget(position, size, texture, transparent) {
    this->ghost_text = ghost_text;
    this->text = "";
    this->cursor_index = 0;
}

void TextInput::Draw() {
    //keret
    gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
         << color(60, 60, 60)
         << box(size.x, size.y);

    //belseje
    gout << move_to(position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE)
         << color(texture.r, texture.g, texture.b)
         << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);

    //szöveg
    gout << color(0, 0, 0)
         << move_to(position.x - size.x / 2 + APPEND, position.y - (gout.cascent() + gout.cdescent()) / 2)
         << font(text.empty() ? "LiberationMono-Italic.ttf" : "LiberationMono-Regular.ttf", 20)
         << genv::text(text.empty() ? ghost_text : text);
    gout << font("LiberationMono-Regular.ttf", 20);

    int cursor_position = position.x - (size.x / 2) + APPEND + gout.twidth(text.substr(0, cursor_index));
    gout << move_to(cursor_position, position.y - size.y / 2 + APPEND)
         << color(0, 0, 0)
         << line_to(cursor_position, position.y + size.y / 2 - APPEND);
}

void TextInput::Interact(event ev) {
    if (ev.type == ev_key) {
        if (ev.keycode == key_left && cursor_index > 0) {
            cursor_index--;
        }
        if (ev.keycode == key_right && cursor_index < text.size()) {
            cursor_index++;
        }
        if (ev.keycode == key_backspace && cursor_index > 0) {
            text.erase(cursor_index - 1, 1);
            cursor_index--;
        }
        if (ev.keycode >= 32 && ev.keycode <= 255) {
            string temp = "";
            temp += (char)ev.keycode;
            text.insert(cursor_index, temp);
            cursor_index++;
        }
    }
}
