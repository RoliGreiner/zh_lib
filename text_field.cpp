//
// Created by larix on 2026. 04. 23..
//

#include "text_field.h"
#include <sstream>
#include <algorithm>

TextField::TextField(App* app, Vector2 position, Vector2 size, Color texture, vector<string> text, int font_size, bool resizable, bool transparent)
    : Widget(app, position, size, texture, transparent) {
    this->raw_text = text;
    this->font_size = font_size;
    this->resizable = resizable;

    UpdateCanvas();
}

void TextField::UpdateCanvas() {
    gout << font("LiberationMono-Regular.ttf", font_size);

    wrapped_text.clear();

    for (int i = 0; i < raw_text.size(); i++) {
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

    /*
    if (canvas_width < 1) {
        canvas_width = 1;
    }
    if (canvas_height < 1) {
        canvas_height = 1;
    }
    */

    can = canvas(canvas_width, canvas_height);
    can.load_font("LiberationMono-Regular.ttf", font_size);
    can << color(texture.r, texture.g, texture.b)
        << move_to(0, 0)
        << box(canvas_width, canvas_height);

    can << color(0, 0, 0);
    for (int i = 0; i < wrapped_text.size(); ++i) {
        can << move_to(APPEND, i * (gout.cascent() + gout.cdescent()) + APPEND)
            << text(wrapped_text[i]);
    }
}

void TextField::Draw() {
    //keret
    gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
         << color(60, 60, 60)
         << box(size.x, size.y);

    //belseje
    gout << move_to(position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE)
         << color(texture.r, texture.g, texture.b)
         << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);

    gout << stamp(can, 0, current_line * (gout.cascent() + gout.cdescent()), size.x - 2 * BORDER_SIZE, size.y - 2 * BORDER_SIZE, position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE);
}


void TextField::Interact(event ev) {
    //méretezés
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