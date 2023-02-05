#pragma once
#include "TAKEnhancedDll/common.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"

struct Preset : public GameConfig
{
    std::string id;
    std::string name;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Preset, id, name, maxUnits, pathfindingCycles, developerMode,
    mods, noCD, offscreenFix, pauseWhenUnfocused, meleeStuckFix, customizableHpBars
)
