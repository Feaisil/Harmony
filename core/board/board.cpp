#include "board.hpp"

namespace harmony{ namespace core{ namespace board{

Board::Board(unsigned int size):
    size(size)
{}

void Board::operator()(Position& position, common::Element element) const
{
    // if placement is not at end move
    if(position.index < size)
    {
        position(element);
    }
}
const BalancePoint &Board::getBalancePoint() const
{
    return balancePoint;
}

int Board::ComputeScore(const Position& position) const
{
    int result = 0;
    switch(position.getDirection())
    {
    case Position::Direction::Aether:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::AetherEarth:
        case Position::Direction::WaterAether:
            result += 1;
            break;
        case Position::Direction::Earth:
        case Position::Direction::Water:
            result += 2;
            break;
        case Position::Direction::EarthFire:
        case Position::Direction::WindWater:
            result += 3;
            break;
        case Position::Direction::Fire:
        case Position::Direction::Wind:
            result += 4;
            break;
        case Position::Direction::FireWind:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::AetherEarth:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::Aether:
        case Position::Direction::Earth:
            result += 1;
            break;
        case Position::Direction::WaterAether:
        case Position::Direction::EarthFire:
            result += 2;
            break;
        case Position::Direction::Water:
        case Position::Direction::Fire:
            result += 3;
            break;
        case Position::Direction::WindWater:
        case Position::Direction::FireWind:
            result += 4;
            break;
        case Position::Direction::Wind:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::Earth:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::AetherEarth:
        case Position::Direction::EarthFire:
            result += 1;
            break;
        case Position::Direction::Aether:
        case Position::Direction::Fire:
            result += 2;
            break;
        case Position::Direction::WaterAether:
        case Position::Direction::FireWind:
            result += 3;
            break;
        case Position::Direction::Water:
        case Position::Direction::Wind:
            result += 4;
            break;
        case Position::Direction::WindWater:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::EarthFire:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::Earth:
        case Position::Direction::Fire:
            result += 1;
            break;
        case Position::Direction::AetherEarth:
        case Position::Direction::FireWind:
            result += 2;
            break;
        case Position::Direction::Aether:
        case Position::Direction::Wind:
            result += 3;
            break;
        case Position::Direction::WaterAether:
        case Position::Direction::WindWater:
            result += 4;
            break;
        case Position::Direction::Water:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::Fire:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::FireWind:
        case Position::Direction::EarthFire:
            result += 1;
            break;
        case Position::Direction::Wind:
        case Position::Direction::Earth:
            result += 2;
            break;
        case Position::Direction::WindWater:
        case Position::Direction::AetherEarth:
            result += 3;
            break;
        case Position::Direction::Water:
        case Position::Direction::Aether:
            result += 4;
            break;
        case Position::Direction::WaterAether:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::FireWind:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::Wind:
        case Position::Direction::Fire:
            result += 1;
            break;
        case Position::Direction::WindWater:
        case Position::Direction::EarthFire:
            result += 2;
            break;
        case Position::Direction::Water:
        case Position::Direction::Earth:
            result += 3;
            break;
        case Position::Direction::WaterAether:
        case Position::Direction::AetherEarth:
            result += 4;
            break;
        case Position::Direction::Aether:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::Wind:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::FireWind:
        case Position::Direction::WindWater:
            result += 1;
            break;
        case Position::Direction::Fire:
        case Position::Direction::Water:
            result += 2;
            break;
        case Position::Direction::EarthFire:
        case Position::Direction::WaterAether:
            result += 3;
            break;
        case Position::Direction::Earth:
        case Position::Direction::Aether:
            result += 4;
            break;
        case Position::Direction::AetherEarth:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::WindWater:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::Wind:
        case Position::Direction::Water:
            result += 1;
            break;
        case Position::Direction::FireWind:
        case Position::Direction::WaterAether:
            result += 2;
            break;
        case Position::Direction::Fire:
        case Position::Direction::Aether:
            result += 3;
            break;
        case Position::Direction::EarthFire:
        case Position::Direction::AetherEarth:
            result += 4;
            break;
        case Position::Direction::Earth:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::Water:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::WindWater:
        case Position::Direction::WaterAether:
            result += 1;
            break;
        case Position::Direction::Wind:
        case Position::Direction::Aether:
            result += 2;
            break;
        case Position::Direction::FireWind:
        case Position::Direction::AetherEarth:
            result += 3;
            break;
        case Position::Direction::Fire:
        case Position::Direction::Earth:
            result += 4;
            break;
        case Position::Direction::EarthFire:
            result += 5;
            break;
        default:
            break;
        }
        break;
    case Position::Direction::WaterAether:
        switch(balancePoint.getDirection())
        {
        case Position::Direction::Aether:
        case Position::Direction::Water:
            result += 1;
            break;
        case Position::Direction::AetherEarth:
        case Position::Direction::WindWater:
            result += 2;
            break;
        case Position::Direction::Earth:
        case Position::Direction::Wind:
            result += 3;
            break;
        case Position::Direction::EarthFire:
        case Position::Direction::FireWind:
            result += 4;
            break;
        case Position::Direction::Fire:
            result += 5;
            break;
        default:
            break;
        }
        break;
    default:
            break;
    }
    result += ::abs(position.getIndex() - balancePoint.getIndex());
    if( (position.getIndex() + balancePoint.getIndex()) <= result)
    {
        result = position.getIndex() + balancePoint.getIndex();
    }
    result = 2*size - result;
    result += size - position.getIndex();
    return result;
}

}}} // namespaces

