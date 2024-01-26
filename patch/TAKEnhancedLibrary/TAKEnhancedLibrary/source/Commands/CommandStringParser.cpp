#include "TAKEnhancedLibrary/Commands/CommandStringParser.hpp"
#include "TAKEnhancedLibrary/Commands/ICommandStringParser.hpp"

CommandStringParser commandStringParser { CommandStringParsers() };

CommandStringParser::CommandStringParser(CommandStringParsers parsers) : parsers(parsers) {}

std::string CommandStringParser::toString(const Command& command) {
    auto parser = this->parsers.get(command);

    return parser->toString(command);
}

std::unique_ptr<Command> CommandStringParser::fromString(std::string str) {
    auto maybeParser = this->parsers.find([&](const std::shared_ptr<ICommandStringParser>& parser) {
        return parser->canParse(str);
    });

    if (!maybeParser.has_value()) {
        throw "No parser was found that could parse " + str + " correctly.";
    }

    auto& parser = maybeParser.value();
    return parser->fromString(str);
}
