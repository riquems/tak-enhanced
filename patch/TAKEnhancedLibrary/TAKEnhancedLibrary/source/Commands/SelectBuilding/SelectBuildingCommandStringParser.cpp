#include "TAKEnhancedLibrary/Commands/SelectBuilding/SelectBuildingCommandStringParser.hpp"

SelectBuildingCommandStringParser::SelectBuildingCommandStringParser() : ICommandStringParser(SelectBuildingCommand()) {}

std::unique_ptr<SelectBuildingCommand> SelectBuildingCommandStringParser::fromString(std::string str) {
    auto cmdParts = ICommandStringParser::getCommandParts(str);

    return std::make_unique<SelectBuildingCommand>(
        SelectBuildingCommandParams {
            .building = std::stoi(cmdParts.at(1))
        }
    );
}

std::string SelectBuildingCommandStringParser::toString(const SelectBuildingCommand& cmd) {
    return std::string(cmd.name) + " " + std::to_string(cmd.params.building);
}

std::unique_ptr<Command> SelectBuildingCommandStringParser::_fromString(std::string str) {
    return this->fromString(str);
}

std::string SelectBuildingCommandStringParser::toString(const Command& cmd) {
    return this->toString(dynamic_cast<const SelectBuildingCommand&>(cmd));
}
