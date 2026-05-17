//
// Created by larix on 2026. 05. 17..
//

#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

using namespace std;

class Label : public Widget {
    string text;
    int font_size;
    const int APPEND = 3;

public:
    Label(App* app, Vector2 position, Vector2 size, Color texture, string text, int font_size, bool transparent = false);
    void Draw() override;
};


#endif //LABEL_H
