#include "commandlineinterface.hpp"
#include "core/engine.hpp"

namespace harmony{ namespace interface{

CommandLineInterface::CommandLineInterface()
{
}

void CommandLineInterface::getNumberOfPlayers()
{
    settings.numberOfPlayers = 0;
    while(settings.numberOfPlayers < 1 or settings.numberOfPlayers > 5)
    {
        std::cout << "Select the number of players (1-5)" << std::endl;
        std::cin >> settings.numberOfPlayers;
    }
}
void CommandLineInterface::getPlayerSettings()
{
    boost::shared_ptr<harmony::core::PlayerSetting> playerSetting(new harmony::core::PlayerSetting(this));

    while(playerSetting->name.empty())
    {
        std::cout << "Choose player's name:" << std::endl;
        std::cin >> playerSetting->name;
    }
    short chosenElement = 0;
    while(chosenElement == 0)
    {
        std::cout << "Choose player's element (1 Fire, 2 Wind, 3 Water, 4 Aether, 5 Earth):" << std::endl;
        std::cin >> chosenElement;
        switch(chosenElement )
        {
        case 1:
            playerSetting->element = core::common::Element::Fire;
            break;
        case 2:
            playerSetting->element = core::common::Element::Wind;
            break;
        case 3:
            playerSetting->element = core::common::Element::Water;
            break;
        case 4:
            playerSetting->element = core::common::Element::Aether;
            break;
        case 5:
            playerSetting->element = core::common::Element::Earth;
            break;
        default:
            chosenElement = 0;
        }
        for(auto player: settings.playersSettings)
        {
            if(player->element == playerSetting->element)
            {
                chosenElement = 0;
                std::cout << "Element already chosen by player " << player->name << "." << std::endl;
            }
        }
    }

    settings.playersSettings.push_back(playerSetting);
}

void CommandLineInterface::handleSettings()
{
    std::cout << "Loading saved settings" << std::endl;
    if(not settings.load())
    {
        std::cout << "Failed to load settings file, using default!" << std::endl;
        std::string result;
        std::cout << "Do you want to create a new config file? (Yy)" << std::endl;
        std::cin >> result;
        if(result == "y" or result == "Y")
        {
            if(settings.save())
            {
                std::cout << "Successfully saved configuration file " << settings.defaultFilePath << std::endl;
            }
            else
            {
                std::cout << "Could not save configuration file " << settings.defaultFilePath << std::endl;
            }
        }
    }
}

void CommandLineInterface::operator()()
{
    handleSettings();
    getNumberOfPlayers();

    for(int i=0; i<settings.numberOfPlayers; ++i)
    {
        getPlayerSettings();
    }
}

core::common::Element CommandLineInterface::choosePureHarmony(boost::shared_ptr<harmony::core::Player> & player) const
{
    displayBoard();
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

void CommandLineInterface::displayBoard() const
{
    static const int spacing = 2;
    static const std::string nodeChar("O"),spacingChar("*"), emptyChar(" ");
    std::cout << "Game board:"<<std::endl;
    for(int i = 0; i < settings.boardSize * 2 * spacing; ++i)
    {
        std::cout << "=";
    }
    std::cout << std::endl;
    for(int i = 0; i < settings.boardSize * 2 * spacing; ++i)
    {
        for(int j = 0; j < settings.boardSize * 2 * spacing; ++j)
        {
            // direction north, fire
            if( (j == settings.boardSize * spacing) and (i > settings.boardSize * spacing))
            {
                if(j % spacing == 0)
                {
                    std::cout << nodeChar;
                }
                else
                {
                    bool playerFound = false;
                    for(auto player:engine->getGame().getPlayers())
                    {
                        if(player->getPosition().getDirection() == harmony::core::board::Position::Direction::Fire
                                and player->getPosition().getIndex() == i/spacing)
                        {
                            std::cout << player->accessSettings().name.empty()? "X": player->accessSettings().name.substr(0,1);
                            playerFound = true;
                        }
                    }
                    if(not playerFound)
                    {
                        engine->getGame().getBoard().getBalancePoint().getDirection() == harmony::core::board::Position::Direction::Fire;
                        std::cout << spacingChar;
                    }
                }
            }/*
            else
            {
                std::cout << emptyChar;
            }*/
        }
        std::cout << std::endl;
    }

    for(int i = 0; i < settings.boardSize * 2 * spacing; ++i)
    {
        std::cout << "=";
    }
    std::cout << std::endl;
}

}}
