#pragma once

#include "TAKEnhancedDll/common.hpp"

#include "Utils/defs.h"
#include "ConfigFile.hpp"

#include "TAKEnhancedDll/Models/Command.hpp"
#include "TAKEnhancedDll/Models/Keys.hpp"

enum ShowHpOptions {
    SHOW_PLAYER          = 1,
    SHOW_ALLIES          = 2,
    SHOW_ENEMIES         = 4,
    SHOW_ONLY_IF_DAMAGED = 8
};
DEFINE_ENUM_FLAG_OPERATORS(ShowHpOptions);

class Settings
{
public:
    bool EnableDevMode = false;
    bool EnableMods = true;
    uint MaxUnits = 5000;
    uint PathFindingCycles = 100000;
    uint ForcedMinRangeForMelees = 40;
    bool NoCD = true;
    bool PauseWhenUnfocused = false;
    bool OffscreenFix = true;

    ShowHpOptions showHpOptions = SHOW_PLAYER | SHOW_ALLIES | SHOW_ENEMIES | SHOW_ONLY_IF_DAMAGED;

    bool MeleeStuckFix = true;

    std::vector<std::string> SelectedMods;

    std::unordered_map<Keys, Command, KeysHashFunction> keyBindings = {
        std::pair(Keys{ VK_1 }, Command(CommandCode::SELECT_BUILDING, "1")),
        std::pair(Keys{ VK_2 }, Command(CommandCode::SELECT_BUILDING, "2")),
        std::pair(Keys{ VK_3 }, Command(CommandCode::SELECT_BUILDING, "3")),
        std::pair(Keys{ VK_4 }, Command(CommandCode::SELECT_BUILDING, "4")),
        std::pair(Keys{ VK_5 }, Command(CommandCode::SELECT_BUILDING, "5")),
        std::pair(Keys{ VK_6 }, Command(CommandCode::SELECT_BUILDING, "6")),
        std::pair(Keys{ VK_7 }, Command(CommandCode::SELECT_BUILDING, "7")),
        std::pair(Keys{ VK_8 }, Command(CommandCode::SELECT_BUILDING, "8")),
        std::pair(Keys{ VK_9 }, Command(CommandCode::SELECT_BUILDING, "9")),
        std::pair(Keys{ VK_0 }, Command(CommandCode::SELECT_BUILDING, "10"))
    };

    std::map<std::string, std::any> props = {
        std::pair("EnableDevMode", &EnableDevMode),
        std::pair("EnableMods", &EnableMods),
        std::pair("MaxUnits", &MaxUnits),
        std::pair("PathFindingCycles", &PathFindingCycles),
        std::pair("ForcedMinRangeForMelees", &ForcedMinRangeForMelees),
        std::pair("NoCD", &NoCD),
        std::pair("PauseWhenUnfocused", &PauseWhenUnfocused),
        std::pair("OffscreenFix", &OffscreenFix),
        std::pair("MeleeStuckFix", &MeleeStuckFix)
    };

    Settings();

    void LoadSettings(std::string path);

    void loadProperty(std::string propName, std::string value);

    void loadKeyBindings(std::string& key, std::string& value);

    void Save();
};
