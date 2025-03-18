#ifndef SIMULATION_H
#define SIMULATION_H

#include "gameLife.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

struct SimConfig{

    // Default Constants 
    static constexpr int WINDOW_WIDTH = 1000;
    static constexpr int WINDOW_HEIGHT = 800;
    static constexpr int GRID_ROWS = 10;
    static constexpr int GRID_COLS = 10;
    static constexpr int CELL_SIZE = 40;
    static constexpr int FRAMERATE = 5;

    unsigned int window_width;
    unsigned int window_height;
    int grid_rows;
    int grid_cols;
    int cell_size;
    int framerate;

    SimConfig(int width = WINDOW_WIDTH, 
                int height = WINDOW_HEIGHT,
                int rows = GRID_ROWS,
                int cols = GRID_COLS,
                int csize = CELL_SIZE,
                int frate = FRAMERATE
            ) : window_width(width),
                window_height(height),
                grid_rows(rows),
                grid_cols(cols),
                cell_size(csize),
                framerate(frate)
    {}

};



class Simulation{
    public:

    // Initialization Patterns
    static const int R_PENTOMINO[3][3];

    enum PatternName{
        RPENTO,
        GLIDER,
        RANDOM
    };


    public:

    // Constructor
    Simulation(SimConfig sc);

    // Destructor
    ~Simulation();

    void init(int framerate);

    void createPattern(PatternName patterName, int numInstances);
    

    void run(void);

    private:

    // Simulation Data Members
    unsigned int m_window_width;
    unsigned int m_window_height;
    int m_cell_size;

    GameLife m_game;

    sf::RenderWindow m_window;
    sf::Font m_font;
};

#endif 