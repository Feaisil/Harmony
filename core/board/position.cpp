#include "position.hpp"

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

}}} // namespaces
