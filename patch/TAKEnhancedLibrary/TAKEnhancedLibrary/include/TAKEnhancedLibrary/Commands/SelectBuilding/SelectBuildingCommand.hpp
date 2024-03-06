#pragma once
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Params.hpp"
#include "Utils/json.hpp"

struct SelectBuildingCommandParams : Params
{
    int building;
};

struct SelectBuildingCommand : public Command
{
    SelectBuildingCommandParams params;

    SelectBuildingCommand() : Command(CommandCode::SELECT_BUILDING, "SelectBuilding") {}
    SelectBuildingCommand(SelectBuildingCommandParams params) : Command(CommandCode::SELECT_BUILDING, "SelectBuilding"),
        params(params) {}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SelectBuildingCommandParams, building)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SelectBuildingCommand, params)
