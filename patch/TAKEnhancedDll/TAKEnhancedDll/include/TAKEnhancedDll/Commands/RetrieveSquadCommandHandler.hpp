#pragma once

#include "TAKEnhancedDll/Commands/CommandHandler.hpp"
#include "TAKEnhancedLibrary/Commands/RetrieveSquad/RetrieveSquadCommand.hpp"

class RetrieveSquadCommandHandler : public CommandHandler
{
    void _handle(const Command& command) override;

public:
    RetrieveSquadCommandHandler();
    void handle(const RetrieveSquadCommand& command);
};
