#pragma once

#include "event.hpp"

namespace harmony{ namespace core{ namespace events{

enum class DestroyType
{
    Beverage,
    Meal,
    Energy
};

class DestroyResource: public Event
{
public:
    DestroyResource(const boost::weak_ptr<Game> &game, DestroyType type, int power);
    DestroyResource(): type(DestroyType::Beverage){}
private:
    virtual void trigger();
private:
    DestroyType type;
    int power;

    friend class core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Event);
        ar & BOOST_SERIALIZATION_NVP(type);
        ar & BOOST_SERIALIZATION_NVP(power);
    }
};

}}}
