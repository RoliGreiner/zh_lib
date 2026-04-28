//
// Created by larix on 2026. 04. 23..
//

#include "text_field.h"

TextField::TextField(Vector2 position, Vector2 size, Color texture, vector<string> text, bool resizable, bool transparent)
    : Widget(position, size, texture, transparent) {
    this->text = text;
    this->resizable = resizable;
    int max_width = 0;
    for (int i = 0; i < text.size(); i++) {
        max_width = max(max_width, gout.twidth(text[i]));
    }

    can = canvas(max_width + 2 * (BORDER_SIZE + APPEND), text.size() * (gout.cascent() + gout.cdescent()) + 2 * (BORDER_SIZE + APPEND));
    can.load_font("LiberationMono-Regular.ttf", 16);
    can << color(texture.r, texture.g, texture.b) << move_to(0, 0) << box(max_width + 2 * (BORDER_SIZE + APPEND), text.size() * (gout.cascent() + gout.cdescent()) + 2 * (BORDER_SIZE + APPEND));
    can << color(0, 0, 0);
    for (int i = 0; i < text.size(); ++i) {
        can << move_to(APPEND, i * (gout.cascent() + gout.cdescent()) + APPEND)
             << genv::text(text[i]);
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

    gout << stamp(can, 0, current_line * (gout.cascent() + gout.cdescent()), size.x - 2 * BORDER_SIZE - 10 - APPEND, size.y - 2 * BORDER_SIZE, position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE);

    //handle background (track)
    gout << move_to(position.x + size.x / 2 - 10, position.y - size.y / 2)
         << color(0, 0, 0)
         << box(10, size.y);

    // Calculate handle properties
    int line_height = gout.cascent() + gout.cdescent();
    int visible_lines = (size.y - 2 * (BORDER_SIZE + APPEND)) / line_height;
    int max_line = max(0, (int)text.size() - visible_lines);

    // The handle height is proportional to the visible ratio of the text
    float view_ratio = text.empty() ? 1.0f : min(1.0f, (float)visible_lines / text.size());
    int handle_height = max(10, (int)(size.y * view_ratio)); // Minimum 10px height so it doesn't disappear

    // Position depends on current_line relative to max_line
    float scroll_ratio = (max_line > 0) ? (float)current_line / max_line : 0.0f;
    int handle_y = (position.y - size.y / 2) + scroll_ratio * (size.y - handle_height);

    // Draw the actual handle (thumb) inside the track
    gout << move_to(position.x + size.x / 2 - 8, handle_y + 2)
         << color(150, 150, 150) // Gray scrollbar thumb
         << box(6, handle_height - 4);
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
            pressed = false;
        }
        if (pressed) {
            size.x = 2 * abs(ev.pos_x - position.x);
            size.y = 2 * abs(ev.pos_y - position.y);
        }
    }

    if (ev.button == btn_wheeldown) {
        if (++current_line > text.size() - (size.y - 2 * (BORDER_SIZE + APPEND)) / (gout.cascent() + gout.cdescent()))
            current_line = text.size() - (size.y - 2 * (BORDER_SIZE + APPEND)) / (gout.cascent() + gout.cdescent());
    }
    if (ev.button == btn_wheelup) {
        if (--current_line < 0)
            current_line = 0;
    }
}
