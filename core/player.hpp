#pragma once

#include "board/position.hpp"
#include "harmonycard.hpp"

#include <list>
#include <boost/shared_ptr.hpp>

namespace harmony{ namespace core{

namespace events{
class Event;
class PureHarmony;
}

struct PlayerSettings
{

};

class Player
{
public:
    Player();

private:
    board::Position position;
    std::list<boost::shared_ptr<HarmonyCard>> harmonyDeck;
    std::list<boost::shared_ptr<HarmonyCard>> playerBoard;
    int money;
    int stock;
    PlayerSettings settings;

    friend class events::Event;
    friend class events::PureHarmony;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(position);
    }

};

}}
