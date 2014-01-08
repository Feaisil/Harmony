#pragma once

#include "core/common.hpp"
#include "event.hpp"

namespace harmony{ namespace core{

class Player;

namespace events{
class AddChosenAction;

class PureHarmony : public Event
{
public:
    PureHarmony(Game & game, const boost::weak_ptr<Player> & player, common::Element element);
private:
    virtual void trigger();
private:
    const boost::weak_ptr<Player> player;
    common::Element element;

    friend class AddChosenAction;
};

}}} // namespaces
