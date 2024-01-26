#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Commands/Command.hpp"

void to_json(json& j, const std::shared_ptr<Command>& kc);

void from_json(const json& j, std::shared_ptr<Command>& kc);
