#include "player.hpp"

namespace harmony{ namespace core{

Player::Player()
{
}

std::ostream& operator<< (std::ostream& stream, const ::harmony::core::Player & player)
{
    stream << "{ position : "
           << player.position
           << " }";

    return stream;
}

}} // namespaces
