#include "TAKEnhancedDll/Commands/SetUnitStanceCommandHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

SetUnitStanceCommandHandler::SetUnitStanceCommandHandler() {
}

void SetUnitStanceCommandHandler::_handle(const Command& command) {
    handle(dynamic_cast<const SetUnitStanceCommand&>(command));
}

void SetUnitStanceCommandHandler::handle(const SetUnitStanceCommand& command) {
    if (gameWrapper->isInWriteMode())
        return;

    auto& stance = command.params.stance;

    gameWrapper->setUnitStance(stance);
}
