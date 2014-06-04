#include "player.hpp"

namespace harmony{ namespace core{

Player::Player(const Setting &settings, const PlayerSetting &playersSettings):
    energy(settings.startingEnergy),
    beverage(settings.startingBeverage),
    meal(settings.startingMeal),
    score(0),
    settings(playersSettings)
{
}

}} // namespaces
