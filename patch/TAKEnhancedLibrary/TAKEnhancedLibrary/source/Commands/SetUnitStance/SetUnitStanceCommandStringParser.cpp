#include "TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommandStringParser.hpp"

SetUnitStanceCommandStringParser::SetUnitStanceCommandStringParser() : ICommandStringParser(SetUnitStanceCommand()) {}

std::unique_ptr<SetUnitStanceCommand> SetUnitStanceCommandStringParser::fromString(std::string str) {
    auto cmdParts = ICommandStringParser::getCommandParts(str);

    auto maybeStance = UnitStance::fromString(cmdParts.at(1));

    if (!maybeStance.has_value()) {
        throw "Invalid stance value supplied" + cmdParts.at(1);
    }

    auto stance = maybeStance.value();

    return std::make_unique<SetUnitStanceCommand>(
        SetUnitStanceCommandParams {
            .stance = stance,
        }
    );
}

std::string SetUnitStanceCommandStringParser::toString(const SetUnitStanceCommand& cmd) {
    return std::string(cmd.name) + " " + UnitStance::toString(cmd.params.stance);
}

std::unique_ptr<Command> SetUnitStanceCommandStringParser::_fromString(std::string str) {
    return this->fromString(str);
}

std::string SetUnitStanceCommandStringParser::toString(const Command& cmd) {
    return this->toString(dynamic_cast<const SetUnitStanceCommand&>(cmd));
}
