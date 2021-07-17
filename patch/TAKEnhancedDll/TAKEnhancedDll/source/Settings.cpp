#pragma once

#include "TAKEnhancedDll/Settings.hpp"

template <typename T1, typename T2>
std::unordered_map<T2, T1> build_reversed_map(const std::unordered_map<T1, T2>& map1)
{
    std::unordered_map<T2, T1> map2;

    std::for_each(map1.begin(), map1.end(), [&](std::pair<T1, T2> elem) {
        map2.insert(std::pair<T2, T1>(elem.second, elem.first));
        });

    return map2;
}

std::unordered_map<ShowHpOption, std::string> showHpOptionToString = {
    std::pair(ALWAYS_SHOW         , "Always"),
    std::pair(NEVER_SHOW          , "Never"),
    std::pair(SHOW_ONLY_IF_DAMAGED, "Only If Damaged"),
};
std::unordered_map<std::string, ShowHpOption> stringToShowHpOption;

std::unordered_map<Color, std::string> colorToString = {
    std::pair(LIGHT_BLUE, "Light Blue"),
    std::pair(RED       , "Red"),
    std::pair(WHITE     , "White"),
    std::pair(GREEN     , "Green"),
    std::pair(BLUE      , "Blue"),
    std::pair(PURPLE    , "Purple"),
    std::pair(YELLOW    , "Yellow"),
    std::pair(BLACK     , "Black"),
    std::pair(ORANGE    , "Orange"),
    std::pair(BROWN     , "Brown")
};
std::unordered_map<std::string, Color> stringToColor;

std::unordered_map<HpColorMode, std::string> hpColorModeToString = {
    std::pair(ORIGINAL          , "Original"),
    std::pair(MATCH_PLAYER_COLOR, "Match Player Color"),
    std::pair(FIXED_COLOR       , "Fixed")
};
std::unordered_map<std::string, HpColorMode> stringToHpColorMode;

Settings::Settings() {}

void Settings::initializeSettings()
{
    stringToShowHpOption = build_reversed_map(showHpOptionToString);
    stringToColor        = build_reversed_map(colorToString);
    stringToHpColorMode  = build_reversed_map(hpColorModeToString);
}

void Settings::LoadSettings(std::string path)
{
    std::fstream cfgFile(path);
        
    if (cfgFile.is_open())
    {
        while (cfgFile.good())
        {
            std::string nextLine;
            std::getline(cfgFile, nextLine);

            if (isSection(nextLine)) {
                sectionBeingScanned = extractSectionName(nextLine);
            }

            std::stringstream nextLineSS(nextLine);

            std::string buffer;
            std::string key;
            std::string value;

            bool key_time = true;
            while (std::getline(nextLineSS, buffer, '=')) {
                if (key_time) {
                    if (buffer.at(buffer.size() - 1) == ' ') {
                        buffer.pop_back();
                    }
                    key = buffer;

                    key_time = false;
                }
                else {
                    if (buffer.at(0) == ' ') {
                        buffer = buffer.substr(1, buffer.size() - 1);
                    }

                    value = buffer;
                }
            }

            loadProperty(key, value);
                
            loadKeyBindings(key, value);
        }

        cfgFile.close();
    }
}

void Settings::loadProperty(std::string propName, std::string value)
{
    if (props.contains(propName)) {
        try {
            bool* prop = std::any_cast<bool*>(props[propName]);
            *prop = str_to_boolean(value);
            return;
        }
        catch (std::bad_any_cast& e) {}

        try {
            uint* prop = std::any_cast<uint*>(props[propName]);
            *prop = str_to_uint(value);
            return;
        }
        catch (std::bad_any_cast& e) {}

        try {
            std::string* prop = std::any_cast<std::string*>(props[propName]);
            *prop = value;
            return;
        }
        catch (std::bad_any_cast& e) {}
    }
    
    if (str_equals_str(sectionBeingScanned, "MyHpOptions")) {
        loadHpOptions(myHpOptions, propName, value);
    }
    else if (str_equals_str(sectionBeingScanned, "AllyHpOptions")) {
        loadHpOptions(allyHpOptions, propName, value);
    }
    else if (str_equals_str(sectionBeingScanned, "EnemyHpOptions")) {
        loadHpOptions(enemyHpOptions, propName, value);
    }

    if (str_equals_str(propName, "SelectedMods")) {
        std::string filename;

        std::stringstream ss(value);

        std::filesystem::path current_path = std::filesystem::current_path();
        std::vector<std::string> hpi_files = get_files_from_path(current_path, ".hpi");

        while (std::getline(ss, filename, ',')) {
            if (filename.at(0) == ' ') {
                filename = filename.substr(1, filename.size() - 1);
            }

            auto string_iterator = std::find(hpi_files.begin(), hpi_files.end(), filename);

            if (string_iterator != hpi_files.end()) {
                SelectedMods.push_back(filename);
            }
        }
    }
}

