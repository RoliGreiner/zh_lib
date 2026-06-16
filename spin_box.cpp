//
// Created by larix on 2026. 06. 05..
//

#include "spin_box.h"
#include <algorithm>

SpinBox::SpinBox(App* app, Vector2 position, Vector2 size, int min_value, int max_value, int step, int initial_value, Color color_override)
    : Widget(app, position, size, color_override) {
    this->min_value = min_value;
    this->max_value = max_value;
    this->step = step;
    value = initial_value;

    value = clamp(value, min_value, max_value);
}

void SpinBox::Increment() { value = min(value + step, max_value); }
void SpinBox::Decrement() { value = max(value - step, min_value); }

void SpinBox::Draw() {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};
    const int BTN_W = 26;
    int radius = Radius();
    int inner_radius = radius - BORDER_SIZE;

    Color fill = Resolve(GetTheme().surface);

    // keret + belső
    FillRoundedBox(top_left.x, top_left.y, size.x, size.y, radius, GetTheme().border);

    int inner_x = top_left.x + BORDER_SIZE;
    int inner_y = top_left.y + BORDER_SIZE;
    int inner_width = size.x - BORDER_SIZE * 2;
    int inner_height = size.y - BORDER_SIZE * 2;

    FillRoundedBox(inner_x, inner_y, inner_width, inner_height, inner_radius, fill);

    // érték szövege
    string value_text = to_string(value);
    Color text_color = GetTheme().text;
    gout << color(text_color.r, text_color.g, text_color.b)
         << move_to(inner_x + 6, position.y - (gout.cascent() + gout.cdescent()) / 2)
         << genv::text(value_text);

    // fel / le gombok (a jobb sarkok lekerekítve, hogy illeszkedjenek a kerethez)
    int btn_x = inner_x + inner_width - BTN_W;
    int half = inner_height / 2;

    Vector2 m = MousePos();
    bool over_up = m.x > btn_x && m.x < btn_x + BTN_W && m.y > inner_y && m.y < inner_y + half;
    bool over_down = m.x > btn_x && m.x < btn_x + BTN_W && m.y >= inner_y + half && m.y < inner_y + inner_height;

    Color up_c = over_up ? Mix(GetTheme().surface_alt, GetTheme().accent, 0.30f) : GetTheme().surface_alt;
    Color down_c = over_down ? Mix(GetTheme().surface_alt, GetTheme().accent, 0.30f) : Darken(GetTheme().surface_alt, 6);

    FillRoundedBoxEx(btn_x, inner_y, BTN_W, half, inner_radius,
                     false, true, false, false, up_c);              // top-right
    FillRoundedBoxEx(btn_x, inner_y + half, BTN_W, inner_height - half, inner_radius,
                     false, false, false, true, down_c);            // bottom-right

    // elválasztó vonalak
    gout << color(GetTheme().border.r, GetTheme().border.g, GetTheme().border.b);
    gout << move_to(btn_x, inner_y) << box(1, inner_height);
    gout << move_to(btn_x, inner_y + half) << box(BTN_W, 1);

    // + és - jelek
    string up = "+";
    string down = "-";
    gout << color(text_color.r, text_color.g, text_color.b);
    gout << move_to(btn_x + BTN_W / 2 - gout.twidth(up) / 2,
                    inner_y + half / 2 - gout.cascent() / 2)
         << genv::text(up);
    gout << move_to(btn_x + BTN_W / 2 - gout.twidth(down) / 2,
                    inner_y + half + (inner_height - half) / 2 - gout.cascent() / 2)
         << genv::text(down);
}

void SpinBox::Interact(event ev) {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};
    int inner_x = top_left.x + BORDER_SIZE;
    int inner_y = top_left.y + BORDER_SIZE;
    int inner_width = size.x - BORDER_SIZE * 2;
    int inner_height = size.y - BORDER_SIZE * 2;

    const int BTN_W = 26;
    int btn_x = inner_x + inner_width - BTN_W;

    if (ev.type == ev_mouse && ev.button == btn_left) {
        bool in_buttons = ev.pos_x > btn_x && ev.pos_x < btn_x + BTN_W &&
                          ev.pos_y > inner_y && ev.pos_y < inner_y + inner_height;
        if (in_buttons) {
            if (ev.pos_y < inner_y + inner_height / 2) Increment();
            else                           Decrement();
        }
    }

    if (ev.type == ev_mouse && UnderMouse({ev.pos_x, ev.pos_y})) {
        if (ev.button == btn_wheelup)        Increment();
        else if (ev.button == btn_wheeldown) Decrement();
    }
}

int SpinBox::GetValue() const { return value; }

void SpinBox::SetValue(int new_value) {
    value = new_value;
    if (value < min_value) value = min_value;
    if (value > max_value) value = max_value;
}
