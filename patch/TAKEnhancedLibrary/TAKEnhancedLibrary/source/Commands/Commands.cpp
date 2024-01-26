#include "TAKEnhancedLibrary/Commands/Commands.hpp"
#include "dky/std.hpp"

Commands commands;

std::optional<Command> Commands::get(CommandCode code) {
    return dky::find(this->commands, [&](const Command& command) {
        return command.code == code;
    });
}

std::optional<Command> Commands::find(std::function<bool(const Command&)> predicate) {
    return dky::find(this->commands, predicate);
}
