//
// Created by larix on 2026. 05. 21..
//

#ifndef CHECK_BOX_H
#define CHECK_BOX_H

#include "widget.h"

class CheckBox : public Widget {
protected:
    bool checked;

public:
    CheckBox(App* app, Vector2 position, Vector2 size, bool state = false, bool transparent = false, Color color_override = USE_THEME);

    void Draw() override;
    void Interact(event ev) override;
    bool GetState() { return checked; }
};

#endif //CHECK_BOX_H
