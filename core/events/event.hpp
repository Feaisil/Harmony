#pragma once

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace harmony{ namespace core{

class Turn;
class Game;

namespace events{

class Event
{
protected:
    Event(Game& game);
    Event();
    virtual void trigger (){}
    virtual void replay (){ trigger(); }

protected:
    Game& game;

private:
private:
    friend class ::harmony::core::Turn;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(game);
    }
};

}}} // namespaces
