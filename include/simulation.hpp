#ifndef SIMULATION_H
#define SIMULATION_H

class Simulation{
    public:

    static constexpr int WINDOW_WIDTH = 1000;
    static constexpr int WINDOW_HEIGHT = 800;


    Simulation(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT);

    private:

    int m_width;
    int m_height;
    int m_cell_size;
};

#endif 