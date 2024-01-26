#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommand.hpp"
#include "TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommand.hpp"

class Commands
{
    std::vector<Command> commands = {
        SelectBuildingCommand(),
        RotateBuildingCommand()
    };

public:
    std::optional<Command> get(CommandCode code);
    std::optional<Command> find(std::function<bool(const Command&)> predicate);
};

extern Commands commands;
