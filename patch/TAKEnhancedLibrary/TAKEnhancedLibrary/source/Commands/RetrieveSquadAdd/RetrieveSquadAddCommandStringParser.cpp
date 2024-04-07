#include "TAKEnhancedLibrary/Commands/RetrieveSquadAdd/RetrieveSquadAddCommandStringParser.hpp"

RetrieveSquadAddCommandStringParser::RetrieveSquadAddCommandStringParser() : ICommandStringParser(RetrieveSquadAddCommand()) {}

std::unique_ptr<RetrieveSquadAddCommand> RetrieveSquadAddCommandStringParser::fromString(std::string str) {
    auto cmdParts = ICommandStringParser::getCommandParts(str);

    return std::make_unique<RetrieveSquadAddCommand>(
        RetrieveSquadAddCommandParams {
            .squad = std::stoi(cmdParts.at(1))
        }
    );
}

std::string RetrieveSquadAddCommandStringParser::toString(const RetrieveSquadAddCommand& cmd) {
    return std::string(cmd.name) + " " + std::to_string(cmd.params.squad);
}

std::unique_ptr<Command> RetrieveSquadAddCommandStringParser::_fromString(std::string str) {
    return this->fromString(str);
}

std::string RetrieveSquadAddCommandStringParser::toString(const Command& cmd) {
    return this->toString(dynamic_cast<const RetrieveSquadAddCommand&>(cmd));
}
