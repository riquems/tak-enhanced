#pragma once
#include "TAKEnhancedLibrary/Commands/ICommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/RetrieveSquad/RetrieveSquadCommand.hpp"

class RetrieveSquadCommandStringParser : public ICommandStringParser
{
    std::string toString(const Command& cmd) override;
    std::unique_ptr<Command> _fromString(std::string str) override;

public:
    RetrieveSquadCommandStringParser();
    std::string toString(const RetrieveSquadCommand& cmd);
    std::unique_ptr<RetrieveSquadCommand> fromString(std::string str);
};
