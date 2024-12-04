#ifndef PARTICLES_H
#define PARTICLES_H

#include "GUI.hpp"
#include "system.hpp"

namespace task2 {
    enum {
        Small_R = 8,
        Small_m = 8
    };
    class GUI;
    const static double dt = 0.1;
    class Particle {
        double Vx, Vy, x, y, R, mass;
    public:
        virtual void move() = 0;
        void collision(Particle& p);
        void wall_collision();
        //bool too_close(Particle& other);
        virtual void draw(GUI *g) = 0;
        virtual ~Particle() = default;
        double get_x();
        double get_y();
        double get_Vx();
        double get_Vy();
        double get_R();
        double get_m();
        void set_x(double n);
        void set_y(double n);
        void set_Vx(double n);
        void set_Vy(double n);
        void set_R(double n);
        void set_mass(double n);
    };

    class Small_Particle : public Particle {
    public:
        Small_Particle();
        virtual void draw(GUI *g);
        void move() override;
    };

    class Big_Particle : public Particle {
    public:
        Big_Particle();
        virtual void draw(GUI *g);
        void move() override;
    };
}

#endif