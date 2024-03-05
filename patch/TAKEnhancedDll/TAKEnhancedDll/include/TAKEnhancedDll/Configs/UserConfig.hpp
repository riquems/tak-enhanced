#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include <TAKEnhancedLibrary/KeyBinding.hpp>

struct UserConfig
{
    std::string onSpacebar;
    std::string onDoubleClick;
    std::string onTripleClick;
    std::string onCtrlDoubleClick;
    std::vector<KeyBinding> keyBindings;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    UserConfig, onSpacebar, onDoubleClick, onTripleClick, onCtrlDoubleClick, keyBindings
)
