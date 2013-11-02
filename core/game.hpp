#pragma once

#include "board/board.hpp"

#include <list>
#include <memory>

namespace harmony{ namespace core{

class Turn;
class Player;

namespace events{
class Event;
class ChooseAction;
class PureHarmony;
}

class Game
{
public:
    Game();

private:
    std::list<std::shared_ptr<Player>> players;
    board::Board board;

    friend class Turn;
    friend class events::Event;
    friend class events::ChooseAction;
    friend class events::PureHarmony;

    friend std::ostream& operator<< (std::ostream& stream, const Game & game);
};

}}
