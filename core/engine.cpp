#include "engine.hpp"

namespace harmony{ namespace core{

Engine::Engine(const Setting &settings):
    state(State::initialized)

{
    game.reset(new Game(settings));
}

void Engine::operator()()
{
    state = State::running;
    game->status = Game::Status::ongoing;
    // TODO remove turn count (temporary end condition)
    while(state == State::running)
    {
        boost::shared_ptr<harmony::core::Turn> turn(new harmony::core::Turn (game));
        (*turn)();
        executedTurns.push_back(turn);
        if(game->getStatus() != Game::Status::ongoing)
        {
            state = State::ended;
        }
    }
}
const Game &Engine::getGame() const
{
    return *game;
}


}}
