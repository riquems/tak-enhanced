#pragma once

#include "TAKEnhancedDll/Commands/Command.hpp"
#include "TAKEnhancedDll/Commands/CommandJsonParser.hpp"
#include "TAKEnhancedDll/Keys/KeyCombination.hpp"
#include "TAKEnhancedDll/Keys/KeyCombinationJsonParser.hpp"

struct KeyBinding
{
    KeyCombination keyCombination;
    Command command;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(KeyBinding, keyCombination, command)
