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

    vector<Widget*> widgets;

public:
    App(int width = 1200, int height = 1000);
    ~App();

    int Width() const { return width; }
    int Height() const { return height; }

    void RegisterWidget(Widget* w);
    void ClearWindow();
    void Refresh();
    void EventLoop();
    void Start();
};

#endif // APP_H