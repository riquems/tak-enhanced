#pragma once
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Params.hpp"
#include "Utils/json.hpp"

struct RetrieveSquadAddCommandParams : Params
{
    int squad;
};

struct RetrieveSquadAddCommand : public Command
{
    RetrieveSquadAddCommandParams params;

    RetrieveSquadAddCommand() : Command(CommandCode::RETRIEVE_SQUAD_ADD, "RetrieveSquadAdd") {}
    RetrieveSquadAddCommand(RetrieveSquadAddCommandParams params) : Command(CommandCode::RETRIEVE_SQUAD_ADD, "RetrieveSquadAdd"),
        params(params) {}
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RetrieveSquadAddCommandParams, squad)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RetrieveSquadAddCommand, params)
