#include "game.hpp"
#include "player.hpp"

namespace harmony{ namespace core{

Game::Game():
    board(5)
{
    for(int i = 0; i< 5; ++i)
    {
        players.push_back(boost::shared_ptr<Player>(new Player()));
    }
}

}}
