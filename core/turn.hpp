#pragma once

#include <memory>
#include <list>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

#include "events/event.hpp"

namespace harmony{ namespace core{

class Game;

namespace events{
class Event;
class ChooseAction;
class AddChosenAction;
class DrawDisharmony;
class PlayHarmonyCards;
}

class Turn
{
public:
    Turn(const boost::weak_ptr<Game>& game);
    void operator()();
private:
    void processEvents();
    void operator<<(boost::shared_ptr<events::Event>& event);

private:
    /** Remaining events to be triggered*/
    std::list<boost::shared_ptr<events::Event>> remainingEvents;
    /** The following is to be used for replay */
    std::list<boost::shared_ptr<events::Event>> executedEvents;

    boost::weak_ptr<Game> game;

private:
    friend class events::ChooseAction;
    friend class events::AddChosenAction;
    friend class events::DrawDisharmony;
    friend class events::PlayHarmonyCards;

    Turn(){} // Default constructor for boost serialization
    friend class boost::serialization::access;template<class Archive>
    void serialize(Archive & ar, const unsigned int ) const
    {
        ar & BOOST_SERIALIZATION_NVP(remainingEvents);
        ar & BOOST_SERIALIZATION_NVP(executedEvents);
        ar & BOOST_SERIALIZATION_NVP(game);
    }
};

}} //namespaces
