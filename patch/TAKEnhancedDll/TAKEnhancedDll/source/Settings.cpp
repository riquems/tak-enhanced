#pragma once

#include "TAKEnhancedDll/Settings.hpp"

Settings::Settings() {}

void Settings::LoadSettings(std::string path)
{
    std::fstream cfgFile(path);
        
    if (cfgFile.is_open())
    {
        while (cfgFile.good())
        {
            std::string nextLine;
            std::getline(cfgFile, nextLine);

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

    if (str_equals_str(propName, "ShowPlayer")) {
        bool ShowPlayerHpBar = str_to_boolean(value);

        if (!ShowPlayerHpBar) {
            showHpOptions &= ~SHOW_PLAYER;
        }
    }
    else if (str_equals_str(propName, "ShowAllies")) {
        bool ShowAlliesHpBar = str_to_boolean(value);

        if (!ShowAlliesHpBar) {
            showHpOptions &= ~SHOW_ALLIES;
        }
    }
    else if (str_equals_str(propName, "ShowEnemies")) {
        bool ShowEnemiesHpBar = str_to_boolean(value);

        if (!ShowEnemiesHpBar) {
            showHpOptions &= ~SHOW_ENEMIES;
        }
    }
    else if (str_equals_str(propName, "ShowOnlyIfDamaged")) {
        bool ShowHpBarOnlyIfDamaged = str_to_boolean(value);

        if (!ShowHpBarOnlyIfDamaged) {
            showHpOptions &= ~SHOW_ONLY_IF_DAMAGED;
        }
    }
    else if (str_equals_str(propName, "SelectedMods")) {
        std::string filename;

        std::stringstream ss(value);

        while (std::getline(ss, filename, ',')) {
            if (filename.at(0) == ' ') {
                filename = filename.substr(1, filename.size() - 1);
            }

            SelectedMods.push_back(filename);
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
        cfgFile.writeSection("General");
        cfgFile.writeProperty("EnableDevMode", EnableDevMode);
        cfgFile.writeProperty("EnableMods", EnableMods);
        cfgFile.writeList("SelectedMods", SelectedMods);

        cfgFile << std::endl << std::endl;

        cfgFile.writeProperty("MaxUnits", MaxUnits);
        cfgFile.writeProperty("PathfindingCycles", PathFindingCycles);

        cfgFile << std::endl;

        cfgFile.writeSection("Changes");
        cfgFile.writeProperty("NoCD", NoCD);
        cfgFile.writeProperty("OffscreenFix", OffscreenFix);

        cfgFile << std::endl;

        cfgFile.writeSection("HP Bar");
        cfgFile.writeProperty("ShowPlayer", (showHpOptions & SHOW_PLAYER) == SHOW_PLAYER);
        cfgFile.writeProperty("ShowAllies", (showHpOptions & SHOW_ALLIES) == SHOW_ALLIES);
        cfgFile.writeProperty("ShowEnemies", (showHpOptions & SHOW_ENEMIES) == SHOW_ENEMIES);
        cfgFile.writeProperty("ShowOnlyIfDamaged", (showHpOptions & SHOW_ONLY_IF_DAMAGED) == SHOW_ONLY_IF_DAMAGED);

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
