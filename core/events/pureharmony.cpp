#include "pureharmony.hpp"

#include "core/player.hpp"
#include "core/game.hpp"
#include "core/board/board.hpp"

namespace harmony{ namespace core{ namespace events{

PureHarmony::PureHarmony(Game & game, const boost::weak_ptr<Player> & player, common::Element element):
    Event(game),
    player(player),
    element(element)
{
}

void PureHarmony::trigger()
{
    game.board(player.lock()->position, element);
    game.board(game.board.balancePoint, element);
}

}}} // namespaces
