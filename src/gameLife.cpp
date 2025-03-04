#include "gameLife.hpp"

    // Neighbor offsets: dr is delta row, dc is delta column 
    // Directions:                            NE, N,  NW,  E,  W, SE,  S, SW
    const int DR[GameLife::NUM_NEIGHBORS] = {-1, -1 , -1,  0,  0, +1, +1, +1};
    const int DC[GameLife::NUM_NEIGHBORS] = {-1,  0,  +1, -1, +1, -1,  0, +1};

 


GameLife::GameLife(int rows, int cols) : m_rows(rows), m_cols(cols), m_grid(nullptr) 
{
    std::cerr << __func__ << " default constructor executes\n";
}

// Copy constructor
GameLife::GameLife(const GameLife& rhs)
{
    std::cerr << __func__ << " copy constructor executes\n";
    // constructor, so no memory has been allocated for m_grid
    m_rows = rhs.m_rows;
    m_cols = rhs.m_cols;
    new2dGrid(m_rows, m_cols);

    // copy contents of rhs into m_grid
    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            m_grid[r][c] = rhs.m_grid[r][c];
        }
    }
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
    m_grid = rhs.m_grid;

    // set rhs to nullptr so that the destructor does free the 
    // memory to which this.m_grid points
    rhs.m_grid = nullptr;
    rhs.m_rows = 0;
    rhs.m_cols = 0;
}

GameLife::~GameLife()
{
    free2dGrid();
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

    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            m_grid[r][c] = distrib(generator);
        }
    }
}


std::ostream& operator << (std::ostream& os, const GameLife& obj)
{
    os << "rows: " <<obj.m_rows << ", cols: " << obj.m_cols << "\nGrid Data\n";
    for(int r = 0; r < obj.m_rows; r++){
        for(int c = 0; c < obj.m_cols; c++){
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
        free2dGrid();

        // this is a constructor, so no memory has been allocated for
        // this.m_grid 
        m_rows = rhs.m_rows;
        m_cols = rhs.m_cols;
        // want this to point to rhs's dynamically allocated memory
        m_grid = rhs.m_grid;

        // set rhs to nullptr so that the destructor does free the 
        // memory to which this.m_grid points
        rhs.m_grid = nullptr;
        rhs.m_rows = 0;
        rhs.m_cols = 0;
    }

    return *this;
}

// copy assignment
GameLife& GameLife::operator = (const GameLife& rhs)
{
    std::cerr << __func__ << " assignment operator executes\n";

    // check for self-assignment 
    if(this == &rhs){
        return *this;
    }

    // the 2d arrays may not be the same size
    // we could check that, but I am choosing to free 
    // the existing memory and re-allocate without checking
    free2dGrid();
    new2dGrid(rhs.m_rows, rhs.m_cols);

    // copy contents of rhs grid 
    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            m_grid[r][c] = rhs.m_grid[r][c];
        }
    }

    return *this;
}


void GameLife::new2dGrid(int rows, int cols)
{
    if(m_grid != nullptr){
        free2dGrid();
    }

    // dynamically allocate 2d array
    if(rows > 0 && cols > 0){
        m_grid = new int*[rows];

        for(int r = 0; r < rows; r++){
            m_grid[r] = new int[cols];
        }
    }

    m_rows = rows;
    m_cols = cols;
}

void GameLife::free2dGrid(void)
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
        m_grid = nullptr;
    }

}