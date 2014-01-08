#pragma once

#include "game.hpp"
#include "turn.hpp"

namespace harmony{ namespace core{

class Engine
{
public:
    Engine(/* game setting, player settings*/);
    void operator()(int numberOfTurns);
private:
    Game game;
    std::list<boost::shared_ptr<Turn>> executedTurns;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(game);
        //ar & BOOST_SERIALIZATION_NVP(executedTurns);
    }
};

}}
