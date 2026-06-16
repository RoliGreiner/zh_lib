//
// Created by larix on 2026. 06. 08..
//

#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include "widget.h"
#include "slider.h"

using namespace std;

class ProgressBar : public Widget {
protected:
    int value;
    int min_value, max_value;
    Orientation orientation;
    bool show_value;

public:
    ProgressBar(App* app, Vector2 position, Vector2 size, int min_value, int max_value, int value = 0, Orientation orientation = Orientation::HORIZONTAL, bool show_value = false, bool transparent = false, Color color_override = USE_THEME);
    void Draw() override;

    int  GetValue() const { return value; }
    void SetValue(int v);
    void SetRange(int lo, int hi) { min_value = lo; max_value = hi; SetValue(value); }
};

#endif // PROGRESS_BAR_H