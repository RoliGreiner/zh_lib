//
// Created by larix on 2026. 06. 05..
//

#include "spin_box.h"

SpinBox::SpinBox(App* app, Vector2 position, Vector2 size, Color texture,
                 int min_value, int max_value, int step, int initial_value)
    : Widget(app, position, size, texture) {
    this->min_value = min_value;
    this->max_value = max_value;
    this->step = step;
    value = initial_value;

    if (value < min_value) value = min_value;
    if (value > max_value) value = max_value;
}

void SpinBox::Increment() {
    value = min(value + step, max_value);
}

void SpinBox::Decrement() {
    value = max(value - step, min_value);
}

void SpinBox::Draw() {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};
    const int BTN_W = 24;

    // keret
    gout << color(60, 60, 60) << move_to(top_left.x, top_left.y) << box(size.x, size.y);

    // belső terület
    int inner_x = top_left.x + BORDER_SIZE;
    int inner_y = top_left.y + BORDER_SIZE;
    int inner_w = size.x - BORDER_SIZE * 2;
    int inner_h = size.y - BORDER_SIZE * 2;

    gout << color(texture.r, texture.g, texture.b)
         << move_to(inner_x, inner_y) << box(inner_w, inner_h);

    // érték szövege (balra igazítva, függőlegesen középen)
    string value_text = to_string(value);
    gout << color(0, 0, 0)
         << move_to(inner_x + 5, position.y - gout.cascent() / 2)
         << genv::text(value_text);

    // fel / le nyomógombok a jobb szélen
    int btn_x = inner_x + inner_w - BTN_W;
    int half = inner_h / 2;

    gout << color(200, 200, 200) << move_to(btn_x, inner_y) << box(BTN_W, half);            // fel
    gout << color(180, 180, 180) << move_to(btn_x, inner_y + half) << box(BTN_W, inner_h - half); // le

    // elválasztó vonalak
    gout << color(60, 60, 60);
    gout << move_to(btn_x, inner_y) << box(1, inner_h);        // szöveg és gombok között
    gout << move_to(btn_x, inner_y + half) << box(BTN_W, 1);   // fel és le gomb között

    // + és - jelek a gombok közepére
    string up = "+";
    string down = "-";
    gout << color(0, 0, 0);
    gout << move_to(btn_x + BTN_W / 2 - gout.twidth(up) / 2,
                    inner_y + half / 2 - gout.cascent() / 2)
         << genv::text(up);
    gout << move_to(btn_x + BTN_W / 2 - gout.twidth(down) / 2,
                    inner_y + half + (inner_h - half) / 2 - gout.cascent() / 2)
         << genv::text(down);
}

void SpinBox::Interact(event ev) {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};
    int inner_x = top_left.x + BORDER_SIZE;
    int inner_y = top_left.y + BORDER_SIZE;
    int inner_w = size.x - BORDER_SIZE * 2;
    int inner_h = size.y - BORDER_SIZE * 2;

    const int BTN_W = 24;
    int btn_x = inner_x + inner_w - BTN_W;
    int half = inner_h / 2;

    // kattintás a fel / le gombra
    if (ev.type == ev_mouse && ev.button == btn_left) {
        bool in_buttons = ev.pos_x > btn_x && ev.pos_x < btn_x + BTN_W &&
                          ev.pos_y > inner_y && ev.pos_y < inner_y + inner_h;
        if (in_buttons) {
            if (ev.pos_y < inner_y + half) {
                Increment();
            } else {
                Decrement();
            }
        }
    }

    // görgetés a widget felett
    if (ev.type == ev_mouse && UnderMouse({ev.pos_x, ev.pos_y})) {
        if (ev.button == btn_wheelup) {
            Increment();
        } else if (ev.button == btn_wheeldown) {
            Decrement();
        }
    }
}

int SpinBox::GetValue() const {
    return value;
}

void SpinBox::SetValue(int new_value) {
    value = new_value;
    if (value < min_value) value = min_value;
    if (value > max_value) value = max_value;
}