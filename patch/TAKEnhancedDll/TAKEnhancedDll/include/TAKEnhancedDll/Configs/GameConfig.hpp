#pragma once
#include "TAKEnhancedDll/common.hpp"
#include "GameSetting.hpp"
#include "CustomizableHpBarsSettings.hpp"

struct ModsSettings : GameSetting
{
    std::vector<std::string> selectedMods;
};

struct MeleeStuckFixSettings : GameSetting
{
    uint forcedMinRangeForMelees;
};

struct GameConfig
{
    GameSetting useMapScript;
    GameSetting skipLogo;
    GameSetting showNetworkStats;
    GameSetting disableCavedogVerification;
    GameSetting pretendNoExpansion;
    GameSetting fixCursor;
    GameSetting disableUiPreload;
    GameSetting noSideCulling;
    uint maxUnits;
    uint pathfindingCycles;
    GameSetting developerMode;
    ModsSettings mods;
    GameSetting noCD;
    GameSetting offscreenFix;
    GameSetting pauseWhenUnfocused;
    MeleeStuckFixSettings meleeStuckFix;
    CustomizableHpBarsSettings customizableHpBars;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    ModsSettings,
    enabled,
    selectedMods
)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    MeleeStuckFixSettings,
    enabled,
    forcedMinRangeForMelees
)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    GameConfig,
    useMapScript,
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
    customizableHpBars
)
