#pragma once

#include <memory>
#include <queue>
#include <list>

namespace harmony{ namespace core{

class Game;

namespace events{
class Event;
class ChooseAction;
}

class Turn
{
public:
    Turn(Game & game, unsigned int id);
    void operator()();
private:
    void operator<<(std::shared_ptr<events::Event>& event);
    std::queue<std::shared_ptr<events::Event>> remainingEvents;
    std::list<std::shared_ptr<events::Event>> executedEvents;
    const unsigned int id;
    Game &game;

    friend class events::ChooseAction;

//    friend std::ostream& operator<< (std::ostream& stream, const ::harmony::core::Turn & turn);
};

}} //namespaces
