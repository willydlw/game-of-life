#ifndef PATTERNS_HPP
#define PATTERNS_HPP

#include <string>

namespace GlobalConstants
{
    enum PatternId{
        BLOCK,
        BEEHIVE,
        BLINKER
    };

    struct Pattern{
        int rows;
        int cols;
        int **data; 
    };

    const char* patternNames[3] = {"Block", "Beehive", "Blinker"};

    // Initialization Patterns

    const Pattern BLOCK_PATTERN = {.rows = 3, .cols = 3, .ptrData(&BLOCK)};
    constexpr int R_PENTIMINO_DIMENSION = 3;
    extern const int R_PENTOMINO[3][3];

    // Still Life Patterns
    constexpr int BLOCK_PATTERN_DIMENSION = 4;
    extern const int BLOCK[4][4];

    constexpr int BEEHIVE_PATTERN_ROWS = 5;   
    constexpr int BEEHIVE_PATTERN_COLS = 6;     
    extern const int BEEHIVE[5][6];      


    // Oscillation Patterns
    constexpr int BLINKER_PATTERN_DIMENSION = 5;
    extern const int BLINKER[5][5];         // period 2
    
    constexpr int TOAD_PATTERN_DIMENSION = 6;
    extern const int TOAD[6][6];               // period 2

    constexpr int BEACON_PATTERN_DIMENSION = 4;
    extern const int BEACON[4][4];          // period 2


}

#endif 