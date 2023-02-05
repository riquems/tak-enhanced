#pragma once
#include "TAKEnhancedDll/common.hpp"
#include "TAKEnhancedDll/Commands/Command.hpp"
#include "TAKEnhancedDll/Wrappers/GameWrapper.h"

void selectBuilding(Params params);

class Commands
{
    std::vector<Command> commands = {
        Command(CommandCode::SELECT_BUILDING, "Select Building", selectBuilding)
    };

public:
    std::optional<Command> get(CommandCode code);
    std::optional<Command> find(std::function<bool(const Command&)> predicate);
};

extern Commands commands;
