#pragma once

#include "TAKEnhancedDll/Commands/CommandHandler.hpp"
#include "TAKEnhancedLibrary/Commands/RetrieveSquadAdd/RetrieveSquadAddCommand.hpp"

class RetrieveSquadAddCommandHandler : public CommandHandler
{
    void _handle(const Command& command) override;

public:
    RetrieveSquadAddCommandHandler();
    void handle(const RetrieveSquadAddCommand& command);
};
