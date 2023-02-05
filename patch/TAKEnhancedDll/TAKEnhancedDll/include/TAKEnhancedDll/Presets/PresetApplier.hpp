#pragma once
#include "TAKEnhancedDll/common.hpp"
#include <TAKEnhancedDll/Presets/Preset.hpp>

class PresetApplier
{
public:
    void applyPreset(const Preset& preset, GameConfig& gameConfig);
};
