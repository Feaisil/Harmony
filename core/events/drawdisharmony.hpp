#pragma once

#include "event.hpp"

namespace harmony{ namespace core{ namespace events{

class DrawDisharmony : public Event
{
private:
    DrawDisharmony(const boost::weak_ptr<Game> &game,Turn& turn);
    virtual void trigger();
private:
    Turn& turn;

    friend class ::harmony::core::Turn;
};

}}}
