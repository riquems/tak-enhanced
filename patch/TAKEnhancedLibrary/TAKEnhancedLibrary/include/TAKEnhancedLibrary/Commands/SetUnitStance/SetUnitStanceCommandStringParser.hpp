#pragma once
#include "TAKEnhancedLibrary/Commands/ICommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommand.hpp"

class SetUnitStanceCommandStringParser : public ICommandStringParser
{
    std::string toString(const Command& cmd) override;
    std::unique_ptr<Command> _fromString(std::string str) override;

public:
    SetUnitStanceCommandStringParser();
    std::string toString(const SetUnitStanceCommand& cmd);
    std::unique_ptr<SetUnitStanceCommand> fromString(std::string str);
};
