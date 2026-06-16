//
// theme.h  -  global colour scheme for the widget library.
//
// One Theme drives the colours of every widget. You pick a preset (or build
// your own) and hand it to the App constructor; from then on every widget
// follows it automatically. No per-widget colours required.
//
#ifndef THEME_H
#define THEME_H

struct Color {
    int r = 0, g = 0, b = 0, a = 255;
};

static constexpr Color USE_THEME{ -1, -1, -1, -1 };
inline bool IsThemeColor(const Color& c) { return c.r < 0; }

inline int Clamp255(int v) { return v < 0 ? 0 : (v > 255 ? 255 : v); }

inline Color Lighten(Color c, int amount) {
    return { Clamp255(c.r + amount), Clamp255(c.g + amount), Clamp255(c.b + amount), c.a };
}
inline Color Darken(Color c, int amount) {
    return { Clamp255(c.r - amount), Clamp255(c.g - amount), Clamp255(c.b - amount), c.a };
}

inline Color Mix(Color x, Color y, float t) {
    return {
        Clamp255(int(x.r + (y.r - x.r) * t)),
        Clamp255(int(x.g + (y.g - x.g) * t)),
        Clamp255(int(x.b + (y.b - x.b) * t)),
        255};
}

struct Theme {
    Color window;          // app background
    Color surface;         // main widget fill (inputs, lists, spin boxes...)
    Color surface_alt;     // secondary fill (slider track, spin buttons, empty rows)
    Color border;          // outlines / grid lines
    Color accent;          // primary action / highlight / slider fill / checkmark
    Color accent_hover;    // accent under the mouse
    Color accent_pressed;  // accent while pressed
    Color selection;       // selected list row background
    Color text;            // primary text
    Color text_muted;      // ghost text / secondary text / arrows
    Color text_on_accent;  // text/icon drawn on top of an accent fill

    int radius = 4;        // global corner radius (px); 0 = square corners

    static Theme Dark();
    static Theme Light();
    static Theme Midnight();
};

inline Theme Theme::Dark() {
    Theme t;
    t.window         = { 24,  27,  34};
    t.surface        = { 38,  42,  53};
    t.surface_alt    = { 30,  34,  44};
    t.border         = { 58,  64,  79};
    t.accent         = { 88, 166, 255};
    t.accent_hover   = Lighten(t.accent, 26);
    t.accent_pressed = Darken (t.accent, 38);
    t.selection      = { 46,  80, 124};
    t.text           = {230, 233, 239};
    t.text_muted     = {138, 146, 162};
    t.text_on_accent = { 14,  18,  26};
    return t;
}

inline Theme Theme::Light() {
    Theme t;
    t.window         = {244, 246, 250};
    t.surface        = {255, 255, 255};
    t.surface_alt    = {236, 240, 246};
    t.border         = {205, 212, 222};
    t.accent         = { 37,  99, 235};
    t.accent_hover   = Lighten(t.accent, 24);
    t.accent_pressed = Darken (t.accent, 32);
    t.selection      = {209, 226, 252};
    t.text           = { 28,  31,  38};
    t.text_muted     = {120, 128, 142};
    t.text_on_accent = {255, 255, 255};
    return t;
}

inline Theme Theme::Midnight() {
    Theme t;
    t.window         = { 17,  18,  26};
    t.surface        = { 31,  33,  46};
    t.surface_alt    = { 24,  26,  38};
    t.border         = { 52,  55,  74};
    t.accent         = {167, 139, 250};
    t.accent_hover   = Lighten(t.accent, 24);
    t.accent_pressed = Darken (t.accent, 40);
    t.selection      = { 62,  56, 104};
    t.text           = {233, 233, 244};
    t.text_muted     = {146, 148, 170};
    t.text_on_accent = { 18,  16,  30};
    return t;
}

#endif // THEME_H
