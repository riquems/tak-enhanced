#pragma once
#include "TAKEnhancedDll/Common.hpp"

struct GameSetting
{
    bool enabled = false;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(GameSetting, enabled)
