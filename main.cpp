#include "widget.h"
#include "button.h"
#include <vector>
#include <iostream>

using namespace genv;
using namespace std;

const int WIDTH = 1000;
const int HEIGHT = 800;

void EventLoop(vector<Widget*> widgets);
void ClearWindow();
void Test() {
    cout << "Hello" << endl;
}

class App {
    vector<Widget*> widgets;

public:
    void Test() {
        cout << "Hello" << endl;
    }
    App() {
        widgets.push_back(new Widget({200, 200}, {100, 100}, {0, 50, 200}));
        widgets.push_back(new Button(
            {200, 500},
            {100, 40},
            {255, 255, 255},
            "Hello",
            [this]() { this->Test();}
        ));
    }
    void Start() {
        EventLoop(widgets);
        for (Widget* widget : widgets) {
            delete widget;
        }
    }
};

int main() {
    gout.open(WIDTH, HEIGHT);
    gout << font("LiberationMono-Regular.ttf", 20);
    gout << refresh;
    App app = App();
    app.Start();

    return 0;
}

void EventLoop(vector<Widget*> widgets) {
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        ClearWindow();

        if (ev.button == btn_left) {
            for (Widget* widget : widgets) {
                Button* button = dynamic_cast<Button*>(widget);

                if (button != nullptr) {
                    if (button->UnderMouse({ev.pos_x, ev.pos_y})) {
                        button->Press();
                    }
                }
            }
        }

        for (Widget* widget : widgets) {
            widget->Draw();
        }

        gout << refresh;
    }
}

void ClearWindow() {
    gout << move_to(0, 0) << color(255, 255, 255) << box(WIDTH, HEIGHT);
}
