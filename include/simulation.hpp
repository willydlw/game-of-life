#ifndef SIMULATION_H
#define SIMULATION_H

#include "gameLife.hpp"
#include "patterns.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

struct SimConfig{

    // Default Constants 
    static constexpr unsigned int WINDOW_WIDTH = 1000;
    static constexpr unsigned int WINDOW_HEIGHT = 800;
    static constexpr int GRID_ROWS = 10;
    static constexpr int GRID_COLS = 10;
    static constexpr int CELL_SIZE = 40;
    static constexpr int FRAMERATE = 5;
    static constexpr Pattern::PatternId DEFAULT_PATTERN = Pattern::RANDOM;

    unsigned int window_width;
    unsigned int window_height;
    int grid_rows;
    int grid_cols;
    int cell_size;
    int framerate;
    Pattern::PatternId pid;

    SimConfig(int width = WINDOW_WIDTH, 
                int height = WINDOW_HEIGHT,
                int rows = GRID_ROWS,
                int cols = GRID_COLS,
                int csize = CELL_SIZE,
                int frate = FRAMERATE,
                Pattern::PatternId pid = DEFAULT_PATTERN
            ) : window_width(width),
                window_height(height),
                grid_rows(rows),
                grid_cols(cols),
                cell_size(csize),
                framerate(frate),
                pid(pid)
    {}

};



class Simulation{

    private:

    static const char* GENERATION_MSG;
    public:

    // Constructor
    Simulation(SimConfig& sc);

    // Destructor
    ~Simulation();

    void init(SimConfig& sc);

    void initPattern(std::vector<Cell>& cells, Pattern::PatternId pid = Pattern::RANDOM);

    //void createPattern(PatternName patternName, int numInstances)
    
    void run(void);

    private:

    // Simulation Data Members
    unsigned int m_window_width;
    unsigned int m_window_height;
    int m_cell_size;

    GameLife m_game;

    // SFML 
    sf::RenderWindow m_window;
    sf::Font m_font;
   

    private:        // helper functions

    // initial patterns
    void initRandom(std::vector<Cell>& cells, int min, int max);      
};

#endif 