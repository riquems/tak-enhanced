#pragma once

#include "TAKEnhancedDll/Commands/CommandHandler.hpp"
#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommand.hpp"

class SelectBuildingCommandHandler : public CommandHandler
{
    void _handle(const Command& command) override;

public:
    SelectBuildingCommandHandler();
    void handle(const SelectBuildingCommand& command);
};
