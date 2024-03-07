#pragma once
#include "TAKEnhancedDll/common.hpp"
#include "TAKEnhancedDll/Configs/GameConfig.hpp"

struct Preset : public GameConfig
{
    std::string id;
    std::string name;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    Preset,
    id,
    name,
    testMultiScript,
    skipLogo,
    showNetworkStats,
    disableCavedogVerification,
    pretendNoExpansion,
    fixCursor,
    disableUiPreload,
    noSideCulling,
    maxUnits,
    pathfindingCycles,
    developerMode,
    mods,
    noCD,
    offscreenFix,
    pauseWhenUnfocused,
    meleeStuckFix,
    customizableHpBars,
    friendlyFire,
    modifiers
)
