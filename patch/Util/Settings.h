#pragma once

#include "common.h"

class Settings
{
public:
    bool enable_dev_mode = false;
    bool enable_mods = true;
    uint max_units = 5000;
    uint pathfinding_cycles = 100000;
    uint forced_minrange_for_melees = 40;
    bool no_cd = true;
    bool melee_stuck_fix = true;
    bool pause_when_unfocused = false;
    bool offscreen_fix = true;

    std::vector<std::string> selected_mods;

    Settings() {}
    void LoadSettings(std::string path) 
    {
        std::fstream cfgFile(path);
        
        if (cfgFile.is_open())
        {
            while (cfgFile.good())
            {
                // char key[64];
                // char value[64];

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

                // sscanf_s(nextLine.c_str(), "%s = %s", key, 64, value, 64);

                this->MapClassFieldToValue(key.c_str(), value.c_str());
            }

            cfgFile.close();
        }
    }

    void MapClassFieldToValue(const char* key, const char* value)
    {
        if (str_equals_str(key, "EnableDevMode")) {
            enable_dev_mode = str_to_boolean(value);
        }
        else if (str_equals_str(key, "EnableMods")) {
            enable_mods = str_to_boolean(value);
        }
        else if (str_equals_str(key, "MaxUnits")) {
            max_units = str_to_uint(value);
        }
        else if (str_equals_str(key, "PathfindingCycles")) {
            pathfinding_cycles = str_to_uint(value);
        }
        else if (str_equals_str(key, "NoCD")) {
            no_cd = str_to_boolean(value);
        }
        else if (str_equals_str(key, "MeleeStuckFix")) {
            melee_stuck_fix = str_to_boolean(value);
        }
        else if (str_equals_str(key, "OffscreenFix")) {
            offscreen_fix = str_to_boolean(value);
        }
        else if (str_equals_str(key, "PauseWhenUnfocused")) {
            pause_when_unfocused = str_to_boolean(value);
        }
        else if (str_equals_str(key, "ForcedMinRangeForMelees")) {
            forced_minrange_for_melees = str_to_uint(value);
        }
        else if (str_equals_str(key, "SelectedMods")) {
            std::string filename;

            std::stringstream ss(value);

            while (std::getline(ss, filename, ',')) {
                if (filename.at(0) == ' ') {
                    filename = filename.substr(1, filename.size() - 1);
                }

                selected_mods.push_back(filename);
            }
        }
    }

    void Save()
    {
        std::ofstream cfgFile("TAKEnhanced.cfg");

        if (cfgFile.is_open())
        {
            cfgFile << "[General]" << std::endl;
            cfgFile << "EnableDevMode = " << boolean_to_str(enable_dev_mode) << std::endl;
            cfgFile << "EnableMods = " << boolean_to_str(enable_mods) << std::endl;
            cfgFile << "SelectedMods = ";

            for (std::string& mod_filename : selected_mods) {
                if (!str_equals_str(mod_filename.c_str(), selected_mods.at(selected_mods.size() - 1).c_str())) {
                    cfgFile << mod_filename << ", ";
                }
                else {
                    cfgFile << mod_filename;
                }
            }

            cfgFile << std::endl << std::endl;
            cfgFile << "MaxUnits = " << max_units << std::endl;
            cfgFile << "PathfindingCycles = " << pathfinding_cycles << std::endl;
            cfgFile << std::endl;
            cfgFile << "[Changes]" << std::endl;
            cfgFile << "NoCD = " << boolean_to_str(no_cd) << std::endl;
            cfgFile << "MeleeStuckFix = " << boolean_to_str(melee_stuck_fix) << std::endl;
            cfgFile << "OffscreenFix = " << boolean_to_str(offscreen_fix) << std::endl;
            cfgFile << "PauseWhenUnfocused = " << boolean_to_str(pause_when_unfocused) << std::endl;
            cfgFile << std::endl;
            cfgFile << "[MeleeStuckFix]" << std::endl;
            cfgFile << "ForcedMinRangeForMelees = " << forced_minrange_for_melees << std::endl;

            cfgFile.close();
        }
    }
};