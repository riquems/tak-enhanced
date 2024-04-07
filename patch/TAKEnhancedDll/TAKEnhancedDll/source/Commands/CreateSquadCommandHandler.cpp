#include "TAKEnhancedDll/Commands/CreateSquadCommandHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Commands.hpp"
#include "TAKEnhancedLibrary/Commands/CommandStringParser.hpp"

CreateSquadCommandHandler::CreateSquadCommandHandler() {}

void CreateSquadCommandHandler::_handle(const Command& command) {
    handle(dynamic_cast<const CreateSquadCommand&>(command));
}

void CreateSquadCommandHandler::handle(const CreateSquadCommand& command) {
    if (gameWrapper->isInWriteMode())
        return;

    TAKEnhancedLibrary::ExecuteCommand(commandStringParser.toString(command));
}
