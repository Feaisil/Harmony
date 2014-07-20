#include "game.hpp"
#include "player.hpp"
#include "settings.hpp"
namespace harmony{ namespace core{

Game::Game(const Setting& settings):
    board(settings.boardSize),
    settings(settings)
{
    std::cout << settings.boardSize << std::endl; // TODO REMOVE DEBUG
    assert(settings.playersSettings.size() < size_t(6) and settings.numberOfPlayers == settings.playersSettings.size());

    for(std::list<boost::shared_ptr<PlayerSetting>>::const_iterator it = settings.playersSettings.begin(); it != settings.playersSettings.end(); ++it)
    {
        players.push_back(boost::shared_ptr<Player>(new Player(settings, **it)));
        for(short i = 0; i < settings.distanceFromStart; ++i)
        {
            players.back()->position(players.back()->settings.element);
        }
    }
}
const std::vector<boost::shared_ptr<Player> >& Game::getPlayers() const
{
    return players;
}
const board::Board &Game::getBoard() const
{
    return board;
}

}}