void Settings::loadKeyBindings(std::string& key, std::string& value)
{
    for (std::pair<std::string, CommandCode> entry : strToCommandCode) {
        std::string commandStr = entry.first;

        if (str_contains_str(key, commandStr)) {
            // handling the key part
            Command command;
            command.code = entry.second;
            command.params = getParamsFromCommandStrWithParams(key, commandStr);

            // handling the value part
            Keys keys = strToKeys(value);
                
            auto keys_iterator = std::find_if(keyBindings.begin(), keyBindings.end(),
                [&](std::pair<Keys, Command> entry) {
                    return command == entry.second;
                }
            );

            if (keys_iterator != keyBindings.end()) {
                keyBindings.erase(keys_iterator);
            }

            keyBindings.insert(std::pair { keys, command });
        }
    }
}

void Settings::Save()
{
    ConfigFile cfgFile("TAKEnhanced.cfg");

    if (cfgFile.is_open())
    {
        cfgFile.writeSection("Launcher");
        cfgFile.writeProperty("Width", Launcher.Width);
        cfgFile.writeProperty("Height", Launcher.Height);

        cfgFile << std::endl;

        cfgFile.writeSection("Game");
        cfgFile.writeProperty("EnableDevMode", EnableDevMode);
        cfgFile.writeProperty("EnableMods", EnableMods);
        cfgFile.writeList("SelectedMods", SelectedMods);

        cfgFile << std::endl << std::endl;

        cfgFile.writeProperty("MaxUnits", MaxUnits);
        cfgFile.writeProperty("PathfindingCycles", PathFindingCycles);

        cfgFile << std::endl;

        cfgFile.writeProperty("NoCD", NoCD);
        cfgFile.writeProperty("OffscreenFix", OffscreenFix);

        cfgFile << std::endl;

        cfgFile.writeSection("MyHpOptions");
        cfgFile.writeProperty("Mode", showHpOptionToString[myHpOptions.showHpOption]);
        cfgFile.writeProperty("HpColorMode", hpColorModeToString[myHpOptions.hpColorOption.mode]);
        cfgFile.writeProperty("FixedColor", colorToString[myHpOptions.hpColorOption.color]);

        cfgFile << std::endl;

        cfgFile.writeSection("AllyHpOptions");
        cfgFile.writeProperty("Mode", showHpOptionToString[allyHpOptions.showHpOption]);
        cfgFile.writeProperty("HpColorMode", hpColorModeToString[allyHpOptions.hpColorOption.mode]);
        cfgFile.writeProperty("FixedColor", colorToString[allyHpOptions.hpColorOption.color]);

        cfgFile << std::endl;

        cfgFile.writeSection("EnemyHpOptions");
        cfgFile.writeProperty("Mode", showHpOptionToString[enemyHpOptions.showHpOption]);
        cfgFile.writeProperty("HpColorMode", hpColorModeToString[enemyHpOptions.hpColorOption.mode]);
        cfgFile.writeProperty("FixedColor", colorToString[enemyHpOptions.hpColorOption.color]);

        cfgFile << std::endl;

        cfgFile.writeSection("MeleeStuckFix");
        cfgFile.writeProperty("MeleeStuckFix", MeleeStuckFix);
        cfgFile.writeProperty("ForcedMinRangeForMelees", ForcedMinRangeForMelees);

        cfgFile << std::endl;

        cfgFile.writeSection("Keys");

        for (std::pair<Keys, Command> keyBinding : keyBindings) {
            Keys* keys = &keyBinding.first;
            Command* command = &keyBinding.second;

            cfgFile.writeProperty(command->to_string(), keys->to_string());
        }
            
        cfgFile << std::endl;
        cfgFile.close();
    }
}

bool Settings::isSection(std::string str)
{
    if (std::regex_match(str, std::regex("\\[[A-z]*\\]"))) {
        return true;
    }

    return false;
}

std::string Settings::extractSectionName(std::string str)
{
    return str.substr(1, str.size() - 2);
}

void Settings::loadHpOptions(HpOptions& hpOption, std::string propName, std::string value)
{
    if (str_equals_str(propName, "Mode")) {
        hpOption.showHpOption = stringToShowHpOption[value];
    }
    else if (str_equals_str(propName, "HpColorMode")) {
        hpOption.hpColorOption.mode = stringToHpColorMode[value];
    }
    else if (str_equals_str(propName, "FixedColor")) {
        hpOption.hpColorOption.color = stringToColor[value];
    }
}
