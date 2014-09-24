#pragma once

#include <memory>
#include <iostream>

#include <boost/serialization/nvp.hpp>

#include "core/element.hpp"

namespace harmony{ namespace core{
class Engine;

namespace board{

class Board;

struct Position
{
public:
    enum class Direction{
        Center,
        Fire,
        FireWind,
        Wind,
        WindWater,
        Water,
        WaterAether,
        Aether,
        AetherEarth,
        Earth,
        EarthFire
    };

    Position();
    /** Update with an input element */
    void operator()(common::Element element, bool negative = false);
    void moveToCenter();
    Direction getDirection() const;

    int getIndex() const;

private:
    friend class Board;
    friend class harmony::core::Engine;
    Direction direction;
    int index;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & BOOST_SERIALIZATION_NVP(direction);
        ar & BOOST_SERIALIZATION_NVP(index);
    }
};

}}} // namespaces
