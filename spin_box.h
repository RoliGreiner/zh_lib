//
// Created by larix on 2026. 06. 05..
//

#ifndef SPINBOX_H
#define SPINBOX_H

#include "widget.h"

using namespace std;

class SpinBox : public Widget {
protected:
    int value;
    int min_value;
    int max_value;
    int step;

    void Increment();
    void Decrement();

public:
    SpinBox(App* app, Vector2 position, Vector2 size, int min_value, int max_value, int step = 1, int initial_value = 0, Color color_override = USE_THEME);
    void Draw() override;
    void Interact(event ev) override;
    int GetValue() const;
    void SetValue(int new_value);
};

#endif // SPINBOX_H
