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
    //keret
    gout << move_to(position.x - size.x / 2, position.y - size.y / 2)
         << color(60, 60, 60)
         << box(size.x, size.y);

    //belseje
    gout << move_to(position.x - size.x / 2 + BORDER_SIZE, position.y - size.y / 2 + BORDER_SIZE)
         << color(texture.r, texture.g, texture.b)
         << box(size.x - BORDER_SIZE * 2, size.y - BORDER_SIZE * 2);

    //szöveg
    gout << color(0, 0, 0)
         << move_to(position.x - gout.twidth(text) / 2, position.y - (gout.cascent() + gout.cdescent()) / 2)
         << font("LiberationMono-Regular.ttf", font_size)
         << genv::text(text);
    gout << font("LiberationMono-Regular.ttf", app->FontSize());
}