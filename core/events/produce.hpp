#pragma once

#include "event.hpp"

namespace harmony{ namespace core{ namespace events{
class ChooseAction;

enum class ProduceType
{
    Beverage,
    Meal,
    Rest,
    Eat
};

class Produce : public PlayerEvent
{
private:
    Produce(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, ProduceType type);
    virtual void trigger();
private:
    ProduceType type;
    friend class ChooseAction;
};
}}}
