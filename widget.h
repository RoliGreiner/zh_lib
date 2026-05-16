//
// Created by larix on 2026. 04. 20..
//

#ifndef WIDGET_H
#define WIDGET_H

#include "graphics.hpp"

using namespace genv;

class App;

struct Vector2 {
    int x, y;
};
struct Color {
    int r, g, b, a;
};

class Widget {
protected:
    App* app;
    Vector2 position{};
    Vector2 size{};
    bool active = false;
    Color texture{};
    bool transparent;
    const int BORDER_SIZE = 2;
public:
    Widget(App* app, Vector2 position, Vector2 size, Color texture, bool transparent = false);
    virtual ~Widget() = default;
    virtual void Draw();
    virtual void Interact(event ev);
    virtual bool UnderMouse(Vector2 mouse_position);
};

#endif // WIDGET_H