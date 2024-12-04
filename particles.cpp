#include "particles.hpp"
#include <cmath>

void task2::Small_Particle::draw(GUI *g) {
    fl_color(FL_BLUE);
    fl_pie(get_x() - get_R() + x_start, get_y() - get_R() + y_start, get_R() * 2, get_R() * 2, 0, 360);
}

void task2::Big_Particle::draw(GUI *g) {
    fl_color(FL_RED);
    fl_pie(get_x() - get_R() + x_start, get_y() - get_R() + y_start, get_R() * 2, get_R() * 2, 0, 360);
}

void task2::Particle::wall_collision() {
    if (x - R <= x_start) {
        Vx *= -1;
        x = R + x_start;
    }
    if (y - R <= y_start) {
        Vy *= -1;
        y = R + y_start;
    }
    if (x + R >= f_width) {
        Vx *= -1;
        x = f_width - R;
    }
    if (y + R >= f_height) {
        Vy *= -1;
        y = f_height - R;
    }
}

void task2::Particle::set_x(double n) { x = n; }

void task2::Particle::set_y(double n) { y = n; }

void task2::Particle::set_R(double n) { R = n; }

void task2::Particle::set_mass(double n) { mass = n; }


void task2::Particle::set_Vx(double n) { Vx = n; }

void task2::Particle::set_Vy(double n) { Vy = n; }

double task2::Particle::get_x() { return x; }

double task2::Particle::get_y() { return y; }

double task2::Particle::get_Vx() { return Vx; }

double task2::Particle::get_Vy() { return Vy; }

double task2::Particle::get_R() { return R; }

double task2::Particle::get_m() { return mass; }

task2::Small_Particle::Small_Particle(): Particle() {
    set_R(Small_R);
    set_mass(Small_m);
    set_x(abs(rand()) % (f_width - 2 * (int)get_R()) + get_R());
    set_y(abs(rand()) % (f_height - 2 * (int)get_R()) + get_R());
    set_Vx(rand()%50 + 2);
    set_Vy(rand()%50 + 2);
}

task2::Big_Particle::Big_Particle(): Particle() {
    set_R(abs(rand()) % 20 + Small_R + 1);
    set_mass(get_R());
    set_x(abs(rand())%(f_width - 2 * (int)get_R()) + get_R());
    set_y(abs(rand())%(f_height - 2 * (int)get_R()) + get_R());
    set_Vx(rand()%50 + 2);
    set_Vy(rand()%50 + 2);
}

void task2::Small_Particle::move() {
    set_x(get_x() + (int)(get_Vx() * dt));
    set_y(get_y() + (int)(get_Vy() * dt));
}

void task2::Big_Particle::move() {
    set_x(get_x() + (int)(get_Vx() * dt));
    set_y(get_y() + (int)(get_Vy() * dt));
}

void task2::Particle::collision(Particle& p) {
    double vector_x = p.x - x;  
    double vector_y = p.y - y;  
    double dist = sqrt(vector_x * vector_x + vector_y * vector_y);    
    if (dist - R - p.R > 0.05) return;
    double xn = vector_x / dist;  
    double yn = vector_y / dist;  
    x = x - (xn * (R + p.R - dist)) * (mass / (mass + p.mass));  
    y = y - (yn * (R + p.R - dist)) * (mass / (mass + p.mass));   
    p.x = p.x + (xn * (R + p.R - dist)) * (p.mass / (mass + p.mass));
    p.y = p.y + (yn * (R + p.R - dist)) * (p.mass / (mass + p.mass));
    double v1n = Vx * xn + Vy * yn;  
    double v2n = p.Vx * xn + p.Vy * yn;  
    double v1 = (v1n * (mass - p.mass) + 2 * p.mass * v2n) / (mass + p.mass);  
    double v2 = (v2n * (p.mass - mass) + 2 * mass * v1n) / (mass + p.mass);  
    set_Vx(Vx + (v1 - v1n) * xn);  
    set_Vy(Vy + (v1 - v1n) * yn);  
    p.set_Vx(p.Vx + (v2 - v2n) * xn);  
    p.set_Vy(p.Vy + (v2 - v2n) * yn);
    if (R + p.R - dist > 0.5) {
        move();
        move();
    }
    /*x = x - (xn * (R + p.get_R() - dist)) * (mass / (mass + p.get_m()));  
    y = y - (yn * (get_R() + p.get_R() - dist)) * (mass / (mass + p.get_m()));   
    p.x = p.x + (xn * (R + p.R - dist)) * (p.mass / (mass + p.mass));
    p.y = p.y + (yn * (R + p.R - dist)) * (p.mass / (mass + p.mass));*/
}