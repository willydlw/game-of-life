#ifndef GAMELIFE_H
#define GAMELIFE_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include <random>

class GameLife{
    public:

    static constexpr int DEAD = 0;
    static constexpr int ALIVE = 1;
    

    static constexpr int NUM_NEIGHBORS = 8;

    // Neighbor row, column offsets: dr is delta row, dc is delta column 
    static const int DR[NUM_NEIGHBORS]; 
    static const int DC[NUM_NEIGHBORS];

    GameLife(size_t rows = 0, size_t cols = 0);


    // prevent copy construction
    GameLife(const GameLife& rhs) = delete;

    // move constructor - used to assign temporary r-values 
     // use noexcept because move assignment not allowed to throw an exception
    GameLife(GameLife&& rhs) noexcept;

    //~GameLife() = default;
    ~GameLife();

    // accessor functions
    int rows(void) const;
    int cols(void) const;

    // initial patterns
    void initRandom(int min = DEAD, int max = ALIVE);  

    void nextGeneration(void); 

    // render the grid
    void draw(sf::RenderWindow& window, int cellSize, float thickness);
    
    // overloaded operators 
    friend std::ostream& operator << (std::ostream& os, const GameLife& obj);

    // prevent copy assignment
    GameLife& operator = (const GameLife& rhs) = delete;

    // move assignment
    // use noexcept because move assignment not allowed to throw an exception
    GameLife& operator = (GameLife&& rhs) noexcept;

    private:

    size_t m_rows;
    size_t m_cols;

    // dynamically allocated 2d integer array
    std::unique_ptr<std::unique_ptr<int[]>[]> m_grid;

    std::unique_ptr<std::unique_ptr<int[]>[]> new2dGrid(size_t rows, size_t cols);
};



#endif 