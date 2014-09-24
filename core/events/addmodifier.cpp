#include "addmodifier.hpp"
#include "core/modifier.hpp"
#include "core/game.hpp"
#include "core/player.hpp"

namespace harmony{ namespace core{ namespace events{

AddModifierToPlayer::AddModifierToPlayer(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, Modifier modifier):
    PlayerEvent(game,player),
    modifier(modifier)
{

}
AddModifierToPlayer::AddModifierToPlayer():
    modifier(Modifier::AddHarmoniousMealAction)
{

}
void AddModifierToPlayer::trigger()
{
    player.lock()->modifiers.push_back(modifier);
}

AddModifierToGame::AddModifierToGame(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, Modifier modifier):
    PlayerEvent(game,player),
    modifier(modifier)
{

}
AddModifierToGame::AddModifierToGame():
    modifier(Modifier::AddHarmoniousMealAction)
{

}
void AddModifierToGame::trigger()
{
    game.lock()->modifiers.push_back(modifier);
}
}}}
