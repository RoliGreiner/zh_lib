//
// Created by larix on 2026. 05. 17..
//

#include "label.h"
#include "app.h"

Label::Label(App* app, Vector2 position, Vector2 size, string text, int font_size, Align alignment, Color color_override)
    : Widget(app, position, size, color_override, true) {
    this->text = text;
    this->font_size = font_size;
    this->alignment = alignment;
}

void Label::Draw() {
    gout << font("LiberationMono-Regular.ttf", font_size);

    int x;
    switch (alignment) {
        case Align::Left:
            x = position.x - size.x / 2 + APPEND;   // left edge + inset
            break;
        case Align::Right:
            x = position.x + size.x / 2 - gout.twidth(text) - APPEND;   // right edge - text - inset
            break;
        case Align::Center:
        default:
            x = position.x - gout.twidth(text) / 2;   // centred on position.x
            break;
    }

    // Vertically centred on position.y (box centre), independent of size.y.
    int y = position.y - gout.cascent() + gout.cdescent();

    Color text_color = Resolve(GetTheme().text);
    gout << color(text_color.r, text_color.g, text_color.b)
         << move_to(x, y)
         << genv::text(text);

    // Restore the app's default font.
    gout << font("LiberationMono-Regular.ttf", app->FontSize());
}
