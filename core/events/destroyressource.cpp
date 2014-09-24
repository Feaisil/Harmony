#include "destroyressource.hpp"

#include "core/game.hpp"

namespace harmony{ namespace core{ namespace events{

DestroyResource::DestroyResource(const boost::weak_ptr<Game> &game, DestroyType type, int power):
    Event(game),
    type(type),
    power(power)
{

}

void DestroyResource::trigger()
{
    if(not game.expired())
    {
        auto gameLock = game.lock();
        for(auto player: gameLock->players)
        {
            switch(type)
            {
            case DestroyType::Beverage:
                player->beverage = std::max(0, player->beverage - power);
                break;
            case DestroyType::Meal:
                player->meal = std::max(0, player->meal - power);
                break;
            case DestroyType::Energy:
                player->energy = std::max(0, player->energy - power);
                break;
            default:
                break;
            }
        }
    }
}

}}}
