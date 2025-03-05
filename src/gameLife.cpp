#include "gameLife.hpp"

#include <utility>          // std::move

// Neighbor offsets: dr is delta row, dc is delta column 
// Directions:                            NE, N,  NW,  E,  W, SE,  S, SW
const int GameLife::DR[GameLife::NUM_NEIGHBORS] = {-1, -1 , -1,  0,  0, +1, +1, +1};
const int GameLife::DC[GameLife::NUM_NEIGHBORS] = {-1,  0,  +1, -1, +1, -1,  0, +1};

 
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

    // memory resources for rhs should be freed when the unique_ptr
    // is reassigned. The following should not be necessary since
    // this is an r-value.
    #if 0
    rhs.m_grid = nullptr;
    rhs.m_rows = 0;
    rhs.m_cols = 0;
    #endif
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

int GameLife::countLiveNeighbors(int row, int col)const
{
    int count = 0;
    for(size_t i = 0; i < GameLife::NUM_NEIGHBORS; i++){
        // Calculate neighbor indices so that edge cases wrap-around
        // Ex: Neighbor row North of row 0 is bottom row, i.e. m_rows - 1
        int r = (row + DR[i] + m_rows) % m_rows;
        int c = (col + DC[i] + m_cols) % m_cols;
        if(m_grid[r][c] == ALIVE){
            count++;
        }
    }

    return count;
}

void GameLife::nextGeneration(void)
{
    // create 2d grid to temporarily store next generation
    std::unique_ptr<std::unique_ptr<int[]>[]> next = new2dGrid(m_rows, m_cols);

    for(size_t r = 0; r < m_rows; ++r){
        for(size_t c = 0; c < m_cols; c++){
            int liveCount = countLiveNeighbors(r, c);
            if(m_grid[r][c] == ALIVE){
                // Death by isolation: live cell dies if it has one or fewer live neighbors
                // Death by overcrowding: live cell dies if it has four or more live neighbors
                // Survival: a live cell with one or two neighbors survives to the next generation
                if(liveCount < 2 || liveCount > 3){
                    next[r][c] = DEAD;
                }
                else{
                    next[r][c] = ALIVE;
                }
            }
            else{
                if(liveCount == 3){
                    // Birth: a dead cell becomes alive if it has exactly three live neighbors 
                    next[r][c] = ALIVE;
                }
                else{
                    next[r][c] = DEAD;
                }
            }
        }
    }
    m_grid = std::move(next);    
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
    // create an array of unique_ptr to int arrays (rows)
    std::unique_ptr<std::unique_ptr<int[]>[]> matrix(new std::unique_ptr<int[]>[rows]);
 
    // for each row, create a unique_ptr to an int array (columns)
    for(size_t i = 0; i < rows; ++i){
        matrix[i] = std::make_unique<int[]>(cols);
    }

    return matrix;
}
