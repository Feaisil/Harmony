#pragma once

#include "event.hpp"

namespace harmony{ namespace core{ namespace events{

class CheckForEndConditions : public Event
{
private:
    CheckForEndConditions(const boost::weak_ptr<Game> &game);
    virtual void trigger();
private:
    friend class ::harmony::core::Turn;
};

}}}
