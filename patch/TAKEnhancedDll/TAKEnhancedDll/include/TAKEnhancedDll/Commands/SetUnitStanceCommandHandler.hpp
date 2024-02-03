#pragma once

#include "TAKEnhancedDll/Commands/CommandHandler.hpp"
#include "TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommand.hpp"

class SetUnitStanceCommandHandler : public CommandHandler
{
    void _handle(const Command& command) override;

public:
    SetUnitStanceCommandHandler();
    void handle(const SetUnitStanceCommand& command);
};
