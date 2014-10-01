#pragma once

#include "core/interface/playerinterface.hpp"
#include "core/interface/settinginterface.hpp"


namespace harmony{ namespace core{
    class HarmonyCard;
    namespace events{
    class Event;
    }
}}

namespace harmony{ namespace interface{

class CommandLineInterface : public harmony::core::interface::PlayerInterface, public harmony::core::interface::SettingInterface
{
public:
    CommandLineInterface();
    virtual ~CommandLineInterface(){}
    void operator()();
    void displayFinalState() const;

    boost::shared_ptr<const harmony::core::Engine> engine;
 private:
    /** \addtogroup player interface pure virtual ilmplementation
     *  @{
     */
    core::interface::Action chooseAction(const boost::shared_ptr<harmony::core::Player> & player, const std::vector<boost::shared_ptr<core::HarmonyCard>> & harmonyHand);
    std::list<boost::shared_ptr<core::HarmonyCard>> chooseCard(const boost::shared_ptr<harmony::core::Player> & player, const std::vector<boost::shared_ptr<core::HarmonyCard>> & harmonyHand, core::interface::ChooseCardType type);
    core::common::Element chooseHarmoniousMealDirection(const boost::shared_ptr<harmony::core::Player> & player);
    boost::shared_ptr<core::events::PlayerEvent> chooseBetweenEvents(const boost::shared_ptr<harmony::core::Player> & player, std::vector<boost::shared_ptr<core::events::PlayerEvent>> & events);
    /** @}*/


    void getNumberOfPlayers();
    void getPlayerSettings();
    void configureSettings();
    void handleSettings();
    void displayBoard() const;
    void displayScore() const;
    void displayDisharmony() const;
};

}}
