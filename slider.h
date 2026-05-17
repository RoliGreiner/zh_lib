//
// Created by larix on 2026. 04. 20..
//

#ifndef SLIDER_H
#define SLIDER_H

#include "widget.h"
#include <algorithm>
#include <functional>

using namespace std;

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
    function<void(int)> on_value_change;
public:
    Slider(App* app, Vector2 position, Vector2 size, Color texture, int min_value, int max_value, int value = 0, Orientation orientation = Orientation::HORIZONTAL, bool transparent = false);
    void Draw() override;
    void Interact(event ev) override;
    int GetValue() { return value; }
    void SetValue(int new_value) { value = clamp(new_value, min_value, max_value); }

    void SetOnValueChange(function<void(int)> callback) { on_value_change = callback; }
};

#endif //SLIDER_H