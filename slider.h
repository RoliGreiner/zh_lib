//
// Created by larix on 2026. 04. 20..
//

#ifndef SLIDER_H
#define SLIDER_H

#include "widget.h"

class Slider : public Widget {
protected:
    int value;
    int min_value, max_value;
    Vector2 handle_position;
    bool pressed = false;
public:
    Slider(Vector2 position, Vector2 size, Color texture, int min_value, int max_value, int value = 0, bool transparent = false);
    void Draw() override;
    void Interact(event ev) override;
};

#endif //SLIDER_H
