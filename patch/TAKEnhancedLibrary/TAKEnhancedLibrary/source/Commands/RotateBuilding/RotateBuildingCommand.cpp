#include "TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommand.hpp"

RotateOrientation RotateOrientation::Clockwise = RotateOrientation("Clockwise");
RotateOrientation RotateOrientation::CounterClockwise = RotateOrientation("CounterClockwise");

RotateBuildingCommand::RotateBuildingCommand() : Command(CommandCode::ROTATE_BUILDING, "RotateBuilding") { }
RotateBuildingCommand::RotateBuildingCommand(RotateBuildingCommandParams params) : Command(CommandCode::ROTATE_BUILDING, "RotateBuilding"), params(params) { }

RotateBuildingCommand RotateBuildingCommand::Clockwise = RotateBuildingCommand(
    RotateBuildingCommandParams {
        .orientation = RotateOrientation::Clockwise,
        .step = 1
    }
);

RotateBuildingCommand RotateBuildingCommand::CounterClockwise = RotateBuildingCommand(
    RotateBuildingCommandParams {
        .orientation = RotateOrientation::CounterClockwise,
        .step = 1
    }
);
