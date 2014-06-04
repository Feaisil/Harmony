#pragma once

#include "game.hpp"
#include "turn.hpp"

namespace harmony{ namespace core{

class Engine
{
    enum class State
    {
        initialized,
        running,
        ended
    };

public:
    Engine(const Setting &settings);
    void operator()(int numberOfTurns);
private:
    State state;
    Game game;
    std::list<boost::shared_ptr<Turn>> executedTurns;

    Engine(){}
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(state);
        ar & BOOST_SERIALIZATION_NVP(game);
        //ar & BOOST_SERIALIZATION_NVP(executedTurns);
    }
};

}}
