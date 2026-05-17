//
// Created by larix on 2026. 05. 15..
//

#ifndef APP_H
#define APP_H

#include "widget.h"
#include <vector>

using namespace std;

class Widget;

class App {
    int width;
    int height;
    int default_font_size;

    vector<Widget*> widgets;

    Widget* list_a;
    Widget* list_b;

public:
    App(int width = 1200, int height = 1000, int font_size = 20);
    ~App();

    int Width() const { return width; }
    int Height() const { return height; }
    int FontSize() const { return default_font_size; }

    void RegisterWidget(Widget* w);
    void MoveItem(Widget* from, Widget* to);
    void ClearWindow();
    void Refresh();
    void EventLoop();
    void Start();
};

#endif // APP_H