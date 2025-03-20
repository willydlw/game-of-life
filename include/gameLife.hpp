#ifndef GAMELIFE_H
#define GAMELIFE_H

#include <SFML/Graphics.hpp>

#include <iostream>

struct Cell{
    int state;
    int row;
    int col;
};

class GameLife{
    public:

    // Cell State Constants
    static constexpr int DEAD = 0;
    static constexpr int ALIVE = 1;
    
    // Neighbor Constants 
    static constexpr int NUM_NEIGHBORS = 8;

    // Neighbor row, column offsets: dr is delta row, dc is delta column 
    static const int DR[]; 
    static const int DC[];


    // Constructor
    GameLife(size_t rows = 0, size_t cols = 0);

    // prevent copy construction
    GameLife(const GameLife& rhs) = default;

    // move constructor - used to assign temporary r-values 
     // use noexcept because move assignment not allowed to throw an exception
    GameLife(GameLife&& rhs) = default;

    ~GameLife() = default;
   

    // accessor functions
    int rows(void) const;
    int cols(void) const;

    void initializeGrid(std::vector<Cell> aliveLocations);



    void nextGeneration(void); 

    // render the grid
    void draw(sf::RenderWindow& window, int cellSize, float thickness);
    
    // overloaded operators 
    friend std::ostream& operator << (std::ostream& os, const GameLife& obj);

    // copy assignment
    GameLife& operator = (const GameLife& rhs) = default;

    // move assignment
    // use noexcept because move assignment not allowed to throw an exception
    GameLife& operator = (GameLife&& rhs) = default;

    private:

    size_t m_rows;
    size_t m_cols;

    // dynamically allocated 2d integer array
    std::vector<int> m_grid;

    // Private helper functions
    
    int calcIndex(int row, int col) const;
    int countLiveNeighbors(int row, int col)const;
};



#endif 