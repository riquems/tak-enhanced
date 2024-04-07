#pragma once
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Params.hpp"
#include "Utils/json.hpp"

struct RetrieveSquadCommandParams : Params
{
    int squad;
};

struct RetrieveSquadCommand : public Command
{
    RetrieveSquadCommandParams params;

    RetrieveSquadCommand() : Command(CommandCode::RETRIEVE_SQUAD, "RetrieveSquad") {}
    RetrieveSquadCommand(RetrieveSquadCommandParams params) : Command(CommandCode::RETRIEVE_SQUAD, "RetrieveSquad"),
        params(params) {}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RetrieveSquadCommandParams, squad)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RetrieveSquadCommand, params)
