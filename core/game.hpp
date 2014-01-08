#pragma once

#include "board/board.hpp"
#include "player.hpp"

#include <list>
#include <memory>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

namespace harmony{ namespace core{

class Turn;

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
    std::list<boost::shared_ptr<Player>> players;
    board::Board board;

    friend class Turn;
    friend class events::Event;
    friend class events::ChooseAction;
    friend class events::PureHarmony;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(players);
        ar & BOOST_SERIALIZATION_NVP(board);
    }

    friend std::ostream& operator<< (std::ostream& stream, const Game & game);
};

}}
