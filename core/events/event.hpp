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
class DrawDisharmony;

class Event
{
public:
    virtual ~Event(){}
protected:
    Event(const boost::weak_ptr<Game>&  game);
    Event(){}
    virtual void trigger (){}
    virtual void replay (){ trigger(); }

protected:
    boost::weak_ptr<Game> game;

private:
    friend class ::harmony::core::Turn;
    friend class DrawDisharmony;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(game);
    }
};

}}} // namespaces

