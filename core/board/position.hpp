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
    void operator()(common::Element element);

    Direction getDirection() const;

    size_t getIndex() const;

private:

    Position( const Position& p){}
    friend class Board;
    friend class harmony::core::Engine;
    Direction direction;
    size_t index;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(direction);
        ar & BOOST_SERIALIZATION_NVP(index);
    }
};

}}} // namespaces
