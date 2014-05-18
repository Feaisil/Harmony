#include "engine.hpp"

namespace harmony{ namespace core{

Engine::Engine()
{
}

void Engine::operator()(int numberOfTurns)
{
    for(int i = 0; i<numberOfTurns; ++i)
    {
        boost::shared_ptr<harmony::core::Turn> turn(new harmony::core::Turn (game));
        (*turn)();
        executedTurns.push_back(turn);
    }
}

}}
