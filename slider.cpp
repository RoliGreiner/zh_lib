//
// Created by larix on 2026. 04. 20..
//

#include "slider.h"
#include <algorithm>
#include <cmath>

using namespace std;

Slider::Slider(Vector2 position, Vector2 size, Color texture, int min_value, int max_value, int value, Orientation orientation, bool transparent)
: Widget(position, size, texture, transparent) {
     this->min_value = min_value;
     this->max_value = max_value;
     this->value = value;
     this->orientation = orientation;

     int length = max(size.x, size.y);

     float ratio = (max_value > min_value) ? (float)(value - min_value) / (float)(max_value - min_value) : 0;

     if (orientation == Orientation::HORIZONTAL) {
         this->handle_position = {position.x - length / 2 + int(length * ratio), position.y};
     } else {
         this->handle_position = {position.x, position.y - length / 2 + int(length * ratio)};
     }
}

void Slider::Draw() {
     int length = max(size.x, size.y);
     int thickness = min(size.x, size.y);
     int handle_size = thickness;

     // test
     if (orientation == Orientation::HORIZONTAL) {
          gout << move_to(position.x - length / 2, position.y - thickness / 2 + 5)
               << color(60, 60, 60)
               << box(length, thickness - 10);

          gout << move_to(position.x - length / 2 + BORDER_SIZE, position.y - thickness / 2 + BORDER_SIZE + 5)
               << color(texture.r, texture.g, texture.b)
               << box(length - BORDER_SIZE * 2, thickness - BORDER_SIZE * 2 - 10);
     } else {
          gout << move_to(position.x - thickness / 2 + 5, position.y - length / 2)
               << color(60, 60, 60)
               << box(thickness - 10, length);

          gout << move_to(position.x - thickness / 2 + BORDER_SIZE + 5, position.y - length / 2 + BORDER_SIZE)
               << color(texture.r, texture.g, texture.b)
               << box(thickness - BORDER_SIZE * 2 - 10, length - BORDER_SIZE * 2);
     }
     // fogó
     int r_outer = handle_size / 2;
     int r_inner = r_outer - BORDER_SIZE;

     for (int y = -r_outer; y <= r_outer; ++y) {
          int dx_outer = sqrt(r_outer * r_outer - y * y);
          gout << move_to(handle_position.x - dx_outer, handle_position.y + y)
               << color(60, 60, 60)
               << box(dx_outer * 2, 1);

          if (y >= -r_inner && y <= r_inner) {
               int dx_inner = sqrt(r_inner * r_inner - y * y);
               gout << move_to(handle_position.x - dx_inner, handle_position.y + y)
                    << color(texture.r, texture.g, texture.b)
                    << box(dx_inner * 2, 1);
          }
     }
}

void Slider::Interact(event ev) {
     int length = std::max(size.x, size.y);

     if (ev.button == btn_left) {
          pressed = true;
     }
     if (ev.button == -btn_left) {
          pressed = false;
     }

     if (pressed) {
          if (orientation == Orientation::HORIZONTAL) {
               handle_position.x = clamp(ev.pos_x, position.x - length / 2, position.x + length / 2);
               value = min_value + (max_value - min_value) * (float(handle_position.x - (position.x - length / 2)) / length);
          } else {
               handle_position.y = clamp(ev.pos_y, position.y - length / 2, position.y + length / 2);
               value = min_value + (max_value - min_value) * (float(handle_position.y - (position.y - length / 2)) / length);
          }
     }
}
