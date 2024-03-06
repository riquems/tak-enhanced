#include "TAKEnhancedLibrary/Commands/CommandStringParsers.hpp"
#include "dky/std.hpp"

std::shared_ptr<ICommandStringParser> CommandStringParsers::get(const Command& command) {
    auto maybeObj = dky::find(this->parsers, [&](const std::shared_ptr<ICommandStringParser>& parser) {
        return parser->ofCommand == command;
    });

    if (!maybeObj.has_value()) {
        throw "No parser was found for command " + command.name;
    }

    return maybeObj.value();
}

std::optional<std::shared_ptr<ICommandStringParser>> CommandStringParsers::find(
    std::function<bool(const std::shared_ptr<ICommandStringParser>&)> predicate
) {
    return dky::find(this->parsers, predicate);
}
