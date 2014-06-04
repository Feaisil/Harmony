#include "engine.hpp"

namespace harmony{ namespace core{

Engine::Engine(const Setting &settings):
    state(State::initialized),
    game(settings)
{

}

void Engine::operator()(int numberOfTurns)
{
    state = State::running;
    for(int i = 0; i<numberOfTurns; ++i)
    {
        boost::shared_ptr<harmony::core::Turn> turn(new harmony::core::Turn (game));
        (*turn)();
        executedTurns.push_back(turn);
        for(std::vector<boost::shared_ptr<Player>>::const_iterator it = game.players.begin(); it != game.players.end(); ++it)
        {
            if((*it)->position.index > 5)
            {
                state = State::ended;
            }
        }
    }
}

}}
