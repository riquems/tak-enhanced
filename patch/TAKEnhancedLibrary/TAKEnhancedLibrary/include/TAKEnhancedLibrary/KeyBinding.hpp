#pragma once

#include "TAKEnhancedLibrary/Commands/CommandJsonParser.hpp"
#include "TAKEnhancedLibrary/Keys/KeyCombination.hpp"
#include "TAKEnhancedLibrary/Keys/KeyCombinationJsonParser.hpp"

struct KeyBinding
{
    KeyCombination keyCombination;
    std::shared_ptr<Command> command;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(KeyBinding, keyCombination, command)
