#include "checkforendconditions.hpp"
#include "core/game.hpp"
#include "core/player.hpp"

namespace harmony{ namespace core{ namespace events{
CheckForEndConditions::CheckForEndConditions(const boost::weak_ptr<Game>& game):
    Event(game)
{
}

void CheckForEndConditions::trigger()
{
    boost::shared_ptr<Game> gameLock = game.lock();
    for(std::vector<boost::shared_ptr<Player>>::iterator it = gameLock->players.begin(); it < gameLock->players.end(); ++it)
    {
         if((*it)->getPosition().getIndex() >= gameLock->settings.boardSize)
         {
             gameLock->eliminatedPlayers.push_back(*it);
             it = gameLock->players.erase(it);
         }
         (*it)->energy = std::min(gameLock->settings.maxEnergy, (*it)->energy + 1);
    }
    if(gameLock->players.empty())
    {
        gameLock->status = Game::Status::lost;
    }

    if(gameLock->getBoard().getBalancePoint().getIndex() >= gameLock->settings.boardSize)
    {
        gameLock->status = Game::Status::lost;
    }
    else if(gameLock->disharmonyDeck.empty())
    {
        gameLock->status = Game::Status::finished;
    }
}

}}} // namespaces
