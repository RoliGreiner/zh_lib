//
// Created by larix on 2026. 04. 20..
//

#include "slider.h"
#include <algorithm>

using namespace std;

Slider::Slider(Vector2 position, Vector2 size, Color texture, int min_value, int max_value, int value, bool transparent)
: Widget(position, size, texture, transparent) {
     this->min_value = min_value;
     this->max_value = max_value;
     this->value = value;
     this->handle_position = {position.x - size.x / 2 + int(size.x * ((float)value / (float)max_value)), position.y};
}

void Slider::Draw() {
     //keret
     gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
          << color(60, 60, 60)
          << box(size.x, size.y);

     //belseje
     gout << move_to(position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE)
          << color(texture.r, texture.g, texture.b)
          << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);
     //handle
     gout << move_to(handle_position.x - size.y / 2, handle_position.y - size.y / 2)
          << color(60, 60, 60)
          << box(size.y, size.y);

     gout << move_to(handle_position.x - size.y / 2 + BORDER_SIZE, handle_position.y - size.y / 2 + BORDER_SIZE)
          << color(texture.r, texture.g, texture.b)
          << box(size.y - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);
}

void Slider::Interact(event ev) {
     if (ev.button == btn_left) {
          pressed = true;
     }
     if (ev.button == -btn_left) {
          pressed = false;
     }
     if (pressed) {
          handle_position.x = clamp(ev.pos_x, position.x - size.x / 2, position.x + size.x / 2);
          //value = max_value * (size.x / (position.x - size.x / 2 - handle_position.x));
     }
}
