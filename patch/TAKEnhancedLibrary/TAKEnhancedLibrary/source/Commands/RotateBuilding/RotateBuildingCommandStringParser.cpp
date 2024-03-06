#include "TAKEnhancedLibrary/Commands/RotateBuilding/RotateBuildingCommandStringParser.hpp"

RotateBuildingCommandStringParser::RotateBuildingCommandStringParser() : ICommandStringParser(RotateBuildingCommand()) {}

std::unique_ptr<RotateBuildingCommand> RotateBuildingCommandStringParser::fromString(std::string str) {
    auto cmdParts = ICommandStringParser::getCommandParts(str);

    auto maybeOrientation = RotateOrientation::fromString(cmdParts.at(1));

    if (!maybeOrientation.has_value()) {
        throw "Invalid orientation value supplied" + cmdParts.at(1);
    }

    auto orientation = maybeOrientation.value();

    return std::make_unique<RotateBuildingCommand>(
        RotateBuildingCommandParams {
            .orientation = orientation,
            .step = 1
        }
    );
}

std::string RotateBuildingCommandStringParser::toString(const RotateBuildingCommand& cmd) {
    return std::string(cmd.name) + " " + RotateOrientation::toString(cmd.params.orientation);
}

std::unique_ptr<Command> RotateBuildingCommandStringParser::_fromString(std::string str) {
    return this->fromString(str);
}

std::string RotateBuildingCommandStringParser::toString(const Command& cmd) {
    return this->toString(dynamic_cast<const RotateBuildingCommand&>(cmd));
}
