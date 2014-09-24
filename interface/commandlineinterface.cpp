#include "commandlineinterface.hpp"
#include "core/engine.hpp"
#include "core/disharmonycard.hpp"
#include "core/harmonycard.hpp"

namespace harmony{ namespace interface{

void displayPlayer(const std::string & name, const core::board::Position& position)
{
    std::cout << " - " << name << " @ " ;
    switch(position.getDirection())
    {
    case harmony::core::board::Position::Direction::Fire:
            std::cout << "Fire";
            break;
    case harmony::core::board::Position::Direction::FireWind:
            std::cout << "Fire-Wind";
            break;
    case harmony::core::board::Position::Direction::Wind :
        std::cout << "Wind";
        break;
    case harmony::core::board::Position::Direction::WindWater :
        std::cout << "Wind-Water";
        break;
    case harmony::core::board::Position::Direction::Water :
        std::cout << "Water";
        break;
    case harmony::core::board::Position::Direction::WaterAether :
        std::cout << "Water-Aether";
        break;
    case harmony::core::board::Position::Direction::Aether :
        std::cout << "Aether";
        break;
    case harmony::core::board::Position::Direction::AetherEarth :
        std::cout << "Aether-Earth";
        break;
    case harmony::core::board::Position::Direction::Earth :
        std::cout << "Earth";
        break;
    case harmony::core::board::Position::Direction::EarthFire :
        std::cout << "Earth-Fire";
        break;
    case harmony::core::board::Position::Direction::Center :
    default:
        std::cout << "Center";
    }
    std::cout << "[" << position.getIndex() << "] " ;
}
void displayPlayer(const std::string & name, const core::board::Position& position, int beverages, int meals, int energies, const std::vector<core::Modifier> modifiers)
{
    displayPlayer(name, position);
    std::cout << "{ " << beverages << " beverages, "  << meals << " meals, " << energies << " energies }" << std::endl;
    if(not modifiers.empty())
    {
        std::cout << "   Modifiers: ";
        for(core::Modifier modifier: modifiers)
        {
            std::cout << "[";
            switch(modifier)
            {
                case core::Modifier::AddHarmoniousMealAction:
                    std::cout << "Add action Harmonious Meal";
                    break;
                default:
                    std::cout << "Unknown";
                    break;
            }
            std::cout << "] ";
        }
        std::cout << std::endl;
    }
}
void displayPlayer(const boost::shared_ptr<harmony::core::Player> & player)
{

    displayPlayer(player->accessSettings().name, player->getPosition(), player->getBeverage(), player->getMeal(), player->getEnergy(), player->getModifiers());

    // display other players stuff
}

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
        std::cout << "========================" << std::endl
                     << "- " << i << std::endl;
        getPlayerSettings();
    }
}

void CommandLineInterface::displayFinalState() const
{
    std::cout << "========================" << std::endl
        << "= End of game =" << std::endl
        << "========================" << std::endl;
    displayBoard();
    switch(engine->getGame().getStatus())
    {
    case core::Game::Status::lost:
        std::cout << "Game lost!" << std::endl;
        break;
    case core::Game::Status::finished:
        std::cout << "Game finished!" << std::endl;
        displayScore();
        break;
    case core::Game::Status::ongoing:
        std::cout << "Game ongoin..." << std::endl;
        break;
    default:break;

    }

}
core::interface::Action CommandLineInterface::chooseAction(const boost::shared_ptr<harmony::core::Player> & player, const std::vector<boost::shared_ptr<core::HarmonyCard>> & harmonyHand) const
{
    (void) player;
    std::cout << "========================" << std::endl;
    displayBoard();
    std::cout << "========================" << std::endl;
    std::cout << "Current player: " << std::endl;
    displayPlayer(player);
    std::cout << "Hand: " << std::endl;
    for(size_t i = 1; i <= harmonyHand.size(); ++i)
    {
        std::cout << " - " << i << " : " << harmonyHand.at(i-1)->getName() << "{ Priority: "<< harmonyHand.at(i-1)->getPriority() << ", Costs: " << harmonyHand.at(i-1)->getBeverageCost() << " beverages, "  << harmonyHand.at(i-1)->getMealCost() << " meals, " << harmonyHand.at(i-1)->getEnergyCost() << " energies }" << std::endl;
    }
    std::cout << "========================" << std::endl;
    short result;
    while(true)
    {
        std::cout << "Choose action to play: "<< std::endl
                  << " - 1 Play Harmony" << std::endl
                  << " - 2 Replace Harmony cards" << std::endl
                  << " - 3 Produce beverage" << std::endl
                  << " - 4 Produce meal" << std::endl
                  << " - 5 Rest" << std::endl
                  << " - 6 Feast" << std::endl;
        if(std::find(player->getModifiers().begin(), player->getModifiers().end(), core::Modifier::AddHarmoniousMealAction) != player->getModifiers().end())
        {
            std::cout << " - 7 Harmonious meal" << std::endl;
        }
        std::cin >> result;
        switch(result)
        {
        case 1:
            return core::interface::Action::PlayHarmonyCards;
        case 2:
            return core::interface::Action::ReplaceHarmonyCards;
        case 3:
            return core::interface::Action::ProduceBeverage;
        case 4:
            return core::interface::Action::ProduceMeal;
        case 5:
            return core::interface::Action::Rest;
        case 6:
            return core::interface::Action::Eat;
        case 7:
            if(std::find(player->getModifiers().begin(), player->getModifiers().end(), core::Modifier::AddHarmoniousMealAction) != player->getModifiers().end())
            {
                return core::interface::Action::HarmoniousMeal;
            }
        default:
            break;
        }
    }
    return core::interface::Action::Rest;
}
std::list<boost::shared_ptr<core::HarmonyCard>> CommandLineInterface::chooseCard(const boost::shared_ptr<harmony::core::Player> & player, const std::vector<boost::shared_ptr<core::HarmonyCard>> & harmonyHand, core::interface::ChooseCardType type) const
{
    std::list<boost::shared_ptr<core::HarmonyCard>> cards;
    std::cout << "========================" << std::endl;
    displayBoard();
    std::cout << "========================" << std::endl;
    displayPlayer(player);

    size_t result;
    while(true)
    {
        switch(type)
        {
        case core::interface::ChooseCardType::PlayHarmony:
            std::cout << "Choose card to play (0 to stop): "<< std::endl;
            break;
        case core::interface::ChooseCardType::ReplaceHarmony:
            std::cout << "Choose card to replace (0 to stop): "<< std::endl;
            break;
        default:
            break;
        }

        for(size_t i = 1; i <= harmonyHand.size(); ++i)
        {
            if(std::find(cards.begin(), cards.end(), harmonyHand.at(i - 1)) == cards.end())
            {
                std::cout << " - " << i << " : " << harmonyHand.at(i-1)->getName() << "{ Priority: "<< harmonyHand.at(i-1)->getPriority() << ", Costs: " << harmonyHand.at(i-1)->getBeverageCost() << " beverages, "  << harmonyHand.at(i-1)->getMealCost() << " meals, " << harmonyHand.at(i-1)->getEnergyCost() << " energies }" << std::endl;
            }
            else
            {
                std::cout << " - " << i << " : [Selected] " << harmonyHand.at(i-1)->getName() << "{ Priority: "<< harmonyHand.at(i-1)->getPriority() << ", Costs: " << harmonyHand.at(i-1)->getBeverageCost() << " beverages, "  << harmonyHand.at(i-1)->getMealCost() << " meals, " << harmonyHand.at(i-1)->getEnergyCost() << " energies }" << std::endl;
            }
        }
        std::cin >> result;
        if(result <= harmonyHand.size() and result > 0)
        {
            if(std::find(cards.begin(), cards.end(), harmonyHand.at(result - 1)) == cards.end())
            {
                cards.push_back(harmonyHand.at(result - 1));
            }
            else
            {
                cards.remove(harmonyHand.at(result - 1));
            }
        }
        if(result == 0)
        {
            return cards;
        }
    }
    return cards;
}

