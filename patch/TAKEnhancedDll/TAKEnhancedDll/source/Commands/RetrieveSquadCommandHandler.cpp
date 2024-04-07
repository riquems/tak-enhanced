#include "TAKEnhancedDll/Commands/RetrieveSquadCommandHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Commands.hpp"
#include "TAKEnhancedLibrary/Commands/CommandStringParser.hpp"

RetrieveSquadCommandHandler::RetrieveSquadCommandHandler() {}

void RetrieveSquadCommandHandler::_handle(const Command& command) {
    handle(dynamic_cast<const RetrieveSquadCommand&>(command));
}

void RetrieveSquadCommandHandler::handle(const RetrieveSquadCommand& command) {
    if (gameWrapper->isBuildMenuOpen())
        return;

    if (gameWrapper->isInWriteMode())
        return;

    TAKEnhancedLibrary::ExecuteCommand(commandStringParser.toString(command));
}
