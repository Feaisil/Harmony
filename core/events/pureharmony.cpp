#include "pureharmony.hpp"

#include "core/player.hpp"
#include "core/game.hpp"
#include "core/board/board.hpp"

namespace harmony{ namespace core{ namespace events{

PureHarmony::PureHarmony(Game& game, Player &player, common::Element element):
    Event(game),
    player(player),
    element(element)
{
}

void PureHarmony::trigger() const
{
    game.board.operator ()(player.position, element);
    game.board.operator ()(game.board.balancePoint, element);
}

}}} // namespaces
