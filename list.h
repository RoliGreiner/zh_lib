//
// Created by larix on 2026. 04. 30..
//

#ifndef LIST_H
#define LIST_H

#include "widget.h"

using namespace std;

class List : public Widget {
protected:
    vector<string> items;
    int selected_index;
    int scroll_offset;
    int max_visible_items;
    bool opened;

public:
    List(App* app, Vector2 position, Vector2 size, Color texture, vector<string> items, int max_visible_items = 5);
    void Draw() override;
    void Interact(event ev) override;
    bool UnderMouse(Vector2 mouse_pos) override;
    string GetValue();
    void RemoveCurrent();
    void AddItem(string item);
    void FocusLost();
};

#endif // LIST_H