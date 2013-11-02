#pragma once

namespace harmony{ namespace core{

class Turn;
class Game;

namespace events{

class Event
{
protected:
    Event(Game &game);
    virtual void trigger () const{}

protected:
    Game &game;

private:
    friend class ::harmony::core::Turn;
};

}}} // namespaces
