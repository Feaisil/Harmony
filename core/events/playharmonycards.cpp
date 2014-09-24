#include "playharmonycards.hpp"
#include "core/game.hpp"
#include "core/player.hpp"
#include "core/turn.hpp"

namespace harmony{ namespace core{ namespace events{

PlayHarmonyCards::PlayHarmonyCards(const boost::weak_ptr<Game> &game, Turn& turn):
    Event(game),
    turn(turn)
{

}

void PlayHarmonyCards::trigger()
{
    boost::shared_ptr<Event> event;
    for(auto values: events)
    {
        event = boost::static_pointer_cast<Event>(values.second);
        turn << event;
    }
}

void PlayHarmonyCards::add(boost::weak_ptr<Player> player, std::list<boost::shared_ptr<HarmonyCard> > &cards)
{
    auto playerLock = player.lock();
    auto gameLock = game.lock();
    for(auto card: cards)
    {
        for(auto event: card->events)
        {
            //<priority, boost::shared_ptr<PlayerEvent>>
            event->game = game;
            event->player = player;
            events.insert(std::make_pair(card->getPriority(), event));
        }
        gameLock->harmonyDiscard.push_back(card);
        auto position = std::find(playerLock->harmonyHand.begin(), playerLock->harmonyHand.end(),card);
        if(position != playerLock->harmonyHand.end())
        {
            playerLock->harmonyHand.erase(position);
        }
        playerLock->energy -= card->getEnergyCost();
        playerLock->beverage -= card->getBeverageCost();
        playerLock->meal -= card->getMealCost();
    }
    for(size_t i = playerLock->harmonyHand.size(); i < size_t(gameLock->settings.harmonyInHand) and not gameLock->harmonyDeck.empty(); ++i)
    {
        playerLock->harmonyHand.push_back(gameLock->harmonyDeck.front());
        gameLock->harmonyDeck.pop_front();
    }
}

}}}
