#include "player.hpp"

namespace harmony{ namespace core{

PlayerSetting::PlayerSetting(interface::PlayerInterface *interface):
    interface(interface)
{

}

Player::Player(const Setting &settings, const PlayerSetting &playersSettings):
    energy(settings.startingEnergy),
    beverage(settings.startingBeverage),
    meal(settings.startingMeal),
    score(0),
    settings(playersSettings)
{
}
const board::Position& Player::getPosition() const
{
    return position;
}

}} // namespaces
