#pragma once
#include "TAKEnhancedDll/Common.hpp"

struct WindowConfig
{
    uint width = 800;
    uint height = 530;
};

struct LauncherConfig
{
    std::string presetsPath = "./TAKEnhanced/Presets";
    std::string modsPath = "./Mods";
    std::string currentPreset = "Custom";
    WindowConfig window;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(WindowConfig, width, height)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(LauncherConfig, currentPreset, presetsPath, modsPath, window)
