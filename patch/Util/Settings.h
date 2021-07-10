#pragma once

#include "common.h"
#include "defs.h"
#include "HelperFunctions.h"

#include "Keys.h"
#include "Command.h"

class Settings
{
public:
    bool EnableDevMode = false;
    bool EnableMods = true;
    uint MaxUnits = 5000;
    uint PathFindingCycles = 100000;
    uint ForcedMinRangeForMelees = 40;
    bool NoCD = true;
    bool MeleeStuckFix = true;
    bool PauseWhenUnfocused = false;
    bool OffscreenFix = true;

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

    Settings() {}
    void LoadSettings(std::string path) 
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

                this->MapClassFieldToValue(key.c_str(), value.c_str());
                
                loadKeyBindings(key, value);
            }

            cfgFile.close();
        }
    }

    void MapClassFieldToValue(const char* key, const char* value)
    {
        if (str_equals_str(key, "EnableDevMode")) {
            EnableDevMode = str_to_boolean(value);
        }
        else if (str_equals_str(key, "EnableMods")) {
            EnableMods = str_to_boolean(value);
        }
        else if (str_equals_str(key, "MaxUnits")) {
            MaxUnits = str_to_uint(value);
        }
        else if (str_equals_str(key, "PathfindingCycles")) {
            PathFindingCycles = str_to_uint(value);
        }
        else if (str_equals_str(key, "NoCD")) {
            NoCD = str_to_boolean(value);
        }
        else if (str_equals_str(key, "MeleeStuckFix")) {
            MeleeStuckFix = str_to_boolean(value);
        }
        else if (str_equals_str(key, "OffscreenFix")) {
            OffscreenFix = str_to_boolean(value);
        }
        else if (str_equals_str(key, "PauseWhenUnfocused")) {
            PauseWhenUnfocused = str_to_boolean(value);
        }
        else if (str_equals_str(key, "ForcedMinRangeForMelees")) {
            ForcedMinRangeForMelees = str_to_uint(value);
        }
        else if (str_equals_str(key, "SelectedMods")) {
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

    void loadKeyBindings(std::string& key, std::string& value)
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

    void Save()
    {
        std::ofstream cfgFile("TAKEnhanced.cfg");

        if (cfgFile.is_open())
        {
            cfgFile << "[General]" << std::endl;
            cfgFile << "EnableDevMode = " << boolean_to_str(EnableDevMode) << std::endl;
            cfgFile << "EnableMods = " << boolean_to_str(EnableMods) << std::endl;
            cfgFile << "SelectedMods = ";

            for (std::string& mod_filename : SelectedMods) {
                if (!str_equals_str(mod_filename.c_str(), SelectedMods.at(SelectedMods.size() - 1).c_str())) {
                    cfgFile << mod_filename << ", ";
                }
                else {
                    cfgFile << mod_filename;
                }
            }

            cfgFile << std::endl << std::endl;
            cfgFile << "MaxUnits = " << MaxUnits << std::endl;
            cfgFile << "PathfindingCycles = " << PathFindingCycles << std::endl;
            cfgFile << std::endl;
            cfgFile << "[Changes]" << std::endl;
            cfgFile << "NoCD = " << boolean_to_str(NoCD) << std::endl;
            cfgFile << "MeleeStuckFix = " << boolean_to_str(MeleeStuckFix) << std::endl;
            cfgFile << "OffscreenFix = " << boolean_to_str(OffscreenFix) << std::endl;
            cfgFile << "PauseWhenUnfocused = " << boolean_to_str(PauseWhenUnfocused) << std::endl;
            cfgFile << std::endl;
            cfgFile << "[MeleeStuckFix]" << std::endl;
            cfgFile << "ForcedMinRangeForMelees = " << ForcedMinRangeForMelees << std::endl;
            cfgFile << std::endl;
            cfgFile << "[Keys]" << std::endl;

            for (std::pair<Keys, Command> keyBinding : keyBindings) {
                Keys* keys = &keyBinding.first;
                Command* command = &keyBinding.second;

                cfgFile << command->to_string() << " = " << keys->to_string() << std::endl;
            }
            
            cfgFile << std::endl;
            cfgFile.close();
        }
    }
};