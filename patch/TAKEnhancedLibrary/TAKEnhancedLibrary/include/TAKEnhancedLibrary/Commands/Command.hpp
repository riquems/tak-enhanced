#pragma once
#include "Utils/json.hpp"
#include <TAKEnhancedLibrary/Commands/Params.hpp>

enum CommandCode {
    INVALID,
    ATTACK,
    SELECT_BUILDING,
    ROTATE_BUILDING,
    SET_UNIT_STANCE,
    CREATE_SQUAD,
    RETRIEVE_SQUAD,
    RETRIEVE_SQUAD_ADD
};

NLOHMANN_JSON_SERIALIZE_ENUM(CommandCode, {
    { INVALID, nullptr },
    { ATTACK, "Attack" },
    { SELECT_BUILDING, "SelectBuilding" },
    { ROTATE_BUILDING, "RotateBuilding" },
    { SET_UNIT_STANCE, "SetUnitStance" },
    { CREATE_SQUAD, "CreateSquad" },
    { RETRIEVE_SQUAD, "RetrieveSquad" },
    { RETRIEVE_SQUAD_ADD, "RetrieveSquadAdd" },
});

struct Command
{
    CommandCode code;
    std::string name;

    Command(CommandCode code, std::string name);
    virtual ~Command();

    bool operator==(const Command& second);
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Command, code, name)
