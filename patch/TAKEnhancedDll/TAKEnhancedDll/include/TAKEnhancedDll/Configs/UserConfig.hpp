#pragma once
#include "TAKEnhancedDll/common.hpp"
#include <TAKEnhancedDll/KeyBinding.hpp>

struct UserConfig
{
    std::string onDoubleClick;
    std::string onTripleClick;
    std::string onCtrlDoubleClick;
    std::vector<KeyBinding> keyBindings;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    UserConfig, onDoubleClick, onTripleClick, onCtrlDoubleClick, keyBindings
)
