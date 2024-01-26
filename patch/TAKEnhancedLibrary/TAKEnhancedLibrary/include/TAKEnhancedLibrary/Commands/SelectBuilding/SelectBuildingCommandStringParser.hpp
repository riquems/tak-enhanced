#pragma once
#include "TAKEnhancedLibrary/Commands/ICommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommand.hpp"

class SelectBuildingCommandStringParser : public ICommandStringParser
{
    std::string toString(const Command& cmd) override;
    std::unique_ptr<Command> _fromString(std::string str) override;

public:
    SelectBuildingCommandStringParser();
    std::string toString(const SelectBuildingCommand& cmd);
    std::unique_ptr<SelectBuildingCommand> fromString(std::string str);
};
