//
// Created by larix on 2026. 05. 15..
//

#include "app.h"
#include "button.h"
#include "list.h"
#include "label.h"
#include "text_input.h"
#include "spin_box.h"
#include "slider.h"
#include "check_box.h"
#include "progress_bar.h"

#include "graphics.hpp"
#include <iostream>
#include <algorithm>

using namespace genv;
using namespace std;

App::App(int width, int height, int font_size, Theme theme)
    : width(width), height(height), default_font_size(font_size), theme(theme) {
    gout.open(width, height);
    gout << font("LiberationMono-Regular.ttf", font_size);

    vector<string> subject_names = {"Magyar", "Matek", "Történelem", "Fizika", "Informatika"};
    for (string name : subject_names) {
        subjects.push_back({name, {}});
    }

    // widgets
    new Label(
        this,
        {20, 30},
        {0, 0},
        "Tanuló neve",
        14, Label::Align::Left);
    student_name = new TextInput(
        this,
        {170, 60},
        {300, 40},
        "Kovács Péter");
    new Label(
        this,
        {20, 100},
        {0, 0},
        "Tantárgy",
        14, Label::Align::Left);
    default_subjects = new List(
        this,
        {170, 130},
        {300, 40},
        subject_names,
        5, ListType::Plain);
    new Label(
        this,
        {20, 340},
        {0, 0},
        "Jegy:",
        14, Label::Align::Left);
    selected_mark = new SpinBox(
        this,
        {100, 340},
        {60, 40},
        1,
        5,
        1,
        5);
    new Button(
        this,
        {230, 340},
        {180, 40},
        "Bejegyez",
        [this]{NewEntry();});

    new Label(
        this,
        {350, 30},
        {0, 0},
        "Napló (kiválasztott tantárgy)",
        14, Label::Align::Left);
    noted_marks = new List(
        this,
        {500, 60},
        {300, 40},
        {},
        6, ListType::Plain);
    new Button(
        this,
        {500, 310},
        {300, 40},
        "Törlés",
        [this]{RemoveMark();});
    new Label(
        this,
        {350, 350},
        {0, 0},
        "Tantárgyankénti átlagok",
        14, Label::Align::Left);
    average_per_subject = new List(
        this,
        {500, 380},
        {300, 40},
        {},
        5, ListType::Plain);

    new Label(
        this,
        {170, 400},
        {0, 0},
        "Összeg bejegyzés",
        16, Label::Align::Center);
    number_of_entry = new Label(
        this,
        {170, 440},
        {0, 0},
        "",
        32, Label::Align::Center);
    new Label(
        this,
        {170, 500},
        {0, 0},
        "Iskola összesített átlaga",
        16, Label::Align::Center);
    school_average = new Label(
        this,
        {170, 540},
        {0, 0},
        "",
        32, Label::Align::Center);

    Update();

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
    gout << move_to(0, 0)
         << color(theme.window.r, theme.window.g, theme.window.b)
         << box(width, height);
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
        mouse = {ev.pos_x, ev.pos_y};       // track the cursor for hover effects
        ClearWindow();

        // Re-evaluate focus on a left click; notify the widgets that gain/lose it.
        if (ev.type == ev_mouse && ev.button == btn_left) {
            int new_focus = -1;
            for (int i = 0; i < (int)widgets.size(); i++) {
                if (widgets[i]->UnderMouse({ev.pos_x, ev.pos_y})) {
                    new_focus = i;
                    break;
                }
            }
            if (new_focus != focus) {
                if (focus != -1)
                    widgets[focus]->FocusLost();
                if (new_focus != -1)
                    widgets[new_focus]->FocusGained();
                focus = new_focus;
            }
        }

        if (focus != -1) {
            widgets[focus]->Interact(ev);
        }

        Update();
        Refresh();
    }
}

void App::Start() {
    EventLoop();
}

void App::NewEntry() {
    string name = student_name->GetText();
    int subject_index = default_subjects->GetCurrentIndex();
    int mark = selected_mark->GetValue();
    for (Grade grade : subjects[subject_index].grades) {
        if (grade.student == name) {
            return;
        }
    }
    subjects[subject_index].grades.push_back({name, mark});
}

void App::RemoveMark() {
    if (subjects[default_subjects->GetCurrentIndex()].grades.empty())
        return;

    subjects[default_subjects->GetCurrentIndex()].grades.erase(subjects[default_subjects->GetCurrentIndex()].grades.begin() + noted_marks->GetCurrentIndex());
}

void App::Update() {
    ostringstream oss;

    vector<string> temp_record;
    for (Grade grade : subjects[default_subjects->GetCurrentIndex()].grades) {
        temp_record.push_back(grade.ToString());
    }
    noted_marks->OverwriteContent(temp_record);

    vector<string> temp_average = {};
    int sum = 0;
    float average_sum = 0;
    int number_of_graded_subject = 0;
    for (SubjectRecord record : subjects) {
        temp_average.push_back(record.ToString());
        if (!record.grades.empty()) {
            sum += record.grades.size();
            average_sum += record.Average();
            number_of_graded_subject++;
        }
    }
    average_per_subject->OverwriteContent(temp_average);
    number_of_entry->UpdateText(to_string(sum));

    oss << fixed << setprecision(2) << average_sum / number_of_graded_subject;
    school_average->UpdateText((average_sum == 0 ? "-" : oss.str()));
}
