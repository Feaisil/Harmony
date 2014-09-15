#pragma once

#include "event.hpp"

namespace harmony{ namespace core{
class Player;
}}
namespace harmony{ namespace core{ namespace events{

class ChooseAction : public Event
{
private:
    ChooseAction(const boost::weak_ptr<Game> &game,Turn& turn);
    virtual void trigger();
private:
    Turn& turn;

    friend class ::harmony::core::Turn;
};

}}} ///namespaces
