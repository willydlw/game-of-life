#include "gameLife.hpp"

    // Neighbor offsets: dr is delta row, dc is delta column 
    // Directions:                            NE, N,  NW,  E,  W, SE,  S, SW
    const int DR[GameLife::NUM_NEIGHBORS] = {-1, -1 , -1,  0,  0, +1, +1, +1};
    const int DC[GameLife::NUM_NEIGHBORS] = {-1,  0,  +1, -1, +1, -1,  0, +1};


    static std::mt19937 random_engine(std::random_device{}());


GameLife::GameLife(int rows, int cols) : m_rows(rows), m_cols(cols) {}

GameLife::~GameLife()
{
    m_window.close();
}


void GameLife::initRandom(int min, int max)
{
    std::uniform_int_distribution<int> distrib(min, max);
}