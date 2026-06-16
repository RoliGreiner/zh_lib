//
// Created by larix on 2026. 04. 20..
//

#include "slider.h"
#include <algorithm>
#include <cmath>

using namespace std;

Slider::Slider(App* app, Vector2 position, Vector2 size, int min_value, int max_value, int value, Orientation orientation, bool transparent, Color color_override)
    : Widget(app, position, size, color_override, transparent) {
    this->min_value = min_value;
    this->max_value = max_value;
    this->value = value;
    this->orientation = orientation;

    int length = max(size.x, size.y);
    float ratio = (max_value > min_value) ? (float)(value - min_value) / (float)(max_value - min_value) : 0;

    if (orientation == Orientation::HORIZONTAL) {
        this->handle_position = {position.x - length / 2 + int(length * ratio), position.y};
    } else {
        this->handle_position = {position.x, position.y - length / 2 + int(length * ratio)};
    }
}

void Slider::Draw() {
    int length = max(size.x, size.y);
    int thickness = min(size.x, size.y);
    int handle_size = thickness;

    Color trackc = GetTheme().surface_alt;
    Color fillc = Resolve(GetTheme().accent);
    Color border = GetTheme().border;

    if (orientation == Orientation::HORIZONTAL) {
        int gx = position.x - length / 2;
        int gy = position.y - thickness / 2 + 5;
        int gw = length;
        int gh = thickness - 10;

        // stadion alakú sín
        FillRoundedBox(gx, gy, gw, gh, gh, border);
        FillRoundedBox(gx + BORDER_SIZE, gy + BORDER_SIZE,
                       gw - BORDER_SIZE * 2, gh - BORDER_SIZE * 2, gh, trackc);

        int filled = clamp(handle_position.x - gx, 0, gw);
        if (filled > BORDER_SIZE) {
            FillRoundedBoxEx(gx + BORDER_SIZE, gy + BORDER_SIZE,
                             filled - BORDER_SIZE, gh - BORDER_SIZE * 2, gh,
                             true, false, true, false, fillc);
        }
    } else {
        int gx = position.x - thickness / 2 + 5;
        int gy = position.y - length / 2;
        int gw = thickness - 10;
        int gh = length;

        FillRoundedBox(gx, gy, gw, gh, gw, border);
        FillRoundedBox(gx + BORDER_SIZE, gy + BORDER_SIZE,
                       gw - BORDER_SIZE * 2, gh - BORDER_SIZE * 2, gw, trackc);

        int filled = clamp(handle_position.y - gy, 0, gh);
        if (filled > BORDER_SIZE) {
            FillRoundedBoxEx(gx + BORDER_SIZE, gy + BORDER_SIZE,
                             gw - BORDER_SIZE * 2, filled - BORDER_SIZE, gw,
                             true, true, false, false, fillc);
        }
    }

    // fogó: accent gyűrű + világos belső (lenyomva accent_hover)
    int r_outer = handle_size / 2;
    int r_inner = r_outer - 2;
    Color ring = fillc;
    Color knob = pressed ? GetTheme().accent_hover : GetTheme().surface;

    for (int y = -r_outer; y <= r_outer; ++y) {
        int dx_outer = (int)sqrt((double)(r_outer * r_outer - y * y));
        gout << move_to(handle_position.x - dx_outer, handle_position.y + y)
             << color(ring.r, ring.g, ring.b)
             << box(dx_outer * 2, 1);

        if (y >= -r_inner && y <= r_inner) {
            int dx_inner = (int)sqrt((double)(r_inner * r_inner - y * y));
            gout << move_to(handle_position.x - dx_inner, handle_position.y + y)
                 << color(knob.r, knob.g, knob.b)
                 << box(dx_inner * 2, 1);
        }
    }
}

void Slider::Interact(event ev) {
    int length = std::max(size.x, size.y);

    if (ev.button == btn_left)  pressed = true;
    if (ev.button == -btn_left) pressed = false;

    if (pressed) {
        if (orientation == Orientation::HORIZONTAL) {
            handle_position.x = clamp(ev.pos_x, position.x - length / 2, position.x + length / 2);
            value = min_value + (max_value - min_value) * (float(handle_position.x - (position.x - length / 2)) / length);
        } else {
            handle_position.y = clamp(ev.pos_y, position.y - length / 2, position.y + length / 2);
            value = min_value + (max_value - min_value) * (float(handle_position.y - (position.y - length / 2)) / length);
        }
    }
}
