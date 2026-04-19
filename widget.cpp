#include "widget.h"
#include "graphics.hpp"

using namespace genv;

Widget::Widget(Vector2 position, Vector2 size, Color texture, bool transparent) : position(position), size(size), texture(texture), transparent(transparent) {
}

void Widget::Draw() {
    if (!transparent) {
        //keret
        gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
                << color(60, 60, 60)
                << box(size.x, size.y);

        //belseje
        gout << move_to(position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE)
                << color(texture.r, texture.g, texture.b)
                << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);
    }
}

bool Widget::UnderMouse(Vector2 mouse_position) {
    return abs(mouse_position.x - position.x) <= size.x / 2 &&
           abs(mouse_position.y - position.y) <= size.y / 2;
}






