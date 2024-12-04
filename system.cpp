#include "system.hpp"
#include "particles.hpp"
#include <cstdlib>
#include <cstdlib>

using namespace task2;

System::System(int seed, int small_ps, int big_ps) {
    srand(seed);
    for (int i = 0; i < small_ps; i++) 
        particles.push_back(new Small_Particle());
    for (int i = 0; i < big_ps; i++)   
        particles.push_back(new Big_Particle());
    check_collisions();
    fflush(stdout);
}

void System::start() {
    gui = new GUI(this);
    gui->start();
}

void System::set_steps(int steps) { this->steps = steps; }

int System::get_steps() { return steps; }

void System::add_small() {
    particles.push_back(new Small_Particle());
}

void System::add_big() {
    particles.push_back(new Big_Particle());
}

void System::remove() 
{
    if (particles.size() > 0) 
    {
        delete particles[particles.size() - 1];
        particles.pop_back();
    }
}

void System::draw() {
    for(auto p : particles) {
        p->draw(gui);
    }
}

void System::make_step() {
    for(auto p : particles)
        p->move();
    check_collisions();
}

void System::check_collisions() {
    for(int i = 0; i < particles.size(); ++i) {
        particles[i]->wall_collision();
        for(int j = i + 1; j < particles.size(); ++j)
            particles[i]->collision(*particles[j]);
    }
}