#pragma once

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace harmony{ namespace core{

class Setting;
class Turn;
class Game;
class Player;

namespace events{
class DrawDisharmony;
class PlayHarmonyCards;
class MultipleEvents;
class MultiplePlayerEvents;
class ChooseBetweenEvents;

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
    friend class MultipleEvents;
    friend class MultiplePlayerEvents;
    friend class DrawDisharmony;
    friend class ChooseBetweenEvents;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {

        ar & BOOST_SERIALIZATION_NVP(game);
    }
};

class PlayerEvent: public Event
{
public:
    virtual ~PlayerEvent(){}
protected:
    PlayerEvent(const boost::weak_ptr<Game>&  game, const boost::weak_ptr<Player>& player );
    PlayerEvent(){}

protected:
    boost::weak_ptr<Player> player;

private:
    friend class MultiplePlayerEvents;
    friend class PlayHarmonyCards;
    friend class ChooseBetweenEvents;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Event);
        ar & BOOST_SERIALIZATION_NVP(player);
    }
};

class MultipleEvents: public Event
{
public:
    MultipleEvents(const boost::weak_ptr<Game> &game, std::vector<boost::shared_ptr<Event>> events);
    void trigger();
    const std::vector<boost::shared_ptr<Event>>& getEvents(){ return events;}
private:
    std::vector<boost::shared_ptr<Event>> events;

    friend class ::harmony::core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Event);
        ar & BOOST_SERIALIZATION_NVP(events);
    }
};
class MultiplePlayerEvents: public PlayerEvent
{
public:
    MultiplePlayerEvents(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, std::vector<boost::shared_ptr<PlayerEvent>> events);
    void trigger();
    const std::vector<boost::shared_ptr<PlayerEvent>>& getEvents(){ return playerEvents;}
private:
    MultiplePlayerEvents(){}
private:
    std::vector<boost::shared_ptr<PlayerEvent>> playerEvents;

    friend class ::harmony::core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PlayerEvent);
        ar & BOOST_SERIALIZATION_NVP(playerEvents);
    }
};
}}} // namespaces

