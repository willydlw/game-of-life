#include "patterns.hpp"

namespace GlobalConstants{

// Initial Patterns 
const int R_PENTOMINO[3][3] = 
    {
        {0, 1, 0}, 
        {1, 1, 0}, 
        {0, 1, 0}
    };


/***   Still Life Patterns    ***/
const int BLOCK[4][4] =
{
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};

const int BEEHIVE[5][6] = 
{
    {0,0,0,0,0,0},
    {0,0,1,1,0,0},
    {0,1,0,0,1,0},
    {0,0,1,1,0,0},
    {0,0,0,0,0,0}
};


/****** Oscillation Patterns  ******/

const int BLINKER[5][5] = 
{
    {0,0,0,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,0,0,0}
};

const int TOAD[6][6] = 
{
    {0,0,0,0,0,0},
    {0,0,0,1,0,0},
    {0,1,0,0,1,0},
    {0,1,0,0,1,0},
    {0,0,1,0,0,0},
    {0,0,0,0,0,0}
};

const int BEACON[4][4] = 
{
    {1,1,0,0},
    {1,1,0,0},
    {0,0,1,1},
    {0,0,1,1}
};




} // end namespace
