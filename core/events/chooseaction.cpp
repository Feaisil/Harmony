#include "chooseaction.hpp"
#include "pureharmony.hpp"

#include "core/turn.hpp"
#include "core/player.hpp"
#include "core/element.hpp"
#include "core/game.hpp"

// For random tests
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

// TODO remove
#include <chrono>
#include <thread>
namespace harmony{ namespace core{ namespace events{

struct DoChooseAction
{
    struct Args
    {

    };
    typedef Args _argumentType;
    typedef common::Element _returnType;

    _returnType operator()(boost::shared_ptr<Player> & player, _argumentType& args)
    {
        return player->accessSettings().interface->choosePureHarmony(player);
    }

};

ChooseAction::ChooseAction(const boost::weak_ptr<Game>& game, Turn &turn):
    Event(game),
    turn(turn)
{

}

void ChooseAction::trigger()
{
    boost::shared_ptr<Game> gameLock = game.lock();
    SimultaneousQuery<DoChooseAction> query (gameLock->settings.isParallel);
    DoChooseAction::Args args;

    std::vector<typename DoChooseAction::_returnType> result = query(gameLock->players, args);
    for(size_t index = 0; index < gameLock->players.size(); ++index)
    {
        boost::shared_ptr<Event> event(new PureHarmony(game, gameLock->players.at(index), result.at(index)));
        turn << event;
    }
}

}}} // namespaces
