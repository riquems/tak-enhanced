#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/CommandStringParsers.hpp"

class CommandStringParser
{
    CommandStringParsers parsers;

public:
    CommandStringParser(CommandStringParsers parsers);

    std::string toString(const Command& command);
    std::unique_ptr<Command> fromString(std::string str);
};

extern CommandStringParser commandStringParser;
