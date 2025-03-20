#ifndef PATTERNS_HPP
#define PATTERNS_HPP

#include <string>


namespace Pattern
{
    // Game of Life Patterns 
    constexpr int NUM_PATTERNS = 8;

    enum PatternId : int {
        BLOCK,
        BEEHIVE,
        LOAF,
        BOAT,
        TUB,
        BLINKER,
        TOAD,
        BEACON,
        RANDOM
    };

    struct PatternInfo{
        PatternId id;
        int rows;
        int cols;
        int data[9][9]; 
    };

    extern const char* patternNames[];
    extern const PatternInfo patterns[NUM_PATTERNS];


    constexpr int R_PENTIMINO_DIMENSION = 3;
    extern const int R_PENTOMINO[3][3];

    // Still Life Patterns: Block, Beehive, Loaf, Boat, Tub
    // Oscillators: Blinker(period 2), Toad(period 2), Beacon(period 2), 
    //      Pulsar(period 3), Pentadecathlon(period 15)
    // Spaceships: Glider, Lightweight spaceship (LWSS),
    //      Middle-weight spaceship(MWSS), Heavyweight Spaceship (HWSS)
     
}

#endif 