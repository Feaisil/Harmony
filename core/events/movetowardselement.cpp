#include "movetowardselement.hpp"
#include "core/game.hpp"
#include "core/player.hpp"


namespace harmony{ namespace core{ namespace events{

MoveAllTowardsElement::MoveAllTowardsElement(const boost::weak_ptr<Game>& game, common::Element element):
    Event(game),
    element(element),
    negative(false)
{
}

void MoveAllTowardsElement::trigger()
{
    if(not game.expired())
    {
        boost::shared_ptr<Game> gameLock = game.lock();
        for(auto player: gameLock->players)
        {
            gameLock->board(player->position, element, negative);
        }
        gameLock->board(gameLock->board.balancePoint, element, negative);
    }
}

MovePlayerTowardsElement::MovePlayerTowardsElement(const boost::weak_ptr<Game>& game, const boost::weak_ptr<Player> &player, common::Element element):
    PlayerEvent(game, player),
    element(element)
{
}

void MovePlayerTowardsElement::trigger()
{
    if(not game.expired() and not player.expired())
    {
        auto playerLock = player.lock();
        auto gameLock = game.lock();
        gameLock->board(playerLock->position, element);
        gameLock->board(gameLock->board.balancePoint, element);
    }
}

}}} // namespaces