core::common::Element CommandLineInterface::chooseHarmoniousMealDirection(const boost::shared_ptr<harmony::core::Player> & player) const
{
    std::cout << "========================" << std::endl;
    displayBoard();
    std::cout << "========================" << std::endl;
    displayPlayer(player);

    short result;
    while(true)
    {
        std::cout << "Select element to play for Harmonious meal (1 Fire, 2 Wind, 3 Water, 4 Aether, 5 Earth):" << std::endl;
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
boost::shared_ptr<core::events::PlayerEvent> CommandLineInterface::chooseBetweenEvents(const boost::shared_ptr<harmony::core::Player> & player, std::vector<boost::shared_ptr<core::events::PlayerEvent>> & events) const
{

    boost::shared_ptr<core::events::PlayerEvent> event;
    std::cout << "========================" << std::endl;
    displayBoard();
    std::cout << "========================" << std::endl;
    displayPlayer(player);

    size_t result;
    while(true)
    {
        std::cout << "Choose event to play: "<< std::endl;

        for(size_t i = 1; i <= events.size(); ++i)
        {
            std::cout << " - " << i << " : " << typeid(*events.at(i-1)).name() << std::endl;
        }
        std::cin >> result;
        if(result <= events.size() and result > 0)
        {
            event = events.at(result - 1);
            return event;
        }
    }
    return event;
}
void CommandLineInterface::displayBoard() const
{
    displayDisharmony();

    std::cout << "Game board:"  <<std::endl;

    std::cout << "Size = " << settings.boardSize << std::endl;
    displayPlayer("Balance point", engine->getGame().getBoard().getBalancePoint());
    std::cout << std::endl;
    if(not engine->getGame().getEliminatedPlayers().empty())
    {
        std::cout << "Eliminated players: " << std::endl;
        for(auto player: engine->getGame().getEliminatedPlayers())
        {
            displayPlayer(player->accessSettings().name, player->getPosition());
            std::cout << std::endl;
        }
    }
    if(not engine->getGame().getPlayers().empty())
    {
        std::cout << "Players: "<< std::endl;
        for(auto player: engine->getGame().getPlayers())
        {
            displayPlayer(player);
        }
    }
    std::cout << std::endl;
}
void CommandLineInterface::displayScore() const
{
    if(not engine->getGame().getEliminatedPlayers().empty())
    {
        std::cout << "Eliminated players: " << std::endl;
        for(auto player: engine->getGame().getEliminatedPlayers())
        {
            std::cout << " - " << player->accessSettings().name << std::endl;
        }
    }
    if(not engine->getGame().getPlayers().empty())
    {
        std::cout << "Winning players scores: " << std::endl;
        for(auto player: engine->getGame().getPlayers())
        {
            std::cout << "Player " << player->accessSettings().name << " : " << engine->getGame().getBoard().ComputeScore(player->getPosition()) << std::endl;
        }
    }
}
void CommandLineInterface::displayDisharmony() const
{
    std::cout << "last disharmony: " << std::endl;
    int i = 0;
    for( std::list<boost::shared_ptr<core::DisharmonyCard>>::const_reverse_iterator it = engine->getGame().getDisharmonyDiscard().rbegin(); it != engine->getGame().getDisharmonyDiscard().rend() and i < settings.disharmonyDraw; ++it, ++i )
    {
        std::cout << (*it)->getName() << std::endl;
    }
}
}}
