#pragma once

#include "TAKEnhancedDll/common.hpp"
#include "TAKEnhancedDll/Utils.hpp"

#include "GameDefs.h"
#include "Utils/defs.h"
#include "ConfigFile.hpp"

#include "TAKEnhancedDll/Models/Command.hpp"
#include "TAKEnhancedDll/Models/Keys.hpp"
#include "TAKEnhancedDll/Settings/PlayerOptions.h"
#include "TAKEnhancedDll/Settings/LauncherSettings.hpp"

extern std::unordered_map<ShowHpOption, std::string> showHpOptionToString;
extern std::unordered_map<std::string, ShowHpOption> stringToShowHpOption;

extern std::unordered_map<Color, std::string> colorToString;
extern std::unordered_map<std::string, Color> stringToColor;

extern std::unordered_map<HpColorMode, std::string> hpColorModeToString;
extern std::unordered_map<std::string, HpColorMode> stringToHpColorMode;

class Settings
{
public:
    LauncherSettings Launcher;

    bool EnableDevMode = false;
    bool EnableMods = true;
    uint MaxUnits = 5000;
    uint PathFindingCycles = 100000;
    uint ForcedMinRangeForMelees = 40;
    bool NoCD = true;
    bool PauseWhenUnfocused = false;
    bool OffscreenFix = true;

    HpOptions myHpOptions    = { SHOW_ONLY_IF_DAMAGED, HpColorOptions { MATCH_PLAYER_COLOR, BLUE } };
    HpOptions allyHpOptions  = { SHOW_ONLY_IF_DAMAGED, HpColorOptions { MATCH_PLAYER_COLOR, LIGHT_BLUE } };
    HpOptions enemyHpOptions = { SHOW_ONLY_IF_DAMAGED, HpColorOptions { MATCH_PLAYER_COLOR, RED } };

    bool MeleeStuckFix = false;

    std::vector<std::string> ShowHpOptions;
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
        std::pair("Width"                  , &Launcher.Width),
        std::pair("Height"                 , &Launcher.Height),
        std::pair("EnableDevMode"          , &EnableDevMode),
        std::pair("EnableMods"             , &EnableMods),
        std::pair("MaxUnits"               , &MaxUnits),
        std::pair("PathFindingCycles"      , &PathFindingCycles),
        std::pair("ForcedMinRangeForMelees", &ForcedMinRangeForMelees),
        std::pair("NoCD"                   , &NoCD),
        std::pair("PauseWhenUnfocused"     , &PauseWhenUnfocused),
        std::pair("OffscreenFix"           , &OffscreenFix),
        std::pair("MeleeStuckFix"          , &MeleeStuckFix)
    };

    std::string sectionBeingScanned;

    Settings();
    void initializeSettings();

    void LoadSettings(std::string path);

    void loadProperty(std::string propName, std::string value);

    void loadKeyBindings(std::string& key, std::string& value);
    void loadHpOptions(HpOptions& hpOption, std::string propName, std::string value);

    void Save();

    bool isSection(std::string str);
    std::string extractSectionName(std::string str);
};
