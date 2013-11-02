#pragma once

#include "board/position.hpp"

namespace harmony{ namespace core{

namespace events{
class Event;
class PureHarmony;
}

class Player
{
public:
    Player();

private:
    board::Position position;

    friend class events::Event;
    friend class events::PureHarmony;

    friend std::ostream& operator<< (std::ostream& stream, const Player & player);
};

}}
