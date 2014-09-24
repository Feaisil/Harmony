#pragma once

#include "event.hpp"
#include <list>
#include <map>

namespace harmony{ namespace core{
class HarmonyCard;
class Player;
class Game;
}}

namespace harmony{ namespace core{ namespace events{

class ChooseAction;

class PlayHarmonyCards : public Event
{
private:
    PlayHarmonyCards(const boost::weak_ptr<Game> & game, Turn& turn);
    virtual void trigger();
    void add(boost::weak_ptr<Player> player, std::list<boost::shared_ptr<HarmonyCard> > &cards);

private:
    Turn& turn;

    typedef int priority;
    std::multimap<priority, boost::shared_ptr<PlayerEvent>>  events;
private:
    friend class ChooseAction;
};
}}}
