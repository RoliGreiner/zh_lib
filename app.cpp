//
// Created by larix on 2026. 05. 15..
//

#include "app.h"
#include "button.h"
#include "list.h"
#include "label.h"
#include "text_input.h"
#include "spin_box.h"

#include "graphics.hpp"
#include <iostream>

using namespace genv;
using namespace std;

App::App(int width, int height, int font_size)
: width(width), height(height), default_font_size(font_size) {
    gout.open(width, height);
    gout << font("LiberationMono-Regular.ttf", 20);
    gout << refresh;

    new Label(
        this,
        {100, 50},
        {100, 40},
        {255, 255, 255},
        "Név:", 20);
    rack_name = new TextInput(
        this,
        {300, 50},
        {300, 40},
        {255, 255, 255},
        "Server-XY");
    new Label(
        this,
        {100, 100},
        {100, 40},
        {255, 255, 255},
        "Tipus:", 20);
    rack_size = new List(
        this,
        {175, 100},
        {50, 40},
        {255, 255, 255},
        {"U1", "U2", "U3", "U4"}, 4, ListType::Plain);
    update_rack = new Button(
        this,
        {375, 100},
        {150, 40},
        {255, 255, 255},
        "Új/Frissít",
        [this]{this->UpdateRacks();});
    rack_configs = new List(
        this,
        {150, 300},
        {200, 40},
        {255, 255, 255},
        {}, 6, ListType::Plain);
    new Label(
        this,
        {300, 300},
        {50, 40},
        {255, 255, 255},
        "db:",
        20);
    number_of_new_racks = new SpinBox(
        this,
        {400, 300},
        {100, 40},
        {255, 255, 255},
        1, 100, 1, 1);
    add_rack = new Button(
        this,
        {400, 350},
        {100, 40},
        {255, 255, 255},
        "Bővítés",
        [this]{AddToServer();});
    remove_rack = new Button(
        this,
        {400, 400},
        {100, 40},
        {255, 255, 255},
        "Törlés",
        [this]{RemoveFromServer();});
    server = new List(
        this,
        {725, 50},
        {450, 40},
        {255, 255, 255},
        {}, 20, ListType::Plain);
    server_size = new Label(
        this,
        {width/2, 950},
        {0, 0},
        {255, 255, 255},
        CalculateServerSize(),
        20);

    ClearWindow();
    Refresh();
}

App::~App() {
    for (Widget* widget : widgets) {
        delete widget;
    }
    widgets.clear();
}

void App::RegisterWidget(Widget* w) {
    widgets.push_back(w);
}

void App::ClearWindow() {
    gout << move_to(0, 0) << color(100, 150, 200) << box(width, height);
}

void App::Refresh() {
    for (Widget* widget : widgets) {
        widget->Draw();
    }
    gout << refresh;
}

void App::EventLoop() {
    event ev;
    int focus = -1;
    while (gin >> ev && ev.keycode != key_escape) {
        ClearWindow();

        if (ev.button == btn_left) {
            focus = -1;
            for (int i = 0; i < (int)widgets.size(); i++) {
                if (widgets[i]->UnderMouse({ev.pos_x, ev.pos_y})) {
                    focus = i;
                    break;
                }
            }
        }

        if (focus != -1) {
            widgets[focus]->Interact(ev);
        }

        Refresh();
    }
}

void App::Start() {
    EventLoop();
}

void App::UpdateRacks() {
    string name = rack_name->GetText();
    int size = rack_size->GetCurrentIndex() + 1;

    for (Rack* rack: racks) {
        if (rack->name == name) {
            if (rack->size != size) {
                rack->size = size;
                UpdateRackConfig();
            }
            return;
        }
    }

    racks.push_back(new Rack(name, size));
    UpdateRackConfig();
}

void App::AddToServer() {
    if (rack_configs->GetSize() == 0) {
        return;
    }
    Rack* rack = racks[rack_configs->GetCurrentIndex()];
    int quantity = number_of_new_racks->GetValue();

    for (; quantity != 0; quantity--) {
        server_structure.push_back(rack);
    }
    cout << to_string(server_structure.size()) << endl;
    UpdateServer();
}

void App::RemoveFromServer() {
    if (server_structure.size() == 0) {
        return;
    }

    int selected_row = server->GetCurrentIndex();
    int progress = 0;
    for (int i = 0; i < server_structure.size(); i++) {
        if (progress <= selected_row && selected_row <= progress + server_structure[i]->size - 1) {
            server_structure.erase(server_structure.begin() + i);
            UpdateServer();
            server->SetCurrentIndex((server->GetSize() <= progress ? progress - 1 : progress));
            return;
        }
        progress += server_structure[i]->size;
    }
}

string App::CalculateServerSize() {
    return to_string(server_structure.size()) + " gép " + to_string(server->GetSize()) + "U helyet foglal el";
}


void App::UpdateRackConfig() {
    vector<string> new_racks = {};

    for (Rack* rack: racks) {
        string name = rack->name + "(U" + to_string(rack->size) + ")";
        new_racks.push_back(name);
    }

    rack_configs->OverwriteContent(new_racks);
    UpdateServer();
}

void App::UpdateServer() {
    vector<string> new_server = {};

    for (Rack* rack: server_structure) {
        switch (rack->size) {
            case 1:
                new_server.push_back("<" + rack->name + "/" + "1");
                break;
            case 2:
                new_server.push_back("/" + rack->name + "/" + "1");
                new_server.push_back("\\" + rack->name + "/" + "2");
                break;
            default:

                new_server.push_back("/" + rack->name + "/" + "1");
                for (int i = 2; i < rack->size; i++) {
                    new_server.push_back("|" + rack->name + "/" + to_string(i));
                }
                new_server.push_back("\\" + rack->name + "/" + "4");
                break;
        }
    }

    server->OverwriteContent(new_server);
    server_size->UpdateText(CalculateServerSize());
}
