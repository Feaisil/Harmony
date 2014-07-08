#include "commandlineinterface.hpp"

namespace harmony{ namespace interface{

CommandLineInterface::CommandLineInterface()
{
}

void CommandLineInterface::getNumberOfPlayers()
{
    settings.numberOfPlayers = 3;
}
void CommandLineInterface::getPlayerSettings()
{
    boost::shared_ptr<harmony::core::PlayerSetting> playerSetting(new harmony::core::PlayerSetting(this));

    playerSetting->name = "Fanny";
    playerSetting->element = harmony::core::common::Element::Water;

    settings.playersSettings.push_back(playerSetting);
}

void CommandLineInterface::operator()()
{
    getNumberOfPlayers();

    for(int i=0; i<settings.numberOfPlayers; ++i)
    {
        getPlayerSettings();
    }
}

core::common::Element CommandLineInterface::choosePureHarmony(boost::shared_ptr<harmony::core::Player> & player) const
{
    std::cout << player->accessSettings().name << std::endl;
    short result;
    while(true)
    {
        std::cout << "Select element to play (1 Fire, 2 Wind, 3 Water, 4 Aether, 5 Earth):" << std::endl;
        std::cin >> result;
        switch(result)
        {
        case 1:
            return core::common::Element::Fire;
        case 2:
            return core::common::Element::Wind;
        case 3:
            return core::common::Element::Water;
        case 4:
            return core::common::Element::Aether;
        case 5:
            return core::common::Element::Earth;
        default:
            break;
        }
    }
    return core::common::Element::Fire;
}

}}
