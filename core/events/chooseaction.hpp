#pragma once

#include <memory>
#include <list>
#include "event.hpp"

namespace harmony{ namespace core{ namespace events{

class ChooseAction : public Event
{
private:
    ChooseAction(Game &game, Turn &turn);
    virtual void trigger() const;

private:
    Turn &turn;

    friend class ::harmony::core::Turn;
};

}}} ///namespaces
