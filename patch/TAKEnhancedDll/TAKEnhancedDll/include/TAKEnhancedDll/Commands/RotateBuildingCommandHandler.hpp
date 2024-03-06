#pragma once

#include "TAKEnhancedDll/Commands/CommandHandler.hpp"
#include "TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommand.hpp"

class RotateBuildingCommandHandler : public CommandHandler
{
    std::vector<std::string> disabledUnits;

    void _handle(const Command& command) override;

public:
    RotateBuildingCommandHandler();
    void handle(const RotateBuildingCommand& command);
};
