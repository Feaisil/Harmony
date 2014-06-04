#pragma once

#include "core/interface/playerinterface.hpp"
#include "core/interface/settinginterface.hpp"

namespace harmony{ namespace interface{

class CommandLineInterface : public harmony::core::interface::PlayerInterface, public harmony::core::interface::SettingInterface
{
public:
    CommandLineInterface();
};

}}
