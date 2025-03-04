#include "simulation.hpp"


int main(void)
{
    SimConfig sc;
    Simulation sim(sc);
    sim.run();
    return 0;
}