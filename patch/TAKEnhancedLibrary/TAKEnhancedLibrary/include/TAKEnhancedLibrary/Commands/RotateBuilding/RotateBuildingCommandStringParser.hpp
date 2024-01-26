#pragma once
#include "TAKEnhancedLibrary/Commands/ICommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommand.hpp"

class RotateBuildingCommandStringParser : public ICommandStringParser
{
    std::string toString(const Command& cmd) override;
    std::unique_ptr<Command> _fromString(std::string str) override;

public:
    RotateBuildingCommandStringParser();
    std::string toString(const RotateBuildingCommand& cmd);
    std::unique_ptr<RotateBuildingCommand> fromString(std::string str);
};
