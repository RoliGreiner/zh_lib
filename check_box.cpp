//
// Created by larix on 2026. 05. 21..
//

#include "check_box.h"

CheckBox::CheckBox(App* app, Vector2 position, Vector2 size, bool state, bool transparent, Color color_override)
    : Widget(app, position, size, color_override, transparent) {
    checked = state;
}

void CheckBox::Draw() {
    if (transparent)
        return;

    Color accent = Resolve(GetTheme().accent);
    Color box_fill = checked ? (Hovered() ? GetTheme().accent_hover : accent)
                             : (Hovered() ? Mix(GetTheme().surface, GetTheme().accent, 0.18f) : GetTheme().surface);
    Color bord = checked ? accent : GetTheme().border;

    int radius = Radius();
    int x = position.x - size.x / 2;
    int y = position.y - size.y / 2;

    FillRoundedBox(x, y, size.x, size.y, radius, bord);
    FillRoundedBox(x + BORDER_SIZE, y + BORDER_SIZE,
                   size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2, radius - BORDER_SIZE, box_fill);

    // pipa
    if (checked) {
        Color tick = GetTheme().text_on_accent;
        gout << color(tick.r, tick.g, tick.b)
             << move_to(position.x - size.x / 2 + 5, position.y - size.y / 2 + 5) << line_to(position.x + size.x / 2 - 5, position.y + size.y / 2 - 5)
             << move_to(position.x - size.x / 2 + 5, position.y + size.y / 2 - 5) << line_to(position.x + size.x / 2 - 5, position.y - size.y / 2 + 5);
    }
}

void CheckBox::Interact(event ev) {
    if (ev.button == btn_left) {
        checked = !checked;
    }
}
