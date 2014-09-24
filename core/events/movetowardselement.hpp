#pragma once

#include "event.hpp"
#include "core/element.hpp"

namespace harmony{ namespace core{ namespace events{

class MoveAllTowardsElement : public Event
{
public:
    MoveAllTowardsElement(const boost::weak_ptr<Game> &game, common::Element element);
private:
    virtual void trigger();

    MoveAllTowardsElement():element(common::Element::Aether), negative(false){}
private:
    common::Element element;
    bool negative;

private:
    friend class ::harmony::core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Event);
        ar & BOOST_SERIALIZATION_NVP(element);
        ar & BOOST_SERIALIZATION_NVP(negative);
    }
};


class MovePlayerTowardsElement : public PlayerEvent
{
public:
    MovePlayerTowardsElement(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, common::Element element);
private:
    virtual void trigger();

    MovePlayerTowardsElement():element(common::Element::Aether){}
private:
    common::Element element;


private:
    friend class ::harmony::core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PlayerEvent);
        ar & BOOST_SERIALIZATION_NVP(element);
    }
};
}}}
