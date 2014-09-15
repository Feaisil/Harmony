#include "eliminateplayers.hpp"
#include "core/game.hpp"

namespace harmony{ namespace core{ namespace events{
EliminatePlayers::EliminatePlayers(const boost::weak_ptr<Game>& game):
    Event(game)
{
}

void EliminatePlayers::trigger()
{
    boost::shared_ptr<Game> gameLock = game.lock();
    for(std::vector<boost::shared_ptr<Player>>::iterator it = gameLock->players.begin(); it < gameLock->players.end(); ++it)
    {
         if((*it)->getPosition().getIndex() >= gameLock->settings.boardSize)
         {
             gameLock->eliminatedPlayers.push_back(*it);
             it = gameLock->players.erase(it);
         }
    }
    if(gameLock->players.empty())
    {
        gameLock->status = Game::Status::lost;
    }
}

}}} // namespaces
