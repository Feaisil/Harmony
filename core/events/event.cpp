#include "event.hpp"

namespace harmony{ namespace core{ namespace events{

Event::Event(const boost::weak_ptr<Game> &game):
    game(game)
{

}
PlayerEvent::PlayerEvent(const boost::weak_ptr<Game>&  game, const boost::weak_ptr<Player>& player ):
    Event(game),
    player(player)
{

}


MultipleEvents::MultipleEvents(const boost::weak_ptr<Game> &game, std::vector<boost::shared_ptr<Event>> events):
    Event(game),
    events(events)
{

}
void MultipleEvents::trigger()
{
    if(not game.expired())
    {
        for(auto event: events)
        {
            event->game = game;
            event->trigger();
        }
    }
}

MultiplePlayerEvents::MultiplePlayerEvents(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, std::vector<boost::shared_ptr<PlayerEvent>> events):
    PlayerEvent(game, player),
    playerEvents(events)
{

}

void MultiplePlayerEvents::trigger()
{
    if(not game.expired() and not player.expired())
    {
        for(auto event: playerEvents)
        {
            event->game = game;
            event->player = player;
            event->trigger();
        }
    }
}

}}}
