//
// Created by larix on 2026. 04. 20..
//

#include "slider.h"
#include <algorithm>
#include <cmath>

using namespace std;

Slider::Slider(App* app, Vector2 position, Vector2 size, Color texture,
               int min_value, int max_value, int value,
               Orientation orientation, bool transparent)
: Widget(app, position, size, texture, transparent),
  value(value), min_value(min_value), max_value(max_value),
  orientation(orientation) {
    int length = max(size.x, size.y);
    float ratio = (max_value > min_value)
                  ? float(value - min_value) / float(max_value - min_value)
                  : 0.0f;

    if (orientation == Orientation::HORIZONTAL) {
        handle_position = { position.x - length / 2 + int(length * ratio), position.y };
    } else {
        handle_position = { position.x, position.y - length / 2 + int(length * ratio) };
    }
}

void Slider::Draw() {
    int length = max(size.x, size.y);
    int thickness = min(size.x, size.y);
    int handle_size = thickness;

    int track_x, track_y, track_w, track_h;
    if (orientation == Orientation::HORIZONTAL) {
        track_x = position.x - length / 2;
        track_y = position.y - thickness / 2 + 5;
        track_w = length;
        track_h = thickness - 10;
    } else {
        track_x = position.x - thickness / 2 + 5;
        track_y = position.y - length / 2;
        track_w = thickness - 10;
        track_h = length;
    }

    gout << move_to(track_x, track_y) << color(60, 60, 60) << box(track_w, track_h);
    gout << move_to(track_x + BORDER_SIZE, track_y + BORDER_SIZE)
         << color(texture.r, texture.g, texture.b)
         << box(track_w - BORDER_SIZE * 2, track_h - BORDER_SIZE * 2);

    int r_outer = handle_size / 2;
    int r_inner = r_outer - BORDER_SIZE;

    for (int y = -r_outer; y <= r_outer; ++y) {
        int dx_outer = sqrt(r_outer * r_outer - y * y);
        gout << move_to(handle_position.x - dx_outer, handle_position.y + y)
             << color(60, 60, 60)
             << box(dx_outer * 2, 1);

        if (y >= -r_inner && y <= r_inner) {
            int dx_inner = sqrt(r_inner * r_inner - y * y);
            gout << move_to(handle_position.x - dx_inner, handle_position.y + y)
                 << color(texture.r, texture.g, texture.b)
                 << box(dx_inner * 2, 1);
        }
    }
}

void Slider::Interact(event ev) {
    int length = max(size.x, size.y);

    if (ev.button == btn_left) pressed = true;
    if (ev.button == -btn_left) pressed = false;

    if (!pressed) return;

    int old_value = value;
    if (orientation == Orientation::HORIZONTAL) {
        handle_position.x = clamp(ev.pos_x, position.x - length / 2, position.x + length / 2);
        value = min_value + (max_value - min_value) *
                (float(handle_position.x - (position.x - length / 2)) / length);
    } else {
        handle_position.y = clamp(ev.pos_y, position.y - length / 2, position.y + length / 2);
        value = min_value + (max_value - min_value) *
                (float(handle_position.y - (position.y - length / 2)) / length);
    }

    if (value != old_value && on_value_change) {
        on_value_change(value);
    }
}