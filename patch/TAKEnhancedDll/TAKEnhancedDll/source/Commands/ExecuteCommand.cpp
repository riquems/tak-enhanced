#include "TAKEnhancedDll/Commands/ExecuteCommand.hpp"
#include "TAKEnhancedDll/Commands/CommandHandlers.hpp"

CommandHandler& getCommandHandler(CommandCode commandCode) {
    switch (commandCode)
    {
        case CommandCode::SELECT_BUILDING: return CommandHandlers::SelectBuilding;
        case CommandCode::ROTATE_BUILDING: return CommandHandlers::RotateBuilding;
        default:
            throw "No command handler for this command type";
    }
}

void executeCommand(const Command& command) {
    auto& handler = getCommandHandler(command.code);

    handler.handle(command);
}
