//
// Created by larix on 2026. 05. 17..
//

#ifndef CONTAINER_H
#define CONTAINER_H

#include "widget.h"
#include <functional>

using namespace std;

class Container : public Widget {
protected:
    Widget* held;
    bool locked;
    Color locked_border_color;
    function<void()> on_click;

    void FitHeldToSelf();

public:
    Container(App* app, Vector2 position, Vector2 size, Color texture, Color locked_color = {250, 0, 0}, Widget* initial = nullptr, bool transparent = false);

    void Draw() override;
    void Interact(event ev) override;

    Widget* AttachWidget(Widget* widget);
    Widget* DetachWidget();

    void Lock() { locked = true; }
    void Unlock() { locked = false; }
    bool IsLocked() const { return locked; }

    Widget* GetHeld() const { return held; }

    void SetOnClick(function<void()> callback) { on_click = callback; }
};

#endif //CONTAINER_H