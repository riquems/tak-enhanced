#pragma once
#include "TAKEnhancedDll/Common.hpp"

struct WindowConfig
{
    uint width;
    uint height;
};

struct LauncherConfig
{
    std::string presetsPath;
    std::string currentPreset;
    WindowConfig window;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WindowConfig, width, height)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LauncherConfig, currentPreset, presetsPath, window)
