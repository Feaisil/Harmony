#pragma once

#include "core/interface/playerinterface.hpp"
#include "core/interface/settinginterface.hpp"


namespace harmony{ namespace core{
    class engine;
    class disharmonycard;
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
    /** \addtogroup player IHM
     *  @{
     */
    core::common::Element choosePureHarmony(boost::shared_ptr<harmony::core::Player> & player) const;

    void getNumberOfPlayers();
    void getPlayerSettings();
    void configureSettings();
    void handleSettings();
    void displayBoard() const;
    void displayScore() const;
    void displayDisharmony() const;
    /** @}*/
};

}}
