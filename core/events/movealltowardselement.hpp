#pragma once

#include "event.hpp"
#include "core/element.hpp"

namespace harmony{ namespace core{
    class Setting;
}}
namespace harmony{ namespace core{ namespace events{

class MoveAllTowardsElement : public Event
{
public:
    MoveAllTowardsElement(const boost::weak_ptr<Game> &game, common::Element element);
private:
    virtual void trigger();

    MoveAllTowardsElement():element(common::Element::Aether){}
private:
    common::Element element;

    friend class ::harmony::core::Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Event);
        ar & BOOST_SERIALIZATION_NVP(element);
    }
};

}}}
