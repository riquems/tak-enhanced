#pragma once

#include "TAKEnhancedDll/Commands/SelectBuildingCommandHandler.hpp"
#include "TAKEnhancedDll/Commands/RotateBuildingCommandHandler.hpp"
#include "TAKEnhancedDll/Commands/SetUnitStanceCommandHandler.hpp"
#include "TAKEnhancedDll/Commands/CreateSquadCommandHandler.hpp"
#include "TAKEnhancedDll/Commands/RetrieveSquadCommandHandler.hpp"
#include "TAKEnhancedDll/Commands/RetrieveSquadAddCommandHandler.hpp"

namespace CommandHandlers
{
    extern SelectBuildingCommandHandler SelectBuilding;
    extern RotateBuildingCommandHandler RotateBuilding;
    extern SetUnitStanceCommandHandler SetUnitStance;
    extern CreateSquadCommandHandler CreateSquad;
    extern RetrieveSquadCommandHandler RetrieveSquad;
    extern RetrieveSquadAddCommandHandler RetrieveSquadAdd;
}
