#ifndef GAMELIFE_H
#define GAMELIFE_H

#include <SFML/Graphics.hpp>

#include <random>

class GameLife{
    public:

    // Random number generator

    static std::mt19937 random_engine;

    static constexpr unsigned int DEAD = 0x0;
    static constexpr unsigned int ALIVE = 0x1;
    

    static constexpr int NUM_NEIGHBORS = 8;

    // Neighbor row, column offsets: dr is delta row, dc is delta column 
    static const int DR[NUM_NEIGHBORS]; 
    static const int DC[NUM_NEIGHBORS];

    GameLife(int rows = 0, int cols = 0);

    ~GameLife();

    void initRandom(int min, int max);
    

    private:

    int m_rows;
    int m_cols;
    int m_cell_size;

    sf::RenderWindow m_window;

};



#endif 