#pragma once
#include "TAKEnhancedDll/common.hpp"
#include "GameSetting.hpp"
#include "CustomizableHpBarsSettings.hpp"
#include "TAKEnhancedDll/Configs/ModifiersSettings.hpp"
#include "TAKEnhancedDll/Configs/FriendlyFireSettings.hpp"

struct ModsSettings : GameSetting
{
    bool enabled = true;
    std::vector<std::string> selectedMods = {
        "TAK Enhanced.hpi",
        "3D Models Fix.hpi",
        "Aimtolerance Fix.hpi",
        "Colorful HP Bars.hpi",
        "Elsin Fix.hpi",
        "Fire Mage Fix.hpi",
        "Guided Weapons Fix.hpi",
        "Kirenna Fix.hpi",
        "Melees Stuck Fix.hpi",
        "Misspellings Fix.hpi",
        "Paralyze Fix.hpi",
        "Weapons Swap Tweak.hpi",
        "Wisp Fix.hpi"
    };
};

struct MeleeStuckFixSettings : GameSetting
{
    bool enabled = true;
    uint forcedMinRangeForMelees = 40;
};

struct GameConfig
{
    GameSetting testMultiScript;
    GameSetting skipLogo;
    GameSetting showNetworkStats;
    GameSetting disableCavedogVerification;
    GameSetting pretendNoExpansion;
    GameSetting fixCursor;
    GameSetting disableUiPreload;
    GameSetting noSideCulling;
    uint maxUnits = 5000;
    uint pathfindingCycles = 100000;
    GameSetting developerMode;
    ModsSettings mods;
    GameSetting noCD = GameSetting { .enabled = true };
    GameSetting offscreenFix = GameSetting { .enabled = true };
    GameSetting pauseWhenUnfocused;
    MeleeStuckFixSettings meleeStuckFix;
    CustomizableHpBarsSettings customizableHpBars;
    FriendlyFireSettings friendlyFire;
    ModifiersSettings modifiers;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    ModsSettings,
    enabled,
    selectedMods
)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    MeleeStuckFixSettings,
    enabled,
    forcedMinRangeForMelees
)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    GameConfig,
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
