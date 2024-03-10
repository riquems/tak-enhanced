#pragma once
#include "TAKEnhancedLibrary/common.hpp"

struct GameSetting
{
    bool enabled = false;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(GameSetting, enabled)
