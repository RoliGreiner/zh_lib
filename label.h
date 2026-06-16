//
// Created by larix on 2026. 05. 17..
//

#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

using namespace std;

class Label : public Widget {
public:
    enum class Align { Left, Center, Right };

private:
    string text;
    int font_size;
    Align alignment;
    const int APPEND = 3;

public:
    Label(App* app, Vector2 position, Vector2 size, string text, int font_size, Align alignment = Align::Center, Color color_override = USE_THEME);
    void Draw() override;
    void UpdateText(string text) { this->text = text; }
};

#endif //LABEL_H
