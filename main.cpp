#include "system.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    int seed = atoi(argv[1]);
    int small_ps = atoi(argv[2]);
    int big_ps = atoi(argv[3]);
    task2::System sys(seed, small_ps, big_ps); 
    sys.start();
    return 0;
}