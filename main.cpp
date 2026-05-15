#include "widget.h"
#include "button.h"
#include "slider.h"
#include "text_input.h"
#include "text_field.h"
#include <vector>
#include <iostream>
#include <fstream>

#include "list.h"

using namespace genv;
using namespace std;

const int WIDTH = 1200;
const int HEIGHT = 1000;

void ClearWindow();

class App {
    vector<Widget*> widgets;
    List* list_a;
    List* list_b;

public:
    void Test() {
        cout << "Hello" << endl;
    }
    void Test2() {
        cout << "Bobr" << endl;
    }
    void MoveItem(List* list_a, List* list_b) {
        string item = list_b->GetValue();
        if (!item.empty()) {
            list_a->AddItem(item);
            list_b->RemoveCurrent();
        }
    }
    void AddItem()
    App() {/*
        widgets.push_back(new Widget(
            {WIDTH / 2, 50},
            {500, 80},
            {0, 50, 150}
        ));
        widgets.push_back(new Button(
            {100, 200},
            {100, 40},
            {200, 100, 50},
            "Hello",
            [this] {Test();}
        ));
        widgets.push_back(new Button(
            {200, 200},
            {100, 40},
            {50, 200, 150},
            "Hód",
            [this] {Test2();}
        ));
        widgets.push_back(new Slider(
            {500, 200},
            {200, 20},
            {255, 200, 255},
            0, 100, 50
        ));
        widgets.push_back(new Slider(
            {800, HEIGHT / 2},
            {200, 20},
            {255, 255, 255},
            0, 100, 50,
            Orientation::VERTICAL
        ));
        widgets.push_back(new TextInput(
            {500, 300},
            {500, 40},
            {255, 255, 255},
            "Test"
        ));

        vector<string> text;
        fstream fin("angol.txt");
        while (fin.good()) {
            string line;
            getline(fin, line);
            text.push_back(line);
        }
        fin.close();

        widgets.push_back(new TextField(
            {WIDTH / 2, 500},
            {500, 300},
            {200, 200, 200},
            text,
            16,
            true
        )); */
        vector<string> elemek = {"egy", "kettő", "hat"};
        list_a = new List({100, 100}, {150, 30}, {255, 255, 255}, elemek);
        widgets.push_back(list_a);

        elemek.clear();
        elemek = {"alma", "körte", "banán", "málna"};
        list_b = new List({300, 100}, {150, 30}, {255, 255, 255}, elemek);
        widgets.push_back(list_b);

        widgets.push_back(new Button(
            {100, 50},
            {100, 50},
            {255, 255, 255},
            "jobbra",
            [this]{MoveItem(list_b, list_a);}));

        widgets.push_back(new Button(
            {300, 50},
            {100, 50},
            {255, 255, 255},
            "balre",
            [this]{MoveItem(list_a, list_b);}));

        ClearWindow();
        for (Widget* widget : widgets) {
            widget->Draw();
        }
        gout << refresh;
    }
    void EventLoop() {
        event ev;
        int focus = -1;
        while (gin >> ev && ev.keycode != key_escape) {
            ClearWindow();
            if (ev.button == btn_left) {
                for (int i = 0; i < widgets.size(); i++) {
                    if (widgets[i]->UnderMouse({ev.pos_x, ev.pos_y})) {
                        focus = i;
                        break;;
                    }
                    if (i == widgets.size() - 1) {
                        focus = -1;
                    }
                }
            }

            if (focus != -1) {
                widgets[focus]->Interact(ev);
            }

            if (ev.keycode == key_left) {
                string item = list_b->GetValue();
                if (!item.empty()) {
                    list_a->AddItem(item);
                    list_b->RemoveCurrent();
                }
            }
            if (ev.keycode == key_right) {
                string item = list_a->GetValue();
                if (!item.empty()) {
                    list_b->AddItem(item);
                    list_a->RemoveCurrent();
                }
            }

            for (Widget* widget : widgets) {
                widget->Draw();
            }
            gout << refresh;
        }
    }
    void Start() {
        EventLoop();
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

void ClearWindow() {
    gout << move_to(0, 0) << color(255, 255, 255) << box(WIDTH, HEIGHT);
}
