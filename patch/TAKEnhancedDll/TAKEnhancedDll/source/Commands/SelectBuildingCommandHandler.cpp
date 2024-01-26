#include "TAKEnhancedDll/Commands/SelectBuildingCommandHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

SelectBuildingCommandHandler::SelectBuildingCommandHandler() {}

void SelectBuildingCommandHandler::_handle(const Command& command) {
    handle(dynamic_cast<const SelectBuildingCommand&>(command));
}

void SelectBuildingCommandHandler::handle(const SelectBuildingCommand& command) {
    if (!gameWrapper->isBuildMenuOpen())
        return;

    if (gameWrapper->isInWriteMode())
        return;

    gameWrapper->selectBuilding(command.params.building);
}
