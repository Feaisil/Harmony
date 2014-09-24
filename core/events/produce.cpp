#include "produce.hpp"

#include "core/player.hpp"
#include "core/game.hpp"

namespace harmony{ namespace core{ namespace events{
Produce::Produce(const boost::weak_ptr<Game> &game, const boost::weak_ptr<Player> &player, ProduceType type):
    PlayerEvent(game,player), type(type)
{
}

void Produce::trigger()
{
    boost::shared_ptr<Player> playerLock = player.lock();
    boost::shared_ptr<Game> gameLock = game.lock();

    switch(type)
    {
    case ProduceType::Beverage:
        if(playerLock->energy >= gameLock->settings.beverageProductionEnergyCost)
        {
            int countSharedOther = std::count(gameLock->modifiers.begin(), gameLock->modifiers.end(), Modifier::ProduceMoreBeverageShared);
            int countShared = std::count(playerLock->modifiers.begin(), playerLock->modifiers.end(), Modifier::ProduceMoreBeverageShared);
            int countPersonal = std::count(playerLock->modifiers.begin(), playerLock->modifiers.end(), Modifier::ProduceMoreBeveragePersonal);
            countSharedOther -= countShared;

            playerLock->energy = playerLock->energy - gameLock->settings.beverageProductionEnergyCost;
            playerLock->beverage = std::min(gameLock->settings.maxBeverage, playerLock->beverage + gameLock->settings.beverageProductionRate + countSharedOther*gameLock->settings.beverageProductionBonusSharedOther + countShared*gameLock->settings.beverageProductionBonusShared + countPersonal*gameLock->settings.beverageProductionBonusPersonal);
        }
        break;
    case ProduceType::Meal:
        if(playerLock->energy >= gameLock->settings.mealProductionEnergyCost)
        {
            int countSharedOther = std::count(gameLock->modifiers.begin(), gameLock->modifiers.end(), Modifier::ProduceMoreMealShared);
            int countShared = std::count(playerLock->modifiers.begin(), playerLock->modifiers.end(), Modifier::ProduceMoreMealShared);
            int countPersonal = std::count(playerLock->modifiers.begin(), playerLock->modifiers.end(), Modifier::ProduceMoreMealPersonal);
            countSharedOther -= countShared;

            playerLock->energy = playerLock->energy - gameLock->settings.mealProductionEnergyCost;
            playerLock->meal = std::min(gameLock->settings.maxMeal, playerLock->meal + gameLock->settings.mealProductionRate + countSharedOther*gameLock->settings.mealProductionBonusSharedOther + countShared*gameLock->settings.mealProductionBonusShared + countPersonal*gameLock->settings.mealProductionBonusPersonal);
        }
        break;
    case ProduceType::Rest:
        {
            int countPersonal = std::count(gameLock->modifiers.begin(), gameLock->modifiers.end(), Modifier::RestProduceMoreEnergyPersonal);


            playerLock->energy = std::min(gameLock->settings.maxEnergy, playerLock->energy + gameLock->settings.restEnergyRate + countPersonal * gameLock->settings.restBonus );
        }
        break;
    case ProduceType::Eat:
        if(playerLock->meal >= gameLock->settings.feedingMealCost and playerLock->beverage >= gameLock->settings.feedingBeverageCost)
        {
            int countPersonal = std::count(playerLock->modifiers.begin(), playerLock->modifiers.end(), Modifier::EatProduceMoreEnergyPersonal);

            playerLock->meal = playerLock->meal - gameLock->settings.feedingMealCost;
            playerLock->beverage = playerLock->beverage - gameLock->settings.feedingBeverageCost;
            playerLock->energy = std::min(gameLock->settings.maxEnergy, playerLock->energy + gameLock->settings.feedingEnergyRate + countPersonal * gameLock->settings.feedingBonus);
        }
        break;
    default:
        break;
    }
}
}}}
