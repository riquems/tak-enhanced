#include "TAKEnhancedDll/Commands/ExecuteCommand.hpp"
#include "TAKEnhancedDll/Commands/CommandHandlers.hpp"

CommandHandler& getCommandHandler(CommandCode commandCode) {
    switch (commandCode)
    {
        case CommandCode::SELECT_BUILDING: return CommandHandlers::SelectBuilding;
        case CommandCode::ROTATE_BUILDING: return CommandHandlers::RotateBuilding;
        case CommandCode::SET_UNIT_STANCE: return CommandHandlers::SetUnitStance;
        case CommandCode::CREATE_SQUAD: return CommandHandlers::CreateSquad;
        case CommandCode::RETRIEVE_SQUAD: return CommandHandlers::RetrieveSquad;
        case CommandCode::RETRIEVE_SQUAD_ADD: return CommandHandlers::RetrieveSquadAdd;
        default:
            throw "No command handler for this command type";
    }
}

void executeCommand(const Command& command) {
    auto& handler = getCommandHandler(command.code);

    handler.handle(command);
}
