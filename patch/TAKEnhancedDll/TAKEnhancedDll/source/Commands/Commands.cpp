#include "TAKEnhancedDll/Commands/Commands.hpp"

void selectBuilding(Params params)
{
    if (!gameWrapper->isBuildMenuOpen())
        return;

    if (gameWrapper->isInWriteMode())
        return;

    int buildingId = std::stoi(params.get("buildingId").value());

    gameWrapper->selectBuilding(buildingId);
}

std::optional<Command> Commands::get(CommandCode code) {
    return dky::find(this->commands, [&](const Command& command) {
        return command.code == code;
    });
}

std::optional<Command> Commands::find(std::function<bool(const Command&)> predicate) {
    return dky::find(this->commands, predicate);
}
