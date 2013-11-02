#pragma once

#include <memory>
#include <iostream>
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
    friend std::ostream& operator<< (std::ostream& stream, const Position::Direction &dir);
    friend std::ostream& operator<< (std::ostream& stream, const Position &pos);
};

}}} // namespaces
