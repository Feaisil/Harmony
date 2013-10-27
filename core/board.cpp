#include "board.hpp"

namespace harmony{ namespace core{ namespace board{

Position::Position():
    direction(Direction::Center),
    index(0)
{}
void Position::operator()(common::Element element)
{
    switch(direction)
    {
    case Direction::Center:
        switch(element)
        {
        case common::Element::Fire:
            direction = Direction::Fire;
            break;
        case common::Element::Wind:
            direction = Direction::Wind;
            break;
        case common::Element::Water:
            direction = Direction::Water;
            break;
        case common::Element::Aether:
            direction = Direction::Aether;
            break;
        case common::Element::Earth:
            direction = Direction::Earth;
            break;
        default:
            break;
        }
        index ++;
        break;
    case Direction::Fire:
        switch(element)
        {
        case common::Element::Fire:
            index ++;
            break;
        case common::Element::Water:
            index --;
        case common::Element::Wind:
            direction = Direction::FireWind;
            break;
        case common::Element::Aether:
            index --;
        case common::Element::Earth:
            direction = Direction::EarthFire;
            break;
        default:
            break;
        }
        break;
    case Direction::FireWind:
        switch(element)
        {
        case common::Element::Fire:
            index ++;
        case common::Element::Earth:
            direction = Direction::Fire;
            break;
        case common::Element::Wind:
            index ++;
        case common::Element::Water:
        case common::Element::Aether:
            direction = Direction::Wind;
            break;
        default:
            break;
        }
        break;
    case Direction::Wind:
        switch(element)
        {
        case common::Element::Earth:
            index --;
        case common::Element::Fire:
            direction = Direction::FireWind;
            break;
        case common::Element::Wind:
            index ++;
            break;
        case common::Element::Aether:
            index --;
        case common::Element::Water:
            direction = Direction::WindWater;
            break;
        default:
            break;
        }
        break;
    case Direction::WindWater:
        switch(element)
        {
        case common::Element::Wind:
            index ++;
        case common::Element::Fire:
            direction = Direction::Wind;
            break;
        case common::Element::Water:
            index ++;
        case common::Element::Aether:
        case common::Element::Earth:
            direction = Direction::Water;
            break;
        default:
            break;
        }
        break;
    case Direction::Water:
        switch(element)
        {
        case common::Element::Fire:
            index --;
        case common::Element::Wind:
            direction = Direction::FireWind;
            break;
        case common::Element::Water:
            index ++;
            break;
        case common::Element::Earth:
            index --;
        case common::Element::Aether:
            direction = Direction::WindWater;
            break;
        default:
            break;
        }
        break;
    case Direction::WaterAether:
        switch(element)
        {
        case common::Element::Water:
            index ++;
        case common::Element::Wind:
            direction = Direction::Water;
            break;
        case common::Element::Aether:
            index ++;
        case common::Element::Earth:
        case common::Element::Fire:
            direction = Direction::Earth;
            break;
        default:
            break;
        }
        break;
    case Direction::Aether:
        switch(element)
        {
        case common::Element::Wind:
            index --;
        case common::Element::Water:
            direction = Direction::WaterAether;
            break;
        case common::Element::Aether:
            index ++;
            break;
        case common::Element::Fire:
            index --;
        case common::Element::Earth:
            direction = Direction::AetherEarth;
            break;
        default:
            break;
        }
        break;
    case Direction::AetherEarth:
        switch(element)
        {
        case common::Element::Aether:
            index ++;
        case common::Element::Water:
            direction = Direction::Aether;
            break;
        case common::Element::Earth:
            index ++;
        case common::Element::Fire:
        case common::Element::Wind:
            direction = Direction::Earth;
            break;
        default:
            break;
        }
        break;
    case Direction::Earth:
        switch(element)
        {
        case common::Element::Water:
            index --;
        case common::Element::Aether:
            direction = Direction::AetherEarth;
            break;
        case common::Element::Earth:
            index ++;
            break;
        case common::Element::Wind:
            index --;
        case common::Element::Fire:
            direction = Direction::EarthFire;
            break;
        default:
            break;
        }
        break;
    case Direction::EarthFire:
        switch(element)
        {
        case common::Element::Fire:
            index ++;
        case common::Element::Wind:
            direction = Direction::Fire;
            break;
        case common::Element::Earth:
            index ++;
        case common::Element::Water:
        case common::Element::Aether:
            direction = Direction::Earth;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    if(index == 0)
    {
        direction = Direction::Center;
    }
}
std::ostream& operator<< (std::ostream& stream, Position::Direction dir)
{
    switch(dir)
    {
    case Position::Direction::Aether:
        stream << std::string("Aether");
        break;
    case Position::Direction::AetherEarth:
        stream << std::string("AetherEarth");
        break;
    case Position::Direction::Earth:
        stream << std::string("Earth");
        break;
    case Position::Direction::EarthFire:
        stream << std::string("EarthFire");
        break;
    case Position::Direction::Fire:
        stream << std::string("Fire");
        break;
    case Position::Direction::FireWind:
        stream << std::string("FireWind");
        break;
    case Position::Direction::Wind:
        stream << std::string("Wind");
        break;
    case Position::Direction::WindWater:
        stream << std::string("WindWater");
        break;
    case Position::Direction::Water:
        stream << std::string("Water");
        break;
    case Position::Direction::WaterAether:
        stream << std::string("WaterAether");
        break;
    case Position::Direction::Center:
        stream << std::string("Center");
        break;
    default:
        stream << std::string("Unknown");
        break;
    }
    return stream;
}
std::ostream& operator<< (std::ostream& stream, Position pos)
{
    stream << "{ direction : "
           << pos.direction
           << " | index : "
           << pos.index
           << " }";
    return stream;
}

Board::Board(size_t size):
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
}}}
