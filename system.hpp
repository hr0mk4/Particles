#ifndef SYSTEM_H
#define SYSTEM_H

#include "particles.hpp"
#include "GUI.hpp"

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <iostream>
#include <string>

#define Window_Width 600
#define Window_Height 480


class Particle;

namespace task2 {
    enum Field_Size {
        x_start = 15,
        y_start = 5, 
        f_width = 570,
        f_height = 380
    };

    enum Inp {
        Inp_w = 50,
        Inp_h = 30,
        Inp_spacing = 50
    };

    enum Buttons {
        buttons = 3,
        spacing = 15,
        button_w = 130,
        button_h = 40,
        font_size = 50,
        indentation = 390
    };

    static const char *msg[] = {"Make moves", "Add a particle", "Delete the particle"};

    enum type {
        Small,
        Big
    };
    class GUI;

    class System {
        std::vector<Particle *> particles;
        GUI *gui;
        int steps;
    public:
        System(int seed, int small_ps, int big_ps);
        void start();
        void add_small();
        void add_big();
        void remove();
        int get_steps();
        void set_steps(int steps);
        void make_step();
        void draw();
        void check_collisions();
    };
}

#endif