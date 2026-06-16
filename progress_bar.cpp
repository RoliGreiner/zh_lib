//
// Created by larix on 2026. 06. 08..
//

#include "progress_bar.h"
#include <algorithm>

ProgressBar::ProgressBar(App* app, Vector2 position, Vector2 size, int min_value, int max_value, int value, Orientation orientation, bool show_value, bool transparent, Color color_override)
    : Widget(app, position, size, color_override, transparent) {
    this->min_value = min_value;
    this->max_value = max_value;
    this->orientation = orientation;
    this->show_value = show_value;
    this->value = value;
    SetValue(value);
}

void ProgressBar::SetValue(int v) {
    value = std::clamp(v, min_value, max_value);
}

void ProgressBar::Draw() {
    int length = std::max(size.x, size.y);
    int thickness = std::min(size.x, size.y);

    Color trackc = GetTheme().surface_alt;
    Color fillc  = Resolve(GetTheme().accent);
    Color bord   = GetTheme().border;

    float ratio = (max_value > min_value) ? (float)(value - min_value) / (float)(max_value - min_value) : 0.f;
    if (ratio < 0.f)
        ratio = 0.f;
    if (ratio > 1.f)
        ratio = 1.f;

    if (orientation == Orientation::HORIZONTAL) {
        int gx = position.x - length / 2;
        int gy = position.y - thickness / 2 + 5;
        int gw = length;
        int gh = thickness - 10;

        // stadion alakú sín (mint a sliderben, fogó nélkül)
        FillRoundedBox(gx, gy, gw, gh, gh, bord);
        FillRoundedBox(gx + BORDER_SIZE, gy + BORDER_SIZE,
                       gw - BORDER_SIZE * 2, gh - BORDER_SIZE * 2, gh, trackc);

        int filled = (int)(ratio * gw);
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

        FillRoundedBox(gx, gy, gw, gh, gw, bord);
        FillRoundedBox(gx + BORDER_SIZE, gy + BORDER_SIZE,
                       gw - BORDER_SIZE * 2, gh - BORDER_SIZE * 2, gw, trackc);

        int filled = (int)(ratio * gh);
        if (filled > BORDER_SIZE) {
            FillRoundedBoxEx(gx + BORDER_SIZE, gy + BORDER_SIZE,
                             gw - BORDER_SIZE * 2, filled - BORDER_SIZE, gw,
                             true, true, false, false, fillc);
        }
    }

    if (show_value && orientation == Orientation::HORIZONTAL) {
        string s = to_string(value);
        Color tc = GetTheme().text;
        gout << color(tc.r, tc.g, tc.b)
             << move_to(position.x - gout.twidth(s) / 2,
                        position.y - (gout.cascent() + gout.cdescent()) / 2)
             << genv::text(s);
    }
}