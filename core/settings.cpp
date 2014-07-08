#include "settings.hpp"

namespace harmony{ namespace core{

std::list<PlayerSetting> playersSettings;
short boardSize;
short distanceFromStart;
short numberOfPlayers;
bool isParallel;

short startingEnergy;
short maxEnergy;
short restEnergyRate;
short feedingEnergyRate;
short feedingBeverageCost;
short feedingMealCost;
short passiveEnergyResplenishmentRate;

short startingBeverage;
short maxBeverage;
short beverageProductionRate;
short beverageProductionEnergyCost;

short startingMeal;
short maxMeal;
short mealProductionRate;
short mealProductionEnergyCost;

Setting::Setting():
    isParallel(false),

    harmonyInHand(4),
    boardSize(5),
    distanceFromStart(2),
    numberOfPlayers(0),

    startingEnergy(3),
    maxEnergy(15),
    restEnergyRate(4),
    feedingEnergyRate(8),
    feedingBeverageCost(2),
    feedingMealCost(2),
    passiveEnergyResplenishmentRate(1),

    startingBeverage(1),
    maxBeverage(15),
    beverageProductionRate(5),
    beverageProductionEnergyCost(3),

    startingMeal(1),
    maxMeal(15),
    mealProductionRate(5),
    mealProductionEnergyCost(3),

    EofDisharmony(0)
{}

}}
