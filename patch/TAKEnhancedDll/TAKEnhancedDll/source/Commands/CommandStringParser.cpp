#include "TAKEnhancedDll/Commands/CommandStringParser.hpp"

CommandStringParser::CommandStringParser(Commands commands) : commands(commands) {}

std::string CommandStringParser::toString(Command command) {
    std::string commandStr = command.name;

    if (command.params.count() > 0) {
        for (auto param : command.params.asUnorderedMap()) {
            commandStr.append(" ").append(param.second);
        }
    }

    return commandStr;
}

Command CommandStringParser::fromString(std::string str) {
    auto command = commands.find(
        [&](const Command& command)->bool {
            return str_contains_str(str, command.name);
        }
    );

    Params params = this->getParamsFromCommandStrWithParams(str, command.value().name);

    return command.value().withParams(params);
}

// Example input: "Spawn Unit aragod 1"
// Example output: { "unitname": "aragod", "player": 1 }
Params CommandStringParser::getParamsFromCommandStrWithParams(std::string str, std::string commandWithoutParams)
{
    Params params;

    char* commandStrBuffer = _strdup(str.c_str());

    char* param = strtok(commandStrBuffer, commandWithoutParams.c_str());
    while (param != NULL) {
        params.add("buildingId", param);

        param = strtok(NULL, commandWithoutParams.c_str());
    }

    return params;
}
