#pragma once

#include "board/board.hpp"
#include "player.hpp"
#include "harmonycard.hpp"
#include "disharmonycard.hpp"

#include <list>
#include <memory>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>

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
    std::vector<boost::shared_ptr<Player>> players;
    board::Board board;
    std::list<boost::shared_ptr<HarmonyCard>> harmonyDeck;
    std::list<boost::shared_ptr<HarmonyCard>> harmonyDiscard;
    std::list<boost::shared_ptr<DisharmonyCard>> disharmonyDeck;
    std::list<boost::shared_ptr<DisharmonyCard>> disharmonyDiscard;

    friend class Turn;
    friend class events::Event;
    friend class events::ChooseAction;
    friend class events::PureHarmony;
    friend class Player;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(players);
        ar & BOOST_SERIALIZATION_NVP(board);
        ar & BOOST_SERIALIZATION_NVP(harmonyDeck);
        ar & BOOST_SERIALIZATION_NVP(harmonyDiscard);
        ar & BOOST_SERIALIZATION_NVP(disharmonyDeck);
        ar & BOOST_SERIALIZATION_NVP(disharmonyDiscard);
    }

};

}}
