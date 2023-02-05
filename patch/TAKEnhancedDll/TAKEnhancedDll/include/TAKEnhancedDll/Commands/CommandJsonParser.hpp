#pragma once
#include "TAKEnhancedDll/Commands/CommandStringParser.hpp"

void to_json(json& j, const Command& c);

void from_json(const json& j, Command& c);
