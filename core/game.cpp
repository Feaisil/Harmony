#include "game.hpp"
#include "player.hpp"
#include "settings.hpp"

#include <algorithm>
#include <boost/random.hpp>

namespace harmony{ namespace core{

Game::Game(const Setting& settings):
    board(settings.boardSize),
    settings(settings),
    status(Status::notStarted)
{
    assert(settings.playersSettings.size() < size_t(6) and settings.numberOfPlayers == settings.playersSettings.size());

    static boost::random::mt19937 gen;

    for(std::list<boost::shared_ptr<PlayerSetting>>::const_iterator it = settings.playersSettings.begin(); it != settings.playersSettings.end(); ++it)
    {
        players.push_back(boost::shared_ptr<Player>(new Player(settings, **it)));
        for(short i = 0; i < settings.distanceFromStart; ++i)
        {
            players.back()->position(players.back()->settings.element);
        }
    }
    {
        std::vector<boost::shared_ptr<DisharmonyCard>> temporaryDisharmony;
        temporaryDisharmony.assign(settings.disharmonyDeckTier1.begin(), settings.disharmonyDeckTier1.end());
        std::shuffle(temporaryDisharmony.begin(), temporaryDisharmony.end(), gen);
        disharmonyDeck.insert(disharmonyDeck.end(), temporaryDisharmony.begin(), temporaryDisharmony.end());
        temporaryDisharmony.clear();
        temporaryDisharmony.assign(settings.disharmonyDeckTier2.begin(), settings.disharmonyDeckTier2.end());
        std::shuffle(temporaryDisharmony.begin(), temporaryDisharmony.end(), gen);
        disharmonyDeck.insert(disharmonyDeck.end(), temporaryDisharmony.begin(), temporaryDisharmony.end());
        temporaryDisharmony.clear();
        temporaryDisharmony.assign(settings.disharmonyDeckTier3.begin(), settings.disharmonyDeckTier3.end());
        std::shuffle(temporaryDisharmony.begin(), temporaryDisharmony.end(), gen);
        disharmonyDeck.insert(disharmonyDeck.end(), temporaryDisharmony.begin(), temporaryDisharmony.end());
        temporaryDisharmony.clear();
    }
    for(auto card: settings.harmonyDeck)
    {
        boost::random::uniform_int_distribution<> dist(0, harmonyDeck.size());

        std::list<boost::shared_ptr<HarmonyCard>>::iterator it = harmonyDeck.begin();
        for(int i = dist(gen); i > 0 and it != harmonyDeck.end(); --i, ++it){}
        harmonyDeck.insert(it, card);
    }
}
const std::vector<boost::shared_ptr<Player> >& Game::getEliminatedPlayers() const
{
    return eliminatedPlayers;
}
const std::vector<boost::shared_ptr<Player> >& Game::getPlayers() const
{
    return players;
}
const std::list<boost::shared_ptr<DisharmonyCard>> &Game::getDisharmonyDiscard() const
{
    return disharmonyDiscard;
}
const board::Board &Game::getBoard() const
{
    return board;
}
Game::Status Game::getStatus() const
{
    return status;
}

}}
