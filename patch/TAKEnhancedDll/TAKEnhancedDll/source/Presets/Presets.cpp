#include "TAKEnhancedDll/Presets/Presets.hpp"

Presets::Presets(std::vector<Preset> presets) : presets(presets) {}

std::optional<Preset> Presets::get(std::string name) {
    return dky::find(this->presets, [&](const Preset& preset) {
        return preset.name == name;
    });
}

std::optional<Preset> Presets::find(std::function<bool(const Preset&)> predicate) {
    return dky::find(this->presets, predicate);
}

bool Presets::empty() {
    return this->presets.empty();
}

std::vector<Preset> Presets::asVector() {
    return this->presets;
}
