//
// Created by larix on 2026. 04. 30..
//

#ifndef LIST_H
#define LIST_H

#include "widget.h"

using namespace std;

enum class ListType { Dropdown, Plain };

class List : public Widget {
protected:
    vector<string> items = {};
    int selected_index;
    int scroll_offset;
    int max_visible_items;
    bool opened;
    ListType type;

public:
    List(App* app, Vector2 position, Vector2 size, vector<string> items, int max_visible_items = 5, ListType type = ListType::Dropdown, Color color_override = USE_THEME);
    void Draw() override;
    void Interact(event ev) override;
    bool UnderMouse(Vector2 mouse_pos) override;
    void FocusLost() override;
    string GetValue();
    int GetSize() { return items.size(); }
    int GetCurrentIndex() { return selected_index; }
    void SetCurrentIndex(int index) {
        if (index < 0 || index >= (int)items.size()) return;
        selected_index = index;
    }
    vector<string> GetContent() { return items; }
    void OverwriteContent(vector<string> items);
    void RemoveAt(int index);
    void RemoveCurrent();
    void AddItem(string item);
};

#endif // LIST_H
