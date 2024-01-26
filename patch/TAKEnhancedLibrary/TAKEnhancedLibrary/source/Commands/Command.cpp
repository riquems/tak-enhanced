#include "TAKEnhancedLibrary/Commands/Command.hpp"

Command::Command(CommandCode code, std::string name)
    : code(code), name(name) {}

Command::~Command() { }

bool Command::operator==(const Command& second) {
    return this->code == second.code;
}
