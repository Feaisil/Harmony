#include "event.hpp"

namespace harmony{ namespace core{ namespace events{

Event::Event(const boost::weak_ptr<Game> &game):
    game(game)
{

}

}}}
