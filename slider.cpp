//
// Created by larix on 2026. 04. 20..
//

#include "slider.h"
#include <algorithm>

using namespace std;

Slider::Slider(Vector2 position, Vector2 size, Color texture, int min_value, int max_value, int value, Orientation orientation, bool transparent)
: Widget(position, size, texture, transparent) {
     this->min_value = min_value;
     this->max_value = max_value;
     this->value = value;
     this->orientation = orientation;

     // Automatically determine length and thickness regardless of how size is passed
     int length = std::max(size.x, size.y);

     float ratio = (float)(value - min_value) / (float)(max_value - min_value);

     if (orientation == Orientation::HORIZONTAL) {
         this->handle_position = {position.x - length / 2 + int(length * ratio), position.y};
     } else {
         this->handle_position = {position.x, position.y - length / 2 + int(length * ratio)};
     }
}

void Slider::Draw() {
     // Automatically determine length and thickness to keep the handle uniform
     int length = std::max(size.x, size.y);
     int thickness = std::min(size.x, size.y);
     int handle_size = thickness; // The handle is always a square matching the thickness

     if (orientation == Orientation::HORIZONTAL) {
          // Horizontal track (keret & belseje)
          gout << move_to(position.x - length / 2, position.y - thickness / 2 + 5)
               << color(60, 60, 60)
               << box(length, thickness - 10);

          gout << move_to(position.x - length / 2 + BORDER_SIZE, position.y - thickness / 2 + BORDER_SIZE + 5)
               << color(texture.r, texture.g, texture.b)
               << box(length - BORDER_SIZE * 2, thickness - BORDER_SIZE * 2 - 10);

          // Horizontal handle
          gout << move_to(handle_position.x - handle_size / 2, handle_position.y - handle_size / 2)
               << color(60, 60, 60)
               << box(handle_size, handle_size);

          gout << move_to(handle_position.x - handle_size / 2 + BORDER_SIZE, handle_position.y - handle_size / 2 + BORDER_SIZE)
               << color(texture.r, texture.g, texture.b)
               << box(handle_size - BORDER_SIZE * 2, handle_size - BORDER_SIZE * 2);
     } else {
          // Vertical track (keret & belseje)
          gout << move_to(position.x - thickness / 2 + 5, position.y - length / 2)
               << color(60, 60, 60)
               << box(thickness - 10, length);

          gout << move_to(position.x - thickness / 2 + BORDER_SIZE + 5, position.y - length / 2 + BORDER_SIZE)
               << color(texture.r, texture.g, texture.b)
               << box(thickness - BORDER_SIZE * 2 - 10, length - BORDER_SIZE * 2);

          // Vertical handle
          gout << move_to(handle_position.x - handle_size / 2, handle_position.y - handle_size / 2)
               << color(60, 60, 60)
               << box(handle_size, handle_size);

          gout << move_to(handle_position.x - handle_size / 2 + BORDER_SIZE, handle_position.y - handle_size / 2 + BORDER_SIZE)
               << color(texture.r, texture.g, texture.b)
               << box(handle_size - BORDER_SIZE * 2, handle_size - BORDER_SIZE * 2);
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