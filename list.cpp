//
// Created by larix on 2026. 04. 30..
//

#include "list.h"
#include <algorithm>

List::List(App* app, Vector2 position, Vector2 size, vector<string> items, int max_visible_items, ListType type, Color color_override)
    : Widget(app, position, size, color_override) {
    this->items = items;
    this->max_visible_items = max_visible_items;
    this->type = type;
    selected_index = 0;
    scroll_offset = 0;
    opened = false;
}

bool List::UnderMouse(Vector2 mouse_pos) {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};

    if (type == ListType::Plain) {
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
    int R = Radius();
    int ir = R - OUTLINE;

    Color surface = Resolve(GetTheme().surface);
    Color rowsel = GetTheme().selection;
    Color empty_row = GetTheme().surface_alt;
    Color grid = GetTheme().border;
    Color tc = GetTheme().text;
    Vector2 m = MousePos();

    if (type == ListType::Plain) {
        int list_height = max_visible_items * size.y;

        // háttér / rács (lekerekített külső)
        FillRoundedBox(top_left.x, top_left.y, size.x, list_height, R, grid);

        int visible_count = min((int)items.size(), max_visible_items);

        for (int i = 0; i < max_visible_items; i++) {
            int item_y = top_left.y + i * size.y;
            bool top = (i == 0);
            bool bot = (i == max_visible_items - 1);

            Color row;
            bool has_item = i < visible_count;
            if (has_item) {
                int actual_index = scroll_offset + i;
                bool hov = m.x > top_left.x && m.x < top_left.x + size.x &&
                           m.y > item_y && m.y < item_y + size.y;
                row = (actual_index == selected_index) ? rowsel
                     : (hov ? Mix(surface, GetTheme().accent, 0.18f) : surface);
            } else {
                row = empty_row;
            }

            FillRoundedBoxEx(top_left.x + OUTLINE, item_y + OUTLINE,
                             size.x - OUTLINE * 2, size.y - OUTLINE * 2, ir,
                             top, top, bot, bot, row);

            if (has_item) {
                gout << color(tc.r, tc.g, tc.b)
                     << move_to(top_left.x + 6, item_y + size.y / 2 - gout.cascent() / 2)
                     << genv::text(items[scroll_offset + i]);
            }
        }
        return;
    }

    // --- Dropdown ---
    // Ha nyitva van, a sáv alja egyenes (a lenyíló panelhez illeszkedik).
    bool op = opened;
    FillRoundedBoxEx(top_left.x, top_left.y, size.x, size.y, R,
                     true, true, !op, !op, grid);
    FillRoundedBoxEx(top_left.x + OUTLINE, top_left.y + OUTLINE,
                     size.x - OUTLINE * 2, size.y - OUTLINE * 2, ir,
                     true, true, !op, !op, surface);

    string display_text = items.empty() ? "" : items[selected_index];
    gout << color(tc.r, tc.g, tc.b)
         << move_to(top_left.x + 6, position.y - gout.cascent() / 2)
         << genv::text(display_text);

    Color arrow = GetTheme().text_muted;
    gout << color(arrow.r, arrow.g, arrow.b)
         << move_to(top_left.x + size.x - 18, position.y - gout.cascent() / 2)
         << genv::text(op ? "^" : "v");

    if (op) {
        int list_start_y = top_left.y + size.y;
        int visible_count = min((int)items.size(), max_visible_items);

        // panel: teteje egyenes, alja lekerekített
        FillRoundedBoxEx(top_left.x, list_start_y, size.x, visible_count * size.y, R,
                         false, false, true, true, grid);

        for (int i = 0; i < visible_count; i++) {
            int actual_index = scroll_offset + i;
            int item_y = list_start_y + i * size.y;
            bool bot = (i == visible_count - 1);

            bool hov = m.x > top_left.x && m.x < top_left.x + size.x &&
                       m.y > item_y && m.y < item_y + size.y;
            Color row = (actual_index == selected_index) ? rowsel
                       : (hov ? Mix(surface, GetTheme().accent, 0.18f) : surface);

            FillRoundedBoxEx(top_left.x + OUTLINE, item_y + OUTLINE,
                             size.x - OUTLINE * 2, size.y - OUTLINE * 2, ir,
                             false, false, bot, bot, row);

            gout << color(tc.r, tc.g, tc.b)
                 << move_to(top_left.x + 6, item_y + size.y / 2 - gout.cascent() / 2)
                 << genv::text(items[actual_index]);
        }
    }
}

void List::Interact(event ev) {
    Vector2 top_left = {position.x - size.x / 2, position.y - size.y / 2};

    if (type == ListType::Plain) {
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

        if (ev.type == ev_mouse && (int)items.size() > max_visible_items) {
            if (ev.button == btn_wheeldown && scroll_offset < (int)items.size() - max_visible_items) {
                scroll_offset++;
            } else if (ev.button == btn_wheelup && scroll_offset > 0) {
                scroll_offset--;
            }
        }
        return;
    }

    // --- Dropdown ---
    if (ev.type == ev_mouse && ev.button == btn_left) {
        bool in_main = Widget::UnderMouse({ev.pos_x, ev.pos_y});

        if (in_main) {
            opened = !opened;
        } else if (opened) {
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

    if (ev.type == ev_mouse && opened && (int)items.size() > max_visible_items) {
        if (ev.button == btn_wheeldown && scroll_offset < (int)items.size() - max_visible_items) {
            scroll_offset++;
        } else if (ev.button == btn_wheelup && scroll_offset > 0) {
            scroll_offset--;
        }
    }
}

string List::GetValue() { return items[selected_index]; }

void List::RemoveCurrent() {
    if (items.empty()) return;
    items.erase(items.begin() + selected_index);
    selected_index = 0;

    int max_scroll = max(0, (int)items.size() - max_visible_items);
    if (scroll_offset > max_scroll) scroll_offset = max_scroll;
}

void List::RemoveAt(int index) {
    if (index >= (int)items.size() || index < 0) return;
    items.erase(items.begin() + index);
}

void List::AddItem(string item) { items.push_back(item); }

void List::FocusLost() {
    Widget::FocusLost();
    opened = false;
}

void List::OverwriteContent(vector<string> items) {
    this->items = items;
    int n = (int)this->items.size();

    if (selected_index >= n)
        selected_index = n > 0 ? n - 1 : 0;

    int max_scroll = n - max_visible_items;
    if (max_scroll < 0)
        max_scroll = 0;
    if (scroll_offset > max_scroll)
        scroll_offset = max_scroll;
}
