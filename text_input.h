//
// Created by larix on 2026. 04. 20..
//

#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "widget.h"

using namespace std;

class TextInput : public Widget {
protected:
    string text;
    string ghost_text;
    int cursor_index;
    const int APPEND = 5;
public:
    TextInput(App* app, Vector2 position, Vector2 size, Color texture, string ghost_text = "", bool transparent = false);
    void Draw() override;
    void Interact(event ev) override;
    string GetText();
};

#endif //TEXT_INPUT_H