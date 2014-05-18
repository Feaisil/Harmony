#pragma once

#include "board/position.hpp"
#include "harmonycard.hpp"

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

namespace harmony{ namespace core{

namespace events{
class Event;
class PureHarmony;
}

struct PlayerSettings
{

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    { 
    }
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
	ar & BOOST_SERIALIZATION_NVP(harmonyDeck);
	ar & BOOST_SERIALIZATION_NVP(playerBoard);
	ar & BOOST_SERIALIZATION_NVP(money);
	ar & BOOST_SERIALIZATION_NVP(stock);
	ar & BOOST_SERIALIZATION_NVP(settings);
    }

};

}}
