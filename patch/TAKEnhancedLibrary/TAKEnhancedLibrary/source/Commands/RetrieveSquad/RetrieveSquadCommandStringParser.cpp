#include "TAKEnhancedLibrary/Commands/RetrieveSquad/RetrieveSquadCommandStringParser.hpp"

RetrieveSquadCommandStringParser::RetrieveSquadCommandStringParser() : ICommandStringParser(RetrieveSquadCommand()) {}

std::unique_ptr<RetrieveSquadCommand> RetrieveSquadCommandStringParser::fromString(std::string str) {
    auto cmdParts = ICommandStringParser::getCommandParts(str);

    return std::make_unique<RetrieveSquadCommand>(
        RetrieveSquadCommandParams {
            .squad = std::stoi(cmdParts.at(1))
        }
    );
}

std::string RetrieveSquadCommandStringParser::toString(const RetrieveSquadCommand& cmd) {
    return std::string(cmd.name) + " " + std::to_string(cmd.params.squad);
}

std::unique_ptr<Command> RetrieveSquadCommandStringParser::_fromString(std::string str) {
    return this->fromString(str);
}

std::string RetrieveSquadCommandStringParser::toString(const Command& cmd) {
    return this->toString(dynamic_cast<const RetrieveSquadCommand&>(cmd));
}
