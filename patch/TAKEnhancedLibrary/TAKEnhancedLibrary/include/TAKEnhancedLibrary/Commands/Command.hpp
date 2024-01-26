#pragma once
#include "Utils/json.hpp"
#include <TAKEnhancedLibrary/Commands/Params.hpp>

enum CommandCode {
    INVALID,
    ATTACK,
    SELECT_BUILDING,
    ROTATE_BUILDING
};

NLOHMANN_JSON_SERIALIZE_ENUM(CommandCode, {
    { INVALID, nullptr },
    { ATTACK, "Attack" },
    { SELECT_BUILDING, "SelectBuilding" },
    { ROTATE_BUILDING, "RotateBuilding" },
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
