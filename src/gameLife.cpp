#include "gameLife.hpp"

    // Neighbor offsets: dr is delta row, dc is delta column 
    // Directions:                            NE, N,  NW,  E,  W, SE,  S, SW
    const int DR[GameLife::NUM_NEIGHBORS] = {-1, -1 , -1,  0,  0, +1, +1, +1};
    const int DC[GameLife::NUM_NEIGHBORS] = {-1,  0,  +1, -1, +1, -1,  0, +1};


    static std::mt19937 random_engine(std::random_device{}());


GameLife::GameLife(int rows, int cols) : m_rows(rows), m_cols(cols), m_grid(nullptr) {}

GameLife::~GameLife()
{
    if(m_grid != nullptr)
    {
        // free column memory allocated for each row
        for(int r = 0; r < m_rows; r++){
            if(m_grid[r]){
                delete[] m_grid[r];
            }
        }

        // free memory allocated for array of row pointers
        delete[] m_grid;

        // not necessary to set m_grid to nullptr as this object is being destroyed
    }
}


void GameLife::initRandom(void)
{
    std::uniform_int_distribution<int> distrib(DEAD, ALIVE);
}