#pragma once

#include "TAKEnhancedLibrary/common.hpp"

#include <TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommand.hpp>

#include <TAKEnhancedLibrary/Commands/CreateSquad/CreateSquadCommand.hpp>
#include <TAKEnhancedLibrary/Commands/RetrieveSquad/RetrieveSquadCommand.hpp>
#include <TAKEnhancedLibrary/Commands/RetrieveSquadAdd/RetrieveSquadAddCommand.hpp>

#include <TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommand.hpp>
#include <TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommand.hpp>

namespace TAKEnhancedLibrary
{
    void ExecuteCommand(const std::string& command);
}
