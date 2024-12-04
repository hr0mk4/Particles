#ifndef GUI_H
#define GUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <FL/fl_draw.H>
#include "system.hpp"

namespace task2 {
    class System;
    class GUI;
    struct controls {
        Fl_Radio_Round_Button *rb[2];
        System *sys;
        GUI *g;
    };

    struct controls2 {
        Fl_Input *i;
        System *sys;
        GUI *g;
    };
    class Field : public Fl_Widget {
        System *s;
    public:
        Field(int x, int y, int w, int h, System *sys);
        void draw();
    };
    class GUI {
    task2::System *s;
    Field *field;
    public:
        GUI(task2::System *sys);
        void start();
        static void make_steps(Fl_Widget *widget, void *user);
        static void add_particle(Fl_Widget *widget, void *user);
        static void del_particle(Fl_Widget *widget, void *user);
        static void set_callback1(Fl_Widget *widget, void *user);
        //static void set_callback2(Fl_Widget *widget, void *user);
        static void sys_step(void *p);
    };
}

#endif