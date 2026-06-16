//
// Created by larix on 2026. 04. 20..
//

#ifndef SLIDER_H
#define SLIDER_H

#include "widget.h"
#include <algorithm>

enum class Orientation {
    HORIZONTAL,
    VERTICAL
};

class Slider : public Widget {
protected:
    int value;
    int min_value, max_value;
    Vector2 handle_position;
    bool pressed = false;
    Orientation orientation;
public:
    Slider(App* app, Vector2 position, Vector2 size, int min_value, int max_value, int value = 0, Orientation orientation = Orientation::HORIZONTAL, bool transparent = false, Color color_override = USE_THEME);
    void Draw() override;
    void Interact(event ev) override;
    int GetValue() { return value; }
    void SetValue(int value) { this->value = std::clamp(value, min_value, max_value); }
};

#endif //SLIDER_H
