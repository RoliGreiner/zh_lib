//
// Created by larix on 2026. 05. 15..
//

#ifndef APP_H
#define APP_H

#include "widget.h"
#include "theme.h"
#include <vector>
#include <iomanip>

class ProgressBar;
class Label;
class Button;
class Widget;
class List;
class TextInput;
class SpinBox;

using namespace std;

struct Grade {
    string student;
    int mark;

    string ToString() {
        ostringstream oss;
        oss << fixed << setprecision(2) << mark;
        int space = 25 - utf8_character_split(student + oss.str()).size();
        return student + string(space, ' ') + oss.str();
    }
};
struct SubjectRecord {
    string name;
    vector<Grade> grades = {};

    float Average() {
        if (grades.empty())
            return 0;

        float sum = 0;
        for (Grade grade : grades) {
            sum += grade.mark;
        }
        return sum / grades.size();
    }
    string ToString() {
        ostringstream oss;
        oss << fixed << setprecision(2) << Average();
        int space = 25 - utf8_character_split(name + (Average() == 0 ? "-" :  oss.str())).size();
        return name + string(space, ' ') + (Average() == 0 ? "-" :  oss.str());
    };
};

class App {
    int width;
    int height;
    int default_font_size;
    Theme theme;
    Vector2 mouse{0, 0};

    vector<Widget*> widgets;

    //widgets
    TextInput* student_name;
    List* default_subjects;
    SpinBox* selected_mark;

    List* noted_marks;
    List* average_per_subject;

    Label* number_of_entry;
    Label* school_average;

    //data holder
    vector<SubjectRecord> subjects = {};

protected:
    void NewEntry();
    void RemoveMark();
    void Update();

public:
    App(int width = 1200, int height = 1000, int font_size = 20, Theme theme = Theme::Dark());
    ~App();

    int Width() const { return width; }
    int Height() const { return height; }
    int FontSize() const { return default_font_size; }

    const Theme& GetTheme() const { return theme; }
    void SetTheme(const Theme& t) { theme = t; }
    Vector2 Mouse() const { return mouse; }

    void RegisterWidget(Widget* w);
    void ClearWindow();
    void Refresh();
    void EventLoop();
    void Start();
};

#endif // APP_H
