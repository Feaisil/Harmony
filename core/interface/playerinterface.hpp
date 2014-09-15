#pragma once

#include <core/element.hpp>
#include <boost/shared_ptr.hpp>

namespace harmony{ namespace core {
class Player;
}}

namespace harmony{ namespace core { namespace interface{

class PlayerInterface
{
public:
    PlayerInterface();
    virtual ~PlayerInterface(){}

    virtual common::Element choosePureHarmony(boost::shared_ptr<harmony::core::Player> & player) const = 0;
    // Choose Action
    // Choose card
    // etc
};

}}}
