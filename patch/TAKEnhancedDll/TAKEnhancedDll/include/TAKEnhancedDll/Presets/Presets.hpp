#pragma once
#include "TAKEnhancedDll/common.hpp"
#include <TAKEnhancedDll/Presets/Preset.hpp>

class Presets
{
    std::vector<Preset> presets;

public:
    Presets(std::vector<Preset> presets);

    std::optional<Preset> get(std::string name);
    std::optional<Preset> find(std::function<bool(const Preset&)> predicate);
    bool empty();

    std::vector<Preset> asVector();
};
