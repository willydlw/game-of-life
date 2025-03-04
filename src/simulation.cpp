#include "simulation.hpp"


Simulation::Simulation(SimConfig sc) : 
        m_window_width(sc.window_width), 
        m_window_height(sc.window_height),
        m_grid_rows(sc.grid_rows),
        m_grid_cols(sc.grid_cols),
        m_cell_size(sc.cell_size),
        m_game(sc.grid_rows, sc.grid_cols)
{
    init();
}

void Simulation::init(void)
{
    m_window.create(sf::VideoMode({m_window_width, m_window_height}), "Game of Life Simulation"); 
    
    if(!m_font.openFromFile("build/bin/assets/arial.ttf"))
    {
        std::cerr << "[FATAL] " << __func__ << ", failed to open font file arial.ttf\n";
        exit(EXIT_FAILURE);
    }
}

Simulation::~Simulation()
{
    std::cerr << "bye bye from ~Simulation()\n";
}


void Simulation::run(void)
{
    
}