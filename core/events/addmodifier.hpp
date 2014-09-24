#pragma once

#include "event.hpp"
#include "core/modifier.hpp"

namespace harmony{ namespace core{
class Setting;
}}

namespace harmony{ namespace core{ namespace events{

class AddModifierToPlayer: public PlayerEvent
{
private:
    AddModifierToPlayer(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, Modifier modifier);
    AddModifierToPlayer();
    virtual void trigger();
private:
    Modifier modifier;
private:
    friend class ::harmony::core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PlayerEvent);
        ar & BOOST_SERIALIZATION_NVP(modifier);
    }
};

class AddModifierToGame : public PlayerEvent
{
private:
    AddModifierToGame(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, Modifier modifier);
    AddModifierToGame();
    virtual void trigger();
private:
    Modifier modifier;
private:
    friend class ::harmony::core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Event);
        ar & BOOST_SERIALIZATION_NVP(modifier);
    }
};

}}}
