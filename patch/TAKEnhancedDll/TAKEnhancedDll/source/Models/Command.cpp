#pragma once

#include "TAKEnhancedDll/Models/Command.hpp"

std::vector<std::string> availableCommandsStrings = {
    "Select Building",
    "Attack"
};

std::unordered_map<CommandCode, std::string> commandCodeToStr = {
   std::pair<CommandCode, std::string>(CommandCode::SELECT_BUILDING, "Select Building"),
   std::pair<CommandCode, std::string>(CommandCode::ATTACK, "Attack"),
};

std::unordered_map<std::string, CommandCode> strToCommandCode;

std::unordered_map<CommandCode, std::function<void(std::vector<std::string>)>> commandCodeToFunction;

template <typename T1, typename T2>
std::unordered_map<T2, T1> build_reversed_map(const std::unordered_map<T1, T2>& map1)
{
    std::unordered_map<T2, T1> map2;

    std::for_each(map1.begin(), map1.end(), [&](std::pair<T1, T2> elem) {
        map2.insert(std::pair<T2, T1>(elem.second, elem.first));
        });

    return map2;
}

void initializeCommands()
{
    strToCommandCode = build_reversed_map(commandCodeToStr);
}

Command::Command() {}
Command::Command(CommandCode _code) : code(_code) {}
Command::Command(CommandCode _code, std::string _param) : code(_code), params { _param } {}
Command::Command(CommandCode _code, std::vector<std::string> _params) : code(_code), params(_params) {}

bool Command::operator==(Command second) {
    return code   == second.code &&
            params == second.params;
}

std::string Command::to_string() const {
    std::string commandStr = commandCodeToStr[code];

    if (params.size() > 0) {
        for (std::string param : params) {
            commandStr.append(" ").append(param);
        }
    }

    return commandStr;
}

void Command::execute() {
    commandCodeToFunction[code](params);
}

std::vector<std::string> getParamsFromCommandStrWithParams(std::string str, std::string commandWithoutParams)
{
    std::vector<std::string> params;

    char* commandStrBuffer = _strdup(str.c_str());

    char* param = strtok(commandStrBuffer, commandWithoutParams.c_str());
    while (param != NULL) {
        params.push_back(param);

        param = strtok(NULL, commandWithoutParams.c_str());
    }

    return params;
}

Command strToCommand(std::string str)
{
    Command command;

    std::pair<std::string, CommandCode> commandNameCommandCodeMapEntry = *std::find_if(strToCommandCode.begin(), strToCommandCode.end(),
        [&](std::pair<std::string, CommandCode> entry) {
            std::string commandStr = entry.first;

            return str_contains_str(str, commandStr);
        }
    );

    std::string commandName = commandNameCommandCodeMapEntry.first;

    command.code = commandNameCommandCodeMapEntry.second;
    command.params = getParamsFromCommandStrWithParams(str, commandName);

    return command;
}
