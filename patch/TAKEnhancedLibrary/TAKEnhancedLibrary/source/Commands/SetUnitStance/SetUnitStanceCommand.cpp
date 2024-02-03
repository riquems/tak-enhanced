#include "TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommand.hpp"

UnitStance UnitStance::Passive = UnitStance("Passive");
UnitStance UnitStance::Defensive = UnitStance("Defensive");
UnitStance UnitStance::Offensive = UnitStance("Offensive");

SetUnitStanceCommand::SetUnitStanceCommand() : Command(CommandCode::SET_UNIT_STANCE, "SetUnitStance") { }
SetUnitStanceCommand::SetUnitStanceCommand(SetUnitStanceCommandParams params) : Command(CommandCode::SET_UNIT_STANCE, "SetUnitStance"), params(params) { }

SetUnitStanceCommand SetUnitStanceCommand::Passive = SetUnitStanceCommand(
    SetUnitStanceCommandParams {
        .stance = UnitStance::Passive,
    }
);

SetUnitStanceCommand SetUnitStanceCommand::Defensive = SetUnitStanceCommand(
    SetUnitStanceCommandParams {
        .stance = UnitStance::Defensive,
    }
);

SetUnitStanceCommand SetUnitStanceCommand::Offensive = SetUnitStanceCommand(
    SetUnitStanceCommandParams {
        .stance = UnitStance::Offensive,
    }
);
