#include "harmoniousmeal.hpp"

#include "core/player.hpp"
#include "core/game.hpp"
#include "core/board/board.hpp"

namespace harmony{ namespace core{ namespace events{

HarmoniousMeal::HarmoniousMeal(const boost::weak_ptr<Game>& game, const boost::weak_ptr<Player> & player, common::Element element):
    Event(game),
    player(player),
    element(element)
{
}

void HarmoniousMeal::trigger()
{
    game.lock()->board(player.lock()->position, element);
}

}}} // namespaces
