#include "gameLife.hpp"

// Neighbor offsets: dr is delta row, dc is delta column 
// Directions:                            NE, N,  NW,  E,  W, SE,  S, SW
const int GameLife::DR[GameLife::NUM_NEIGHBORS] = {-1, -1 , -1,  0,  0, +1, +1, +1};
const int GameLife::DC[GameLife::NUM_NEIGHBORS] = {-1,  0,  +1, -1, +1, -1,  0, +1};



// Constructor
GameLife::GameLife(size_t rows, size_t cols) : m_rows(rows), m_cols(cols), m_grid(rows*cols, 0)
{
    std::cerr << __func__ << " constructor executes, rows: " << rows 
            << ", cols: " << cols << ", m_grid.size(): " << m_grid.size() << "\n";
}


int GameLife::rows(void) const
{
    return m_rows;
}

int GameLife::cols(void) const
{
    return m_cols;
}

void GameLife::initializeGrid(std::vector<Cell> aliveLocations)
{
    m_grid.clear();
    m_grid.resize(m_rows * m_cols);
    
    for(auto cell : aliveLocations ){
        m_grid[calcIndex(cell.row, cell.col)] = cell.state;
    }
}



#if 0
void GameLife::initPattern(PatternName patternName, int numInstances)
{
    size_t r = 
    // treat pattern as 3x3 rectangle
    for(size_t i = 0; i < 3; i++){
        for(size_t j = 0; j < 3; j++){

        }
    }

}
#endif 

int GameLife::countLiveNeighbors(int row, int col)const
{
    int count = 0;
    for(size_t i = 0; i < GameLife::NUM_NEIGHBORS; i++){
        int r = row + DR[i];
        int c = col + DC[i];
        if(r < 0 || r >= static_cast<int>(m_rows) || c < 0 || c >= static_cast<int>(m_cols)){
            continue;
        }

        if(m_grid[calcIndex(r,c)] == ALIVE){
            count++;
        }
    }

    return count;
}

void GameLife::nextGeneration(void)
{
    // create 2d grid to temporarily store next generation
    std::vector<int> next(m_rows * m_cols, 0);
   
    for(size_t r = 0; r < m_rows; ++r){
        for(size_t c = 0; c < m_cols; c++){
            int liveCount = countLiveNeighbors(r, c);
            int index = calcIndex(r,c);
            if(m_grid[index] == ALIVE){
                // Death by isolation: live cell dies if it has one or fewer live neighbors
                // Death by overcrowding: live cell dies if it has four or more live neighbors
                // Survival: a live cell with one or two neighbors survives to the next generation
                if(liveCount < 2 || liveCount > 3){
                    next[index] = DEAD;
                }
                else{
                    next[index] = ALIVE;
                }
            }
            else{
                if(liveCount == 3){
                    // Birth: a dead cell becomes alive if it has exactly three live neighbors 
                    next[index] = ALIVE;
                }
                else{
                    next[index] = DEAD;
                }
            }
        }
    }

    m_grid = next; 
}

void GameLife::draw(sf::RenderWindow& window, int cellSize, float thickness)
{
    sf::RectangleShape rect(sf::Vector2f(cellSize - thickness, cellSize - thickness));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOutlineThickness(thickness);

    for(size_t r = 0; r < m_rows; r++){
        for(size_t c = 0; c < m_cols; c++){
            if(m_grid[calcIndex(r,c)] == GameLife::ALIVE){
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
            os << obj.m_grid[obj.calcIndex(r,c)] << " ";
        }
        os << "\n";
    }

    return os;
}


int GameLife::calcIndex(int row, int col) const
{
    return row * m_cols + col;
}
