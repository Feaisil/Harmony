#include "movealltowardselement.hpp"
#include "core/game.hpp"
#include "core/player.hpp"


namespace harmony{ namespace core{ namespace events{
MoveAllTowardsElement::MoveAllTowardsElement(const boost::weak_ptr<Game>& game, common::Element element):
    Event(game),
    element(element)
{
}

void MoveAllTowardsElement::trigger()
{
    if(not game.expired())
    {
        boost::shared_ptr<Game> gameLock = game.lock();
        for(auto player: gameLock->players)
        {
            gameLock->board(player->position, element);
        }
        gameLock->board(gameLock->board.balancePoint, element);
    }
}

}}} // namespaces
