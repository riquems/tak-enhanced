#pragma once

#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommandStringParser.hpp"

class CommandStringParsers
{
    std::vector<std::shared_ptr<ICommandStringParser>> parsers = {
        std::make_shared<SelectBuildingCommandStringParser>(),
        std::make_shared<RotateBuildingCommandStringParser>(),
        std::make_shared<SetUnitStanceCommandStringParser>(),
    };

public:
    std::shared_ptr<ICommandStringParser> get(const Command& cmd);
    std::optional<std::shared_ptr<ICommandStringParser>> find(std::function<bool(const std::shared_ptr<ICommandStringParser>&)> predicate);
};
