#include "chooseaction.hpp"
#include "harmoniousmeal.hpp"
#include "produce.hpp"
#include "playharmonycards.hpp"

#include "core/turn.hpp"
#include "core/player.hpp"
#include "core/element.hpp"
#include "core/game.hpp"
#include "core/modifier.hpp"

namespace harmony{ namespace core{ namespace events{

struct DoChooseAction
{
    struct Args
    {

    };
    struct ResultType
    {
        ResultType(): action(interface::Action::Rest), direction(common::Element::Aether){}

        interface::Action action;
        std::list<boost::shared_ptr<HarmonyCard> > cards;
        common::Element direction;
    };

    typedef Args _argumentType;
    typedef ResultType _returnType;

    _returnType operator()(boost::shared_ptr<Player> & player, _argumentType& args) const
    {
        (void) args;
        _returnType result;
        bool valid = false;
        while(not valid)
        {
            result.action = player->accessSettings().interface->chooseAction(player, player->harmonyHand);
            switch(result.action)
            {
            case interface::Action::PlayHarmonyCards:
                result.cards = player->accessSettings().interface->chooseCard(player, player->harmonyHand, interface::ChooseCardType::PlayHarmony);
                valid = canPlayCards(result, player);
                break;
            case interface::Action::ReplaceHarmonyCards:
                result.cards = player->accessSettings().interface->chooseCard(player, player->harmonyHand, interface::ChooseCardType::ReplaceHarmony);
                valid = hasCards(result, player);
                break;
            case interface::Action::HarmoniousMeal:
                result.direction = player->accessSettings().interface->chooseHarmoniousMealDirection(player);
                valid = canPlayHarmoniousMeal(player);
                break;

            default:
                valid = true;
                break;
            }
        }

        return result;
    }

private:
    bool hasCards(const _returnType& result, boost::shared_ptr<Player> & player) const
    {
        for( const boost::shared_ptr<HarmonyCard> &card: result.cards)
        {
            if(std::find(player->harmonyHand.begin(), player->harmonyHand.end(), card) == player->harmonyHand.end())
            {
                return false;
            }
        }
        return true;
    }
    bool canPlayCards(const _returnType& result, boost::shared_ptr<Player> & player) const
    {
        if(not hasCards(result, player))
        {
            return false;
        }
        int beverageCost = 0, mealCost = 0, energyCost = 0;
        for(boost::shared_ptr<HarmonyCard> card: result.cards)
        {
            beverageCost += card->getBeverageCost();
            mealCost += card->getMealCost();
            energyCost += card->getEnergyCost();
        }
        return beverageCost <= player->getBeverage() and mealCost <= player->getMeal() and energyCost <= player->getEnergy();
    }
    bool canPlayHarmoniousMeal(boost::shared_ptr<Player> & player) const
    {
        return std::find(player->modifiers.begin(), player->modifiers.end(), Modifier::AddHarmoniousMealAction) != player->modifiers.end();
    }
};

ChooseAction::ChooseAction(const boost::weak_ptr<Game>& game, Turn &turn):
    Event(game),
    turn(turn)
{

}

void ChooseAction::trigger()
{
    boost::shared_ptr<Game> gameLock = game.lock();
    SimultaneousQuery<DoChooseAction> query (gameLock->settings.isParallel);
    DoChooseAction::Args args;

    std::vector<typename DoChooseAction::_returnType> result = query(gameLock->players, args);

    boost::shared_ptr<Event> event;

    boost::shared_ptr<PlayHarmonyCards> playHarmonyCardEvent(new PlayHarmonyCards(game, turn));

    for(size_t index = 0; index < gameLock->players.size(); ++index)
    {

        switch(result.at(index).action)
        {
        case interface::Action::PlayHarmonyCards:
            playHarmonyCardEvent->add(boost::weak_ptr<Player>(gameLock->players.at(index)), result.at(index).cards);
            break;
        case interface::Action::ReplaceHarmonyCards:
            for(auto card: result.at(index).cards)
            {
                gameLock->harmonyDiscard.push_back(card);
                auto position = std::find(gameLock->players.at(index)->harmonyHand.begin(), gameLock->players.at(index)->harmonyHand.end(),card);
                if(position != gameLock->players.at(index)->harmonyHand.end())
                {
                    gameLock->players.at(index)->harmonyHand.erase(position);
                }
            }
            for(size_t i = gameLock->players.at(index)->harmonyHand.size(); i < size_t(gameLock->settings.harmonyInHand) and not gameLock->harmonyDeck.empty(); ++i)
            {
                gameLock->players.at(index)->harmonyHand.push_back(gameLock->harmonyDeck.front());
                gameLock->harmonyDeck.pop_front();
            }
            break;
        case interface::Action::ProduceBeverage:
            event.reset(new Produce(game, gameLock->players.at(index), ProduceType::Beverage));
            turn << event;
            break;
        case interface::Action::ProduceMeal:
            event.reset(new Produce(game, gameLock->players.at(index), ProduceType::Meal));
            turn << event;
            break;
        case interface::Action::Rest:
            event.reset(new Produce(game, gameLock->players.at(index), ProduceType::Rest));
            turn << event;
            break;
        case interface::Action::Eat:
            event.reset(new Produce(game, gameLock->players.at(index), ProduceType::Eat));
            turn << event;
            break;
        case interface::Action::HarmoniousMeal:
            event.reset(new HarmoniousMeal(game, gameLock->players.at(index), result.at(index).direction));
            turn << event;
            break;
        default:
            break;
        }
    }
    event = boost::static_pointer_cast<Event>(playHarmonyCardEvent);
    turn << event;
}

}}} // namespaces
