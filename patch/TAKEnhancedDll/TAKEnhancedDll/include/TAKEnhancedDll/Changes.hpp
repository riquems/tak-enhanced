#pragma once

#include <TAKEnhancedDll/Configs/GameConfig.hpp>
#include <Utils/Logger.h>

extern "C" __declspec(dllexport) const char* TAK_Enhanced_Label;

void applyTakEnhancedVersion();

void applyChanges(std::shared_ptr<GameConfig> config, std::shared_ptr<Logger> logger);