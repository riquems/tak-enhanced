#pragma once

#include "common.h"
#include "defs.h"

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

    std::map<int, int> buildingKeys = { std::pair<int, int>(VK_1, 1),
                                        std::pair<int, int>(VK_2, 2),
                                        std::pair<int, int>(VK_3, 3),
                                        std::pair<int, int>(VK_4, 4),
                                        std::pair<int, int>(VK_5, 5),
                                        std::pair<int, int>(VK_6, 6),
                                        std::pair<int, int>(VK_7, 7),
                                        std::pair<int, int>(VK_8, 8),
                                        std::pair<int, int>(VK_9, 9),
                                        std::pair<int, int>(VK_0, 10) };

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

            cfgFile.close();
        }
    }
};