//
// Created by larix on 2026. 04. 30..
//

#include "list.h"

List::List(App* app, Vector2 position, Vector2 size, Color texture, vector<string> items,
           int max_visible_items, ListType type)
    : Widget(app, position, size, texture) {
    this->items = items;
    this->max_visible_items = max_visible_items;
    this->type = type;
    selected_index = 0;
    scroll_offset = 0;
    opened = false; // a Plain lista sosem használja, mindig "nyitva" rajzol
}

bool List::UnderMouse(Vector2 mouse_pos) {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};

    if (type == ListType::Plain) {
        // A teljes (fix magasságú) listaterület számít kattinthatónak.
        int list_height = max_visible_items * size.y;
        return mouse_pos.x > top_left.x && mouse_pos.x < top_left.x + size.x &&
               mouse_pos.y > top_left.y && mouse_pos.y < top_left.y + list_height;
    }

    bool in_main = Widget::UnderMouse(mouse_pos);

    if (opened) {
        int list_start_y = top_left.y + size.y;
        int visible_count = min((int)items.size(), max_visible_items);
        int list_height = visible_count * size.y;

        bool in_list = mouse_pos.x > top_left.x && mouse_pos.x < top_left.x + size.x &&
                       mouse_pos.y > list_start_y && mouse_pos.y < list_start_y + list_height;
        return in_main || in_list;
    }
    return in_main;
}

void List::Draw() {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};
    const int OUTLINE = 2;

    if (type == ListType::Plain) {
        // Fix méretű lista: mindig max_visible_items sor magas, függetlenül attól,
        // hány elem van benne -> a mérete sosem változik.
        int list_height = max_visible_items * size.y;

        // háttér / keret
        gout << color(100, 100, 100)
             << move_to(top_left.x, top_left.y)
             << box(size.x, list_height);

        int visible_count = min((int)items.size(), max_visible_items);

        // látható elemek
        for (int i = 0; i < visible_count; i++) {
            int actual_index = scroll_offset + i;
            int item_y = top_left.y + i * size.y;

            gout << (actual_index == selected_index ? color(150, 200, 255) : color(240, 240, 240));
            gout << move_to(top_left.x + OUTLINE, item_y + OUTLINE)
                 << box(size.x - OUTLINE * 2, size.y - OUTLINE * 2);

            gout << color(0, 0, 0)
                 << move_to(top_left.x + 5, item_y + size.y / 2 - gout.cascent() / 2)
                 << genv::text(items[actual_index]);
        }

        // üres sorok kitöltése, hogy a doboz mindig tele legyen rajzolva
        for (int i = visible_count; i < max_visible_items; i++) {
            int item_y = top_left.y + i * size.y;
            gout << color(texture.r, texture.g, texture.b)
                 << move_to(top_left.x + OUTLINE, item_y + OUTLINE)
                 << box(size.x - OUTLINE * 2, size.y - OUTLINE * 2);
        }
        return;
    }

    // --- Dropdown mód (eredeti viselkedés) ---
    gout << color(100, 100, 100) << move_to(top_left.x, top_left.y) << box(size.x, size.y);
    gout << color(texture.r, texture.g, texture.b)
         << move_to(top_left.x + OUTLINE, top_left.y + OUTLINE)
         << box(size.x - OUTLINE * 2, size.y - OUTLINE * 2);

    string display_text = items.empty() ? "" : items[selected_index];
    gout << color(0, 0, 0)
         << move_to(top_left.x + 5, position.y - gout.cascent() / 2)
         << genv::text(display_text);

    gout << move_to(top_left.x + size.x - 20, position.y - gout.cascent() / 2) << genv::text("V");

    if (opened) {
        int list_start_y = top_left.y + size.y;
        int visible_count = min((int)items.size(), max_visible_items);

        gout << color(100, 100, 100)
             << move_to(top_left.x, list_start_y)
             << box(size.x, visible_count * size.y);

        for (int i = 0; i < visible_count; i++) {
            int actual_index = scroll_offset + i;
            int item_y = list_start_y + i * size.y;

            gout << (actual_index == selected_index ? color(150, 200, 255) : color(240, 240, 240));

            gout << move_to(top_left.x + OUTLINE, item_y + OUTLINE)
                 << box(size.x - OUTLINE * 2, size.y - OUTLINE * 2);

            gout << color(0, 0, 0)
                 << move_to(top_left.x + 5, item_y + size.y / 2 - gout.cascent() / 2)
                 << genv::text(items[actual_index]);
        }
    }
}

void List::Interact(event ev) {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};

    if (type == ListType::Plain) {
        // Kattintás: csak kiválaszt egy elemet, nincs nyitás/csukás.
        if (ev.type == ev_mouse && ev.button == btn_left) {
            int list_height = max_visible_items * size.y;
            bool in_list = ev.pos_x > top_left.x && ev.pos_x < top_left.x + size.x &&
                           ev.pos_y > top_left.y && ev.pos_y < top_left.y + list_height;
            if (in_list) {
                int clicked_relative = (ev.pos_y - top_left.y) / size.y;
                int new_index = scroll_offset + clicked_relative;
                if (new_index >= 0 && new_index < (int)items.size()) {
                    selected_index = new_index;
                }
            }
        }

        // Görgetés
        if (ev.type == ev_mouse && (int)items.size() > max_visible_items) {
            if (ev.button == btn_wheeldown && scroll_offset < (int)items.size() - max_visible_items) {
                scroll_offset++;
            } else if (ev.button == btn_wheelup && scroll_offset > 0) {
                scroll_offset--;
            }
        }
        return;
    }

    // --- Dropdown mód (eredeti viselkedés) ---
    if (ev.type == ev_mouse && ev.button == btn_left) {
        bool in_main = Widget::UnderMouse({ev.pos_x, ev.pos_y});

        if (in_main) {
            opened = !opened;
        }
        else if (opened) {
            int list_start_y = top_left.y + size.y;
            int visible_count = min((int)items.size(), max_visible_items);
            bool in_list = ev.pos_x > top_left.x && ev.pos_x < top_left.x + size.x &&
                           ev.pos_y > list_start_y && ev.pos_y < list_start_y + visible_count * size.y;

            if (in_list) {
                int clicked_relative = (ev.pos_y - list_start_y) / size.y;
                int new_index = scroll_offset + clicked_relative;

                if (new_index != selected_index) {
                    selected_index = new_index;
                }
                opened = false;
            } else {
                opened = false;
            }
        }
    }

    if (ev.type == ev_mouse && opened && items.size() > max_visible_items) {
        if (ev.button == btn_wheeldown && scroll_offset < items.size() - max_visible_items) {
            scroll_offset++;
        } else if (ev.button == btn_wheelup && scroll_offset > 0) {
            scroll_offset--;
        }
    }
}

string List::GetValue() {
    return items[selected_index];
}

void List::RemoveCurrent() {
    if (items.empty()) return;
    items.erase(items.begin() + selected_index);
    selected_index = 0;

    // a görgetés ne mutasson az elemek vége mögé
    int max_scroll = max(0, (int)items.size() - max_visible_items);
    if (scroll_offset > max_scroll) scroll_offset = max_scroll;
}

void List::RemoveAt(int index) {
    if (index >= items.size() || index < 0)
        return;
    items.erase(items.begin() + index);
}

void List::AddItem(string item) {
    items.push_back(item);
}

void List::FocusLost() {
    opened = false;
}