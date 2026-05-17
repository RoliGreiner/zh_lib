//
// Created by larix on 2026. 05. 17..
//

#include "label.h"
#include "app.h"

Label::Label(App* app, Vector2 position, Vector2 size, Color texture, string text, int font_size, bool transparent)
: Widget(app, position, size, texture, transparent) {
    this->text = text;
    this->font_size = font_size;
}

void Label::Draw() {
    if (!transparent) {
        DrawFrame({60, 60, 60, 255});
    }

    gout << color(0, 0, 0)
         << font("LiberationMono-Regular.ttf", font_size)
         << move_to(position.x - gout.twidth(text) / 2, position.y - (gout.cascent() + gout.cdescent()) / 2)
         << genv::text(text);

    gout << font("LiberationMono-Regular.ttf", app->FontSize());
}