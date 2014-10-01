#pragma once

#include <core/element.hpp>
#include <boost/shared_ptr.hpp>
#include <list>

namespace harmony{ namespace core {
class Player;
class HarmonyCard;
namespace events{
class Event;
class PlayerEvent;
}
}}

namespace harmony{ namespace core { namespace interface{

enum class Action
{
    PlayHarmonyCards,
    ReplaceHarmonyCards,
    ProduceBeverage,
    ProduceMeal,
    Rest,
    Eat,
    HarmoniousMeal
};
enum class ChooseCardType
{
    PlayHarmony,
    ReplaceHarmony
};

class PlayerInterface
{
public:
    PlayerInterface(){}
    virtual ~PlayerInterface(){}

    virtual Action chooseAction(const boost::shared_ptr<harmony::core::Player> & player, const std::vector<boost::shared_ptr<core::HarmonyCard>> & harmonyHand) = 0;
    virtual common::Element chooseHarmoniousMealDirection(const boost::shared_ptr<harmony::core::Player> & player) = 0;
    virtual std::list<boost::shared_ptr<HarmonyCard>> chooseCard(const boost::shared_ptr<harmony::core::Player> & player, const std::vector<boost::shared_ptr<HarmonyCard>> &harmonyHand, ChooseCardType type) = 0;
    virtual boost::shared_ptr<events::PlayerEvent> chooseBetweenEvents(const boost::shared_ptr<harmony::core::Player> & player, std::vector<boost::shared_ptr<events::PlayerEvent>> & events) = 0;
};

}}}
