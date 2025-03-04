#ifndef GAMELIFE_H
#define GAMELIFE_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>

class GameLife{
    public:

    static constexpr int DEAD = 0;
    static constexpr int ALIVE = 1;
    

    static constexpr int NUM_NEIGHBORS = 8;

    // Neighbor row, column offsets: dr is delta row, dc is delta column 
    static const int DR[NUM_NEIGHBORS]; 
    static const int DC[NUM_NEIGHBORS];

    GameLife(int rows = 0, int cols = 0);

    // copy constructor supports following operations:
    //  GameLife f(g);       where g is a GameLife object
    //  GameLife f = g;      where g is a GameLife object
    GameLife(const GameLife& rhs);

    // move constructor - used to assign temporary r-values 
     // use noexcept because move assignment not allowed to throw an exception
    GameLife(GameLife&& rhs) noexcept;

    ~GameLife();

    // accessor functions
    int rows(void) const;
    int cols(void) const;

    void initRandom(int min = DEAD, int max = ALIVE);   
    
    // overloaded operators 
    friend std::ostream& operator << (std::ostream& os, const GameLife& obj);

    // copy assignment
    GameLife& operator = (const GameLife& rhs);

    // move assignment
    // use noexcept because move assignment not allowed to throw an exception
    GameLife& operator = (GameLife&& rhs) noexcept;

    private:

    int m_rows;
    int m_cols;

    int** m_grid;

    void new2dGrid(int rows, int cols);
    void free2dGrid(void);
};



#endif 