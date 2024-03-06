#pragma once
#include "TAKEnhancedLibrary/Keys/KeyCombination.hpp"

void to_json(json& j, const KeyCombination& kc);

void from_json(const json& j, KeyCombination& kc);
