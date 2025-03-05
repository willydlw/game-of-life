#include "gameLife.hpp"

#include <utility>          // std::move

// Neighbor offsets: dr is delta row, dc is delta column 
// Directions:                            NE, N,  NW,  E,  W, SE,  S, SW
const int DR[GameLife::NUM_NEIGHBORS] = {-1, -1 , -1,  0,  0, +1, +1, +1};
const int DC[GameLife::NUM_NEIGHBORS] = {-1,  0,  +1, -1, +1, -1,  0, +1};

 
// Constructor
GameLife::GameLife(size_t rows, size_t cols) : m_rows(rows), m_cols(cols), m_grid(nullptr) 
{
    std::cerr << __func__ << " default constructor executes\n";
    m_grid = new2dGrid(rows, cols);

}


// move constructor - handles temporary r-values 
// without the overhead of copying temporary data from
// rhs to left and then deallocating rhs memory
GameLife::GameLife(GameLife&& rhs) noexcept
{
    std::cerr << __func__ << " move constructor executes\n";

    // this is a constructor, so no memory has been allocated for
    // this.m_grid 
    m_rows = rhs.m_rows;
    m_cols = rhs.m_cols;
    // want this to point to rhs's dynamically allocated memory
    m_grid = std::move(rhs.m_grid);

    // set rhs to nullptr so that the destructor does free the 
    // memory to which this.m_grid points
    rhs.m_grid = nullptr;
    rhs.m_rows = 0;
    rhs.m_cols = 0;
}

GameLife::~GameLife()
{
    //free2dGrid();
    std::cerr << __func__ << " says bye-bye\n";
}

int GameLife::rows(void) const
{
    return m_rows;
}

int GameLife::cols(void) const
{
    return m_cols;
}


void GameLife::initRandom(int min, int max)
{
    // seed random number generator
    // make it static to ensure it is only seeded once
    static std::mt19937 generator(std::random_device{}());

    std::uniform_int_distribution<int> distrib(min, max);

    for(size_t r = 0; r < m_rows; r++){
        for(size_t c = 0; c < m_cols; c++){
            m_grid[r][c] = distrib(generator);
        }
    }
}

void GameLife::nextGeneration(void)
{
    // create 2d grid to temporarily store next generation
    std::unique_ptr<std::unique_ptr<int[]>[]> next = new2dGrid(m_rows, m_cols);
}

void GameLife::draw(sf::RenderWindow& window, int cellSize, float thickness)
{
    sf::RectangleShape rect(sf::Vector2f(cellSize - thickness, cellSize - thickness));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(thickness);

    for(size_t r = 0; r < m_rows; r++){
        for(size_t c = 0; c < m_cols; c++){
            if(m_grid[r][c] == GameLife::ALIVE){
                int x = c * cellSize;
                int y = r * cellSize;
                rect.setPosition(sf::Vector2f(x,y));
                window.draw(rect);
            }
        }
    }
    
}


std::ostream& operator << (std::ostream& os, const GameLife& obj)
{
    os << "rows: " <<obj.m_rows << ", cols: " << obj.m_cols << "\nGrid Data\n";
    for(size_t r = 0; r < obj.m_rows; r++){
        for(size_t c = 0; c < obj.m_cols; c++){
            os << obj.m_grid[r][c] << " ";
        }
        os << "\n";
    }

    return os;
}


// move assignment 
// assigns r-value data to left-side without copying overhead
GameLife& GameLife::operator = (GameLife&& rhs) noexcept
{
    std::cerr << __func__ << " move assignment operator= executing\n";
    if(this != &rhs)
    {
        // this is a constructor, so no memory has been allocated for
        // this.m_grid 
        m_rows = rhs.m_rows;
        m_cols = rhs.m_cols;

        // want this to point to rhs's dynamically allocated memory
        m_grid = std::move(rhs.m_grid);
    }

    return *this;
}



std::unique_ptr<std::unique_ptr<int[]>[]> GameLife::new2dGrid(size_t rows, size_t cols)
{
    std::cerr << __func__ << " ready to allocate grid memory\n";
    std::cerr << "parameters are rows: " << rows << ", cols: " << cols << "\n";

    // create an array of unique_ptr to int arrays (rows)
    std::unique_ptr<std::unique_ptr<int[]>[]> matrix(new std::unique_ptr<int[]>[rows]);
 
    // for each row, create a unique_ptr to an int array (columns)
    for(size_t i = 0; i < rows; ++i){
        matrix[i] = std::make_unique<int[]>(cols);
    }

    return matrix;
}
