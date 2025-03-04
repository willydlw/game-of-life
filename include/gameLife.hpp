#ifndef GAMELIFE_H
#define GAMELIFE_H

#include <SFML/Graphics.hpp>

#include <random>

class GameLife{
    public:

    // Random number generator

    static std::mt19937 random_engine;

    static constexpr int DEAD = 0;
    static constexpr int ALIVE = 1;
    

    static constexpr int NUM_NEIGHBORS = 8;

    // Neighbor row, column offsets: dr is delta row, dc is delta column 
    static const int DR[NUM_NEIGHBORS]; 
    static const int DC[NUM_NEIGHBORS];

    GameLife(int rows = 0, int cols = 0);

    ~GameLife();

    void initRandom(void);    

    private:

    int m_rows;
    int m_cols;

    int** m_grid;
};



#endif 