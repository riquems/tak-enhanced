#pragma once

#include "common.h"
#include "Utils/HelperFunctions.hpp"

#include <functional>

enum CommandCode {
    ATTACK,
    SELECT_BUILDING
};

extern std::vector<std::string> availableCommandsStrings;

extern std::unordered_map<CommandCode, std::function<void(std::vector<std::string>)>> commandCodeToFunction;

extern std::unordered_map<CommandCode, std::string> commandCodeToStr;

extern std::unordered_map<std::string, CommandCode> strToCommandCode;

void initializeCommands();

struct Command
{
    CommandCode code;
    std::vector<std::string> params;

    Command();
    Command(CommandCode _code);
    Command(CommandCode _code, std::string _param);
    Command(CommandCode _code, std::vector<std::string> _params);

    bool operator==(Command second);

    std::string to_string() const;

    void execute();
};

std::vector<std::string> getParamsFromCommandStrWithParams(std::string str, std::string commandWithoutParams);

Command strToCommand(std::string str);
