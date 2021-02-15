#pragma once

#include "common.h"

class Settings
{
public:
	uint MaxUnits = 5000;
	uint PathfindingCycles = 100000;
	uint ForcedMinRangeForMelees = 40;
	bool NoCD = true;
	bool MeleeStuckFix = true;
	bool PauseWhenUnfocused = false;
	bool OffscreenFix = true;

	Settings() {}
	void LoadSettings(std::string path) 
	{
		std::fstream cfgFile(path);
		
		if (cfgFile.is_open())
		{
			while (cfgFile.good())
			{
				char key[64];
				char value[64];

				std::string nextLine;
				std::getline(cfgFile, nextLine);

				sscanf_s(nextLine.c_str(), "%s = %s", key, 64, value, 64);

				this->MapClassFieldToValue(key, value);
			}

			cfgFile.close();
		}
	}

	void MapClassFieldToValue(char* key, char* value)
	{
		if (str_equals_str(key, "MaxUnits")) {
			MaxUnits = str_to_uint(value);
		}
		else if (str_equals_str(key, "PathfindingCycles")) {
			PathfindingCycles = str_to_uint(value);
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
	}

	void Save()
	{
		std::ofstream cfgFile("TAKEnhanced.cfg");

		if (cfgFile.is_open())
		{
			cfgFile << "[General]" << std::endl;
			cfgFile << "MaxUnits = " << MaxUnits << std::endl;
			cfgFile << "PathfindingCycles = " << PathfindingCycles << std::endl;
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