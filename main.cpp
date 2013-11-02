#include <iostream>
#include "core/game.hpp"
#include "core/turn.hpp"

int main( int argc, char** argv)
{
    harmony::core::Game game;
    std::cout << game << std::endl;
    for(int i = 0; i<200; ++i)
    {
        harmony::core::Turn turn(game, i);
        turn();
        std::cout << game << std::endl;
    }
    return EXIT_SUCCESS;
}

