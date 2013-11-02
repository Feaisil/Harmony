#include "game.hpp"
#include "player.hpp"

namespace harmony{ namespace core{

Game::Game():
    board(5)
{
    for(int i = 0; i< 5; ++i)
    {
        players.push_back(std::shared_ptr<Player>(new Player()));
    }
}

std::ostream& operator<< (std::ostream& stream, const ::harmony::core::Game & game)
{
    stream << "{ board : "
           << game.board
           << "| players : [ ";
    for(std::shared_ptr<Player> player: game.players)
    {
        stream << *player
               << " , ";
    }
    stream << " ] }";

    return stream;
}

}}
