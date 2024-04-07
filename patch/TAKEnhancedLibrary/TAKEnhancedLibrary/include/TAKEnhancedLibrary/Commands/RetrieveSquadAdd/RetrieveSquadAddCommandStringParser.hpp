#pragma once
#include "TAKEnhancedLibrary/Commands/ICommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/RetrieveSquadAdd/RetrieveSquadAddCommand.hpp"

class RetrieveSquadAddCommandStringParser : public ICommandStringParser
{
    std::string toString(const Command& cmd) override;
    std::unique_ptr<Command> _fromString(std::string str) override;

public:
    RetrieveSquadAddCommandStringParser();
    std::string toString(const RetrieveSquadAddCommand& cmd);
    std::unique_ptr<RetrieveSquadAddCommand> fromString(std::string str);
};
