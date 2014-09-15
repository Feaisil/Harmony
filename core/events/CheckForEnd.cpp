#include "drawdisharmony.hpp"
#include "core/game.hpp"
#include "core/turn.hpp"

namespace harmony{ namespace core{ namespace events{
DrawDisharmony::DrawDisharmony(const boost::weak_ptr<Game>& game, Turn &turn):
    Event(game),
    turn(turn)
{
}

void DrawDisharmony::trigger()
{
    boost::shared_ptr<Game> gameLock = game.lock();
    for(int i = 0; i < gameLock->settings.disharmonyDraw and not gameLock->disharmonyDeck.empty(); ++i)
    {
        boost::shared_ptr<DisharmonyCard> card = gameLock->disharmonyDeck.front();
        gameLock->disharmonyDeck.pop_front();
        gameLock->disharmonyDiscard.push_back(card);
        for(auto event: card->events)
        {
            event->game = game;
            turn << event;
        }
    }
}

}}} // namespaces
