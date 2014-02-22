#pragma once

#include <memory>
#include <iostream>

#include <boost/serialization/nvp.hpp>

#include "core/common.hpp"

namespace harmony{ namespace core{ namespace board{

class Board;

struct Position
{
public:
    Position();
private:
    /** Update with an input element */
    void operator()(common::Element element);

private:
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
    } direction;
    size_t index;

    friend class Board;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(direction);
        ar & BOOST_SERIALIZATION_NVP(index);
    }
};

}}} // namespaces
