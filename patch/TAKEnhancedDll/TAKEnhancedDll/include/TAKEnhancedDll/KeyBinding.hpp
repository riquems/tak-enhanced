#pragma once

#include "TAKEnhancedLibrary/Commands/CommandJsonParser.hpp"
#include "TAKEnhancedDll/Keys/KeyCombination.hpp"
#include "TAKEnhancedDll/Keys/KeyCombinationJsonParser.hpp"

struct KeyBinding
{
    KeyCombination keyCombination;
    std::shared_ptr<Command> command;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(KeyBinding, keyCombination, command)
