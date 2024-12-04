#include "GUI.hpp"
#include "system.hpp"

using namespace task2;

GUI::GUI(System *sys) {
    s = sys;
}

Field::Field(int x, int y, int w, int h, System *sys): Fl_Widget(x, y, w, h, nullptr), s(sys) {}

void Field::draw() {
    fl_color(FL_WHITE);
    fl_rectf(x(), y(), w(), h());
    s->draw();
}

void GUI::start() {
    int win_w = Window_Width;
    int win_h = Window_Height;
    Fl_Window *win = new Fl_Window(win_w, win_h, "Task2");
    field = new Field(x_start, y_start, f_width, f_height, s);
    Fl_Input *inp = new Fl_Input(Inp_spacing, indentation + spacing + button_h, Inp_w, Inp_h, "Steps:");
    Fl_Button *b[buttons];
    int x = spacing;
    for(int i = 0; i < buttons; ++i) {
        b[i] = new Fl_Button(x, indentation, button_w, button_h, msg[i]);
        b[i]->labelsize(font_size);
        x += button_w + spacing;
    }
    controls2 *c;
    c->i = inp;
    c->sys = s;
    c->g = this;
    b[0]->callback(make_steps, (void*)c);
    b[1]->callback(add_particle, (void*)c);
    b[2]->callback(del_particle, (void*)c);
    win->end();
    win->show();
    Fl::run();
}

void GUI::set_callback1(Fl_Widget *widget, void *user) {
    controls *c = (controls *)user;
    if (c->rb[0]->value()) { //SMALL
        c->sys->add_small();
        c->sys->check_collisions();
        c->g->field->redraw();
    }
    else { //BIG
        c->sys->add_big();
        c->sys->check_collisions();
        c->g->field->redraw();
    }
    Fl_Widget *p;
    do {
        p = widget->parent();
        if (p)
            widget = p;
    } while (p);
    widget->hide();
}

void GUI::make_steps(Fl_Widget *widget, void *user) {
    controls2 *c = (controls2 *)user;
    std::string s = c->i->value();
    c->sys->set_steps(stoi(s));
    if (c->sys->get_steps() > 0) 
        Fl::add_timeout(0, sys_step, c);
    ((Fl_Input*)user)->take_focus();
}

void GUI::sys_step(void *p) {
    controls2 *c = (controls2 *)p;
    System* sys = c->sys;
    sys->set_steps(sys->get_steps() - 1);
    sys->make_step();
    GUI *g = c->g;
    g->field->redraw();
    if (sys->get_steps() <= 0) return;
    Fl::repeat_timeout(0.01, sys_step, p);
}

void GUI::add_particle(Fl_Widget *widget, void *user) {
    controls2 *c1 = (controls2 *)user;
    enum l_win {
        w_w = 200,
        w_h = 110
    };
    enum rb {
        rb_spacing = 5,
        rb_w = 55,
        rb_h = 25
    };
    Fl_Window *win = new Fl_Window(w_w, w_h, "Adding");
    controls *c = new controls;
    c->rb[0] = new Fl_Radio_Round_Button(rb_spacing, rb_spacing, rb_w, rb_h, "Small");
    c->rb[1] = new Fl_Radio_Round_Button(rb_spacing, rb_h + 2 * rb_spacing, rb_w, rb_h, "Big");
    c->sys = c1->sys;
    c->g = c1->g;
    Fl_Button *b = new Fl_Button(rb_spacing, 2 * rb_h + 3 * rb_spacing, rb_w * 3, rb_h, "Add");
    b->callback(set_callback1, (void*)c);
    win->end();
    win->show();
}
void GUI::del_particle(Fl_Widget *widget, void *user) {
    controls2 *c = (controls2 *)user;
    c->sys->remove();
    c->g->field->redraw();
}