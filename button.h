//
// Created by larix on 2026. 04. 20..
//

#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"
#include <functional>

using namespace std;

class Button : public Widget {
protected:
    string text;
    bool pressed = false;
    function<void()> on_press;
public:
    Button(App* app, Vector2 position, Vector2 size, Color texture, string text, function<void()> on_press);
    void Draw() override;
    void Interact(event ev) override;
};

#endif //BUTTON_H