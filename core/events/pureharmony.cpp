#include "pureharmony.hpp"

#include "core/player.hpp"
#include "core/game.hpp"
#include "core/board/board.hpp"

namespace harmony{ namespace core{ namespace events{

PureHarmony::PureHarmony(const boost::weak_ptr<Game>& game, const boost::weak_ptr<Player> & player, common::Element element):
    Event(game),
    player(player),
    element(element)
{
}

void PureHarmony::trigger()
{
    boost::shared_ptr<Game> gameLock = game.lock();
    gameLock->board(player.lock()->position, element);
    gameLock->board(gameLock->board.balancePoint, element);
}

}}} // namespaces
