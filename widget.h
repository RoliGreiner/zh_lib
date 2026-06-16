//
// Created by larix on 2026. 04. 20..
//

#ifndef WIDGET_H
#define WIDGET_H

#include "graphics.hpp"
#include "theme.h"
#include <algorithm>
#include <cmath>

using namespace genv;

class App;

struct Vector2 {
    int x, y;
};

inline void FillRoundedBoxEx(int pos_x, int pos_y, int width, int height, int radius, bool top_left, bool top_right, bool bottom_left, bool bottom_right, Color style) {
    if (width <= 0 || height <= 0)
        return;
    int r = std::min(radius, std::min(width, height) / 2);
    if (r < 0)
        r = 0;

    gout << color(style.r, style.g, style.b);
    for (int y = 0; y < height; ++y) {
        int left_in = 0;
        int right_in = 0;

        if (r > 0 && y < r) {
            int dyc = r - y;
            int inset = r - (int)std::sqrt((double)(r * r - dyc * dyc));
            if (top_left)
                left_in = inset;
            if (top_right)
                right_in = inset;
        } else if (r > 0 && y > height - 1 - r) {
            int dyc = r - (height - 1 - y);
            int inset = r - (int)std::sqrt((double)(r * r - dyc * dyc));
            if (bottom_left)
                left_in = inset;
            if (bottom_right)
                right_in = inset;
        }
        int w = width - left_in - right_in;
        if (w <= 0)
            continue;
        gout << move_to(pos_x + left_in, pos_y + y) << box(w, 1);
    }
}

inline void FillRoundedBox(int x, int y, int width, int height, int radius, Color style) {
    FillRoundedBoxEx(x, y, width, height, radius, true, true, true, true, style);
}

class Widget {
    friend class Container;
protected:
    App* app;
    Vector2 position{};
    Vector2 size{};
    bool active = false;
    Color texture{};
    bool transparent;
    const int BORDER_SIZE = 2;

    const Theme& GetTheme() const;
    Vector2 MousePos() const;
    bool Hovered();
    int Radius() const;
    Color Resolve(Color role) const { return IsThemeColor(texture) ? role : texture; }

public:
    Widget(App* app, Vector2 position, Vector2 size, Color texture = USE_THEME, bool transparent = false);
    virtual ~Widget() = default;
    virtual void Draw();
    virtual void Interact(event ev);
    virtual bool UnderMouse(Vector2 mouse_position);
    virtual void FocusGained();
    virtual void FocusLost();
};

#endif // WIDGET_H
