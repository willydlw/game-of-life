#include "patterns.hpp"

namespace Pattern{
    
    const char* patternNames[] = {
        "Block", "Beehive", "Loaf", "Boat", "Tub", 
        "Blinker", "Toad", nullptr};

// Initial Patterns 
const int R_PENTOMINO[3][3] = 
    {
        {0, 1, 0}, 
        {1, 1, 0}, 
        {0, 1, 0}
    };


    const PatternInfo patterns[NUM_PATTERNS] = 
    {
        {.id = BLOCK, .rows = 3, .cols = 3, .data = 
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        }, 

        {.id = BEEHIVE, .rows = 5, .cols = 6, .data = 
            {
                {0,0,0,0,0,0},
                {0,0,1,1,0,0},
                {0,1,0,0,1,0},
                {0,0,1,1,0,0},
                {0,0,0,0,0,0}
            }
        },

        {
            .id = LOAF, .rows = 6, .cols = 6, .data = 
            {
                {0,0,0,0,0,0},
                {0,0,1,1,0,0},
                {0,1,0,0,1,0},
                {0,0,1,0,1,0},
                {0,0,0,1,0,0},
                {0,0,0,0,0,0}
            }
        },

        {
            .id = BOAT, .rows = 5, .cols = 5, .data = 
            {
                {0,0,0,0,0},
                {0,1,1,0,0},
                {0,1,0,1,0},
                {0,0,1,0,0},
                {0,0,0,0,0}
            }
        },

        {
            .id = TUB, .rows = 5, .cols = 5, .data = 
            {
                {0,0,0,0,0},
                {0,0,1,0,0},
                {0,1,0,1,0},
                {0,0,1,0,0},
                {0,0,0,0,0}
            }
        },

        {
            .id = BLINKER, .rows = 5, .cols = 5, .data =
            {
                {0,0,0,0,0},
                {0,0,1,0,0},
                {0,0,1,0,0},
                {0,0,1,0,0},
                {0,0,0,0,0}
            }
        },

        {
            .id = TOAD, .rows = 6, .cols = 6, .data =
            {
                {0,0,0,0,0,0},
                {0,0,0,1,0,0},
                {0,1,0,0,1,0},
                {0,1,0,0,1,0},
                {0,0,1,0,0,0},
                {0,0,0,0,0,0}
            }
        },

        {
            .id = BEACON, .rows = 4, .cols = 4, .data = 
            {
                {1,1,0,0},
                {1,1,0,0},
                {0,0,1,1},
                {0,0,1,1}
            }
        }
    };

} // end namespace
