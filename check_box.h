//
// Created by larix on 2026. 05. 21..
//

#ifndef ZH_LIB_CHECK_BOX_H
#define ZH_LIB_CHECK_BOX_H

#include "widget.h"

class CheckBox : public Widget {
protected:
    bool checked;

public:
    CheckBox(App* app, Vector2 position, Vector2 size, Color texture, bool state = false, bool transparent = false);

    void Draw() override;
    void Interact(event ev) override;
    bool GetState() { return checked; }
};


#endif //ZH_LIB_CHECK_BOX_H
