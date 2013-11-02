#include "chooseaction.hpp"
#include "pureharmony.hpp"

#include "core/turn.hpp"
#include "core/player.hpp"
#include "core/common.hpp"
#include "core/game.hpp"

namespace harmony{ namespace core{ namespace events{

ChooseAction::ChooseAction(Game& game, Turn &turn):
    Event(game),
    turn(turn)
{

}

void ChooseAction::trigger() const
{
    static int a = 0;//REMOVE
    for(std::shared_ptr<Player> player: game.players)
    {
        // TODO Query player
        // TODO Enqueue Action
        // TODO REMOVE BELOW
        if( a % 6 == 0 )
        {
            std::shared_ptr<Event> event(new PureHarmony(game, *player, common::Element::Aether));
            turn << event;
        }
        if( a % 7 == 1 )
        {
            std::shared_ptr<Event> event(new PureHarmony(game, *player, common::Element::Fire));
            turn << event;
        }
        if( a % 8 == 2 )
        {
            std::shared_ptr<Event> event(new PureHarmony(game, *player, common::Element::Earth));
            turn << event;
        }
        if( a % 9 == 3 )
        {
            std::shared_ptr<Event> event(new PureHarmony(game, *player, common::Element::Water));
            turn << event;
        }
        if( a % 10 == 4 )
        {
            std::shared_ptr<Event> event(new PureHarmony(game, *player, common::Element::Wind));
            turn << event;
        }
        ++a;
    }
}

}}} // namespaces
