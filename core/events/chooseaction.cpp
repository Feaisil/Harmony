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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // not working or not called ?
        static boost::random::mt19937 gen;
        static boost::random::uniform_int_distribution<> dist(0, 4);


        int decision = dist(gen);//REMOVE

        if( decision == 0 )
        {
            return common::Element::Aether;
        }
        if( decision == 1 )
        {
            return common::Element::Fire;
        }
        if( decision == 2 )
        {
            return common::Element::Earth;
        }
        if( decision == 3 )
        {
            return common::Element::Water;
        }
        if( decision == 4 )
        {
            return common::Element::Wind;
        }
    }

};

ChooseAction::ChooseAction(Game& game, Turn &turn):
    Event(game),
    turn(turn)
{

}

void ChooseAction::trigger()
{
    SimultaneousQuery<DoChooseAction, false> query;
    DoChooseAction::Args args;
    std::vector<typename DoChooseAction::_returnType> result = query(game.players, args);
    for(size_t index = 0; index < game.players.size(); ++index)
    {
        boost::shared_ptr<Event> event(new PureHarmony(game, game.players[index], result[index]));
        turn << event;
    }
}

}}} // namespaces
