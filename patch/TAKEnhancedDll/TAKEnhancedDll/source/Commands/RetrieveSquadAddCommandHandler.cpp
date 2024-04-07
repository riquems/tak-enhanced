#include "TAKEnhancedDll/Commands/RetrieveSquadAddCommandHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Commands.hpp"
#include "TAKEnhancedLibrary/Commands/CommandStringParser.hpp"

RetrieveSquadAddCommandHandler::RetrieveSquadAddCommandHandler() {}

void RetrieveSquadAddCommandHandler::_handle(const Command& command) {
    handle(dynamic_cast<const RetrieveSquadAddCommand&>(command));
}

void RetrieveSquadAddCommandHandler::handle(const RetrieveSquadAddCommand& command) {
    if (gameWrapper->isBuildMenuOpen())
        return;

    if (gameWrapper->isInWriteMode())
        return;

    TAKEnhancedLibrary::ExecuteCommand(commandStringParser.toString(command));
}
