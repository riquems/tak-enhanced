#pragma once
#include "TAKEnhancedDll/Common.hpp"

struct GameSetting
{
    bool enabled;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameSetting, enabled)
