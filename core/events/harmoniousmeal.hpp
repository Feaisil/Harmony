#pragma once

#include "core/element.hpp"
#include "event.hpp"

namespace harmony{ namespace core{

class Player;

namespace events{
class AddChosenAction;

class HarmoniousMeal : public Event
{
public:
    HarmoniousMeal(const boost::weak_ptr<Game>& game, const boost::weak_ptr<Player> & player, common::Element element);
private:
    virtual void trigger();
private:
    const boost::weak_ptr<Player> player;
    common::Element element;

    friend class AddChosenAction;
};

}}} // namespaces
