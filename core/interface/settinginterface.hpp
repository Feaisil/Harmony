#pragma once

#include "core/settings.hpp"

namespace harmony{ namespace core{ namespace interface{

class SettingInterface
{
public:
    SettingInterface();
private:
    harmony::core::Setting settings;
};

}}}
