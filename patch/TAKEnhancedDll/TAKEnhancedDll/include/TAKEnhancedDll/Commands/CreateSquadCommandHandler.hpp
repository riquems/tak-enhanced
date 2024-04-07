#pragma once

#include "TAKEnhancedDll/Commands/CommandHandler.hpp"
#include "TAKEnhancedLibrary/Commands/CreateSquad/CreateSquadCommand.hpp"

class CreateSquadCommandHandler : public CommandHandler
{
    void _handle(const Command& command) override;

public:
    CreateSquadCommandHandler();
    void handle(const CreateSquadCommand& command);
};
