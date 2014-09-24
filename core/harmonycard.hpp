#pragma once

#include <boost/serialization/nvp.hpp>

#include <boost/serialization/list.hpp>

#include "core/events/addmodifier.hpp"
#include "core/events/movetowardselement.hpp"
#include "core/events/choosebetweenevents.hpp"

namespace harmony{ namespace core{
namespace events{
class PlayerEvent;
class PlayHarmonyCards;
}

class HarmonyCard
{
public:
    const std::string &getName() const{ return name;}
    int getPriority() const{ return priority;}
    int getBeverageCost() const{ return beverageCost;}
    int getMealCost() const{ return mealCost;}
    int getEnergyCost() const{ return energyCost;}
private:
    std::string name;
    int priority;
    int beverageCost;
    int mealCost;
    int energyCost;
    std::list<boost::shared_ptr<events::PlayerEvent>> events;
private:
    friend class Setting;
    friend class events::PlayHarmonyCards;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar.register_type(static_cast<events::AddModifierToPlayer*>(NULL));
        ar.register_type(static_cast<events::AddModifierToGame*>(NULL));
        ar.register_type(static_cast<events::MovePlayerTowardsElement*>(NULL));
        ar.register_type(static_cast<events::MultiplePlayerEvents*>(NULL));
        ar.register_type(static_cast<events::ChooseBetweenEvents*>(NULL));
        ar & BOOST_SERIALIZATION_NVP(name);
        ar & BOOST_SERIALIZATION_NVP(priority);
        ar & BOOST_SERIALIZATION_NVP(beverageCost);
        ar & BOOST_SERIALIZATION_NVP(mealCost);
        ar & BOOST_SERIALIZATION_NVP(energyCost);
        ar & BOOST_SERIALIZATION_NVP(events);
    }
};

}}
