#include "game.hpp"
#include "player.hpp"
#include "settings.hpp"
namespace harmony{ namespace core{

Game::Game(const Setting& settings):
    board(settings.numberOfPlayers),
    settings(settings)
{
    assert(settings.playersSettings.size() < 6 and settings.numberOfPlayers == settings.playersSettings.size());

    for(std::list<PlayerSetting>::const_iterator it = settings.playersSettings.begin(); it != settings.playersSettings.end(); ++it)
    {
        players.push_back(boost::shared_ptr<Player>(new Player(settings, *it)));
        for(short i = 0; i < settings.distanceFromStart; ++i)
        {
            players.back()->position(players.back()->settings.element);
        }
    }
}

}}
