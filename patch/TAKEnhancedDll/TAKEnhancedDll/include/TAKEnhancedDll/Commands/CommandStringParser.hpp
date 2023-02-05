#pragma once
#include <TAKEnhancedDll/Commands/Commands.hpp>

class CommandStringParser
{
public:
    CommandStringParser(Commands commands);

    std::string toString(Command command);
    Command fromString(std::string str);

private:
    static Params getParamsFromCommandStrWithParams(std::string str, std::string commandWithoutParams);

    Commands commands;
};

extern CommandStringParser commandStringParser;
