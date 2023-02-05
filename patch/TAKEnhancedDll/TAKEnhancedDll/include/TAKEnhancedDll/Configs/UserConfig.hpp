#pragma once
#include "TAKEnhancedDll/common.hpp"
#include <TAKEnhancedDll/KeyBinding.hpp>

struct UserConfig
{
    std::vector<KeyBinding> keyBindings;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UserConfig, keyBindings)
