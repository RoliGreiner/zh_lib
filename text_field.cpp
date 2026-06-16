//
// Created by larix on 2026. 04. 23..
//

#include "text_field.h"
#include <sstream>
#include <algorithm>

TextField::TextField(App* app, Vector2 position, Vector2 size, vector<string> text, int font_size, bool resizable, bool transparent, Color color_override)
    : Widget(app, position, size, color_override, transparent) {
    this->raw_text = text;
    this->font_size = font_size;
    this->resizable = resizable;

    UpdateCanvas();
}

void TextField::UpdateCanvas() {
    gout << font("LiberationMono-Regular.ttf", font_size);

    wrapped_text.clear();

    for (int i = 0; i < (int)raw_text.size(); i++) {
        stringstream ss(raw_text[i]);
        string word;
        string current_line = "";
        ss >> current_line;

        while (ss >> word) {
            if (gout.twidth(current_line + " " + word) > size.x - 2 * (BORDER_SIZE + APPEND)) {
                wrapped_text.push_back(current_line);
                current_line = word;
            } else {
                current_line.append(" " + word);
            }
        }

        if (!current_line.empty()) {
            wrapped_text.push_back(current_line);
        } else if (raw_text[i].empty()) {
            wrapped_text.emplace_back("");
        }
    }

    int canvas_width = size.x - 2 * BORDER_SIZE;
    int canvas_height = wrapped_text.size() * gout.cascent() + gout.cdescent() + 2 * APPEND;

    Color fill = Resolve(GetTheme().surface);
    Color text_color   = GetTheme().text;

    can = canvas(canvas_width, canvas_height);
    can.load_font("LiberationMono-Regular.ttf", font_size);
    can << color(fill.r, fill.g, fill.b)
        << move_to(0, 0)
        << box(canvas_width, canvas_height);

    can << color(text_color.r, text_color.g, text_color.b);
    for (int i = 0; i < (int)wrapped_text.size(); ++i) {
        can << move_to(APPEND, i * (gout.cascent() + gout.cdescent()) + APPEND)
            << text(wrapped_text[i]);
    }
}

void TextField::Draw() {
    Color fill = Resolve(GetTheme().surface);
    Color border = active ? GetTheme().accent : GetTheme().border;
    int radius = Radius();
    int x = position.x - size.x / 2;
    int y = position.y - size.y / 2;

    // lekerekített keret + belső háttér; a görgetett szövegvászon a belsőre kerül
    FillRoundedBox(x, y, size.x, size.y, radius, border);
    FillRoundedBox(x + BORDER_SIZE, y + BORDER_SIZE,
                   size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2, radius - BORDER_SIZE, fill);

    gout << stamp(can, 0, current_line * (gout.cascent() + gout.cdescent()),
                  size.x - 2 * BORDER_SIZE, size.y - 2 * BORDER_SIZE,
                  position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE);
}

void TextField::Interact(event ev) {
    if (ev.type == ev_mouse && resizable) {
        if ((size.x / 2 >= abs(ev.pos_x - position.x) && size.x / 2 <= abs(ev.pos_x - position.x) + 2) ||
            (size.y / 2 >= abs(ev.pos_y - position.y) && size.y / 2 <= abs(ev.pos_y - position.y) + 2)) {
            if (ev.button == btn_left) {
                pressed = true;
            }
        }

        if (ev.button == -btn_left) {
            if (pressed) {
                UpdateCanvas();
            }
            pressed = false;
        }

        if (pressed) {
            size.x = 2 * abs(ev.pos_x - position.x);
            size.y = 2 * abs(ev.pos_y - position.y);
        }
    }

    if (ev.button == btn_wheeldown) {
        current_line++;
    }

    if (ev.button == btn_wheelup) {
        current_line--;
    }

    int max_scroll = wrapped_text.size() - (size.y - 2 * (BORDER_SIZE + APPEND)) / (gout.cascent() + gout.cdescent());
    current_line = clamp(current_line, 0, max_scroll);
}
