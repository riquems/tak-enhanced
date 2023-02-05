#pragma once

#include <functional>

#include "Utils/HelperFunctions.hpp"
#include "Utils/json.hpp"
#include <TAKEnhancedDll/Commands/Params.hpp>

enum CommandCode {
    INVALID,
    ATTACK,
    SELECT_BUILDING
};

NLOHMANN_JSON_SERIALIZE_ENUM(CommandCode, {
    { INVALID, nullptr },
    { ATTACK, "Attack" },
    { SELECT_BUILDING, "SelectBuilding" }
});

struct Command
{
    CommandCode code;
    std::string name;
    Params params;
    std::function<void(Params)> action;

    Command();
    Command(CommandCode code, std::string name, std::function<void(Params)> action);
    Command(CommandCode code, std::string name, Params params, std::function<void(Params)> action);

    bool operator==(Command second);

    void execute();
    void execute(Params params);

    Command withParams(Params params);
};
