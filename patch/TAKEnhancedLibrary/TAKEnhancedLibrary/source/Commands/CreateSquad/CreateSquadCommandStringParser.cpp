#include "TAKEnhancedLibrary/Commands/CreateSquad/CreateSquadCommandStringParser.hpp"

CreateSquadCommandStringParser::CreateSquadCommandStringParser() : ICommandStringParser(CreateSquadCommand()) {}

std::unique_ptr<CreateSquadCommand> CreateSquadCommandStringParser::fromString(std::string str) {
    auto cmdParts = ICommandStringParser::getCommandParts(str);

    return std::make_unique<CreateSquadCommand>(
        CreateSquadCommandParams {
            .squad = std::stoi(cmdParts.at(1))
        }
    );
}

std::string CreateSquadCommandStringParser::toString(const CreateSquadCommand& cmd) {
    return std::string(cmd.name) + " " + std::to_string(cmd.params.squad);
}

std::unique_ptr<Command> CreateSquadCommandStringParser::_fromString(std::string str) {
    return this->fromString(str);
}

std::string CreateSquadCommandStringParser::toString(const Command& cmd) {
    return this->toString(dynamic_cast<const CreateSquadCommand&>(cmd));
}
