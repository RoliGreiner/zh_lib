//
// Created by larix on 2026. 04. 23..
//

#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "widget.h"

using namespace std;

class TextField : public Widget {
protected:
    vector<string> raw_text;
    vector<string> wrapped_text;
    int font_size;
    canvas can;
    int current_line = 0;
    bool resizable;
    bool pressed = false;
    const int APPEND = 3;

    void UpdateCanvas();

public:
    TextField(Vector2 position, Vector2 size, Color texture, vector<string> text, int font_size, bool resizable = false, bool transparent = false);
    void Draw() override;
    void Interact(event ev) override;
};

#endif //TEXT_FIELD_H