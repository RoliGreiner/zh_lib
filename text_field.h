//
// Created by larix on 2026. 04. 23..
//

#ifndef ZH_LIB_TEXT_FIELD_H
#define ZH_LIB_TEXT_FIELD_H

#include "widget.h"

using namespace std;

class TextField : public Widget {
protected:
    vector<string> text;
    canvas can;
    int current_line = 0;
    const int APPEND = 2;
public:
    TextField(Vector2 position, Vector2 size, Color texture, vector<string> text, bool transparent = false);
    void Draw() override;
    void Interact(event ev) override;
};

#endif //ZH_LIB_TEXT_FIELD_H
