#pragma once

#include "core/interface/playerinterface.hpp"
#include "core/interface/settinginterface.hpp"
namespace harmony{ namespace core{
    class engine;
}}

namespace harmony{ namespace interface{

class CommandLineInterface : public harmony::core::interface::PlayerInterface, public harmony::core::interface::SettingInterface
{
public:
    CommandLineInterface();

    /** \addtogroup Configuration IHM
     *  @{
     */
    void getNumberOfPlayers();
    void getPlayerSettings();
    void configureSettings();
    void handleSettings();
    /** @}*/

    void operator()();

    /** \addtogroup player IHM
     *  @{
     */
    core::common::Element choosePureHarmony(boost::shared_ptr<harmony::core::Player> & player) const;
    void displayBoard() const;
    /** @}*/

    boost::shared_ptr<const harmony::core::Engine> engine;

};

}}
