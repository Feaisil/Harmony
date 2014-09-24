#include "choosebetweenevents.hpp"

#include "core/game.hpp"
#include "core/player.hpp"

namespace harmony{ namespace core{ namespace events{

ChooseBetweenEvents::ChooseBetweenEvents(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, std::vector<boost::shared_ptr<PlayerEvent>> playerEvents):
    PlayerEvent(game, player),
    playerEvents(playerEvents)
{

}

void ChooseBetweenEvents::trigger()
{
    if(not game.expired() and not player.expired())
    {
        boost::shared_ptr<PlayerEvent> event(player.lock()->accessSettings().interface->chooseBetweenEvents(player.lock(), playerEvents));

        event->game = game;
        event->player = player;
        event->trigger();
    }
}

}}}
