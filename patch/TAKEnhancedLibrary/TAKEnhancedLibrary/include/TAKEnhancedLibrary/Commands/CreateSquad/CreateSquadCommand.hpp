#pragma once
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Params.hpp"
#include "Utils/json.hpp"

struct CreateSquadCommandParams : Params
{
    int squad;
};

struct CreateSquadCommand : public Command
{
    CreateSquadCommandParams params;

    CreateSquadCommand() : Command(CommandCode::CREATE_SQUAD, "CreateSquad") {}
    CreateSquadCommand(CreateSquadCommandParams params) : Command(CommandCode::CREATE_SQUAD, "CreateSquad"),
        params(params) {}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CreateSquadCommandParams, squad)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CreateSquadCommand, params)
