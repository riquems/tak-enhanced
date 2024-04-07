#pragma once
#include "TAKEnhancedLibrary/Commands/ICommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/CreateSquad/CreateSquadCommand.hpp"

class CreateSquadCommandStringParser : public ICommandStringParser
{
    std::string toString(const Command& cmd) override;
    std::unique_ptr<Command> _fromString(std::string str) override;

public:
    CreateSquadCommandStringParser();
    std::string toString(const CreateSquadCommand& cmd);
    std::unique_ptr<CreateSquadCommand> fromString(std::string str);
};
