#pragma once

#include "core/common.hpp"
#include "event.hpp"

namespace harmony{ namespace core{

class Player;

namespace events{
class ChooseAction;

class PureHarmony : public Event
{
private:
    PureHarmony(Game& game, Player &player, common::Element element);
    virtual void trigger() const;
private:
    Player &player;
    common::Element element;

    friend class ChooseAction;
};

}}} // namespaces
