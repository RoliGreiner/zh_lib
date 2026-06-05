//
// Created by larix on 2026. 05. 15..
//

#ifndef APP_H
#define APP_H

#include "widget.h"
#include <vector>

#include "spin_box.h"

class Label;
class Button;
class Widget;
class List;
class TextInput;
class SpinBox;

using namespace std;

struct Rack {
    string name;
    int size;
};

class App {
    int width;
    int height;
    int default_font_size;

    //Könnyebb kezelhetőség
    vector<Rack*> racks = {};
    vector<Rack*> server_structure = {};


    vector<Widget*> widgets;

    TextInput* rack_name;
    List* rack_size;
    Button* update_rack;
    List* rack_configs;
    SpinBox* number_of_new_racks;
    Button* add_rack;
    Button* remove_rack;
    List* server;
    Label* server_size;

protected:
    void UpdateRacks();
    void AddToServer();
    void RemoveFromServer();
    string CalculateServerSize();
    void UpdateRackConfig();
    void UpdateServer();

public:
    App(int width = 1200, int height = 1000, int font_size = 20);
    ~App();

    int Width() const { return width; }
    int Height() const { return height; }
    int FontSize() const { return default_font_size; }

    void RegisterWidget(Widget* w);
    void ClearWindow();
    void Refresh();
    void EventLoop();
    void Start();
};

#endif // APP_H