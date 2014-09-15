#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

#include "core/events/movealltowardselement.hpp"

namespace harmony{ namespace core{

class Settings;

namespace events
{
class DrawDisharmony;
}

class DisharmonyCard
{
public:
    const std::string &getName() const{ return name;}
private:
    std::string name;
    std::list<boost::shared_ptr<events::Event>> events;

    friend class events::DrawDisharmony;
    friend class Setting;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar.register_type(static_cast<events::MoveAllTowardsElement*>(NULL));
        ar & BOOST_SERIALIZATION_NVP(name);
        ar & BOOST_SERIALIZATION_NVP(events);
    }
};

}}
