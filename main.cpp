#include "graphics.hpp"
#include "widget.h"
#include <vector>

using namespace std;
using namespace genv;

const int WIDTH = 1000;
const int HEIGHT = 800;

void EventLoop(vector<Widget*> widgets);
void ClearWindow();

class App {
    vector<Widget*> widgets;

public:
    App() {
        widgets.push_back(new Widget({200, 200}, {100, 100}, {0, 50, 200}));
    }
    void Start() {
        EventLoop(widgets);
        for (Widget* widget: widgets) {
            delete widget;
        }
    }
};

int main() {
    gout.open(WIDTH, HEIGHT);
    gout << refresh;
    App app = App();
    app.Start();

    return 0;
}

void EventLoop(vector<Widget *> widgets) {
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        ClearWindow();

        for (Widget* widget: widgets) {
            widget->Draw();
        }

        gout << refresh;
    }
}

void ClearWindow() {
    gout << move_to(0, 0) << color(255, 255, 255) << box(WIDTH, HEIGHT);
}
