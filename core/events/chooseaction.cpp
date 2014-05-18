#include "chooseaction.hpp"
#include "pureharmony.hpp"

#include "core/turn.hpp"
#include "core/player.hpp"
#include "core/common.hpp"
#include "core/game.hpp"

// For random tests
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
namespace harmony{ namespace core{ namespace events{

ChooseAction::ChooseAction(Game& game, Turn &turn):
    Event(game),
    turn(turn)
{

}

void ChooseAction::trigger()
{
    static boost::random::mt19937 gen;
    static boost::random::uniform_int_distribution<> dist(0, 4);


    for(boost::shared_ptr<Player> player: game.players)
    {
        int decision = dist(gen);//REMOVE
        // TODO Query player
        // TODO Enqueue Action

        if( decision == 0 )
        {
            boost::shared_ptr<Event> event(new PureHarmony(game, player, common::Element::Aether));
            turn << event;
        }
        if( decision == 1 )
        {
            boost::shared_ptr<Event> event(new PureHarmony(game, player, common::Element::Fire));
            turn << event;
        }
        if( decision == 2 )
        {
            boost::shared_ptr<Event> event(new PureHarmony(game, player, common::Element::Earth));
            turn << event;
        }
        if( decision == 3 )
        {
            boost::shared_ptr<Event> event(new PureHarmony(game, player, common::Element::Water));
            turn << event;
        }
        if( decision == 4 )
        {
            boost::shared_ptr<Event> event(new PureHarmony(game, player, common::Element::Wind));
            turn << event;
        }
    }
}

}}} // namespaces
