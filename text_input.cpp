//
// Created by larix on 2026. 04. 20..
//

#include "text_input.h"
#include "app.h"

TextInput::TextInput(App* app, Vector2 position, Vector2 size, string ghost_text, bool transparent, Color color_override)
    : Widget(app, position, size, color_override, transparent) {
    this->ghost_text = ghost_text;
    this->text = "";
    this->cursor_index = 0;
}

void TextInput::Draw() {
    Color fill = Resolve(GetTheme().surface);
    Color border = active ? GetTheme().accent : GetTheme().border;
    int font_size = app->FontSize();
    int radius = Radius();
    int x = position.x - size.x / 2;
    int y = position.y - size.y / 2;

    FillRoundedBox(x, y, size.x, size.y, radius, border);
    FillRoundedBox(x + BORDER_SIZE, y + BORDER_SIZE, size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2, radius - BORDER_SIZE, fill);

    // szöveg
    bool empty = text.empty();
    Color text_color = empty ? GetTheme().text_muted : GetTheme().text;
    gout << color(text_color.r, text_color.g, text_color.b)
         << move_to(position.x - size.x / 2 + APPEND, position.y - (gout.cascent() + gout.cdescent()) / 2)
         << font(empty ? "LiberationMono-Italic.ttf" : "LiberationMono-Regular.ttf", font_size)
         << genv::text(empty ? ghost_text : text);
    gout << font("LiberationMono-Regular.ttf", font_size);

    // kurzor csak fókuszban
    if (active) {
        int cursor_position = position.x - (size.x / 2) + APPEND + gout.twidth(text.substr(0, cursor_index));
        Color character_color = GetTheme().accent;
        gout << move_to(cursor_position, position.y - size.y / 2 + APPEND)
             << color(character_color.r, character_color.g, character_color.b)
             << line_to(cursor_position, position.y + size.y / 2 - APPEND);
    }
}

void TextInput::Interact(event ev) {
    if (ev.type == ev_key) {
        if (ev.keycode == key_left && cursor_index > 0) {
            cursor_index--;
        }
        if (ev.keycode == key_right && cursor_index < (int)text.size()) {
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

string TextInput::GetText() {
    return text == "" ? ghost_text : text;
}
