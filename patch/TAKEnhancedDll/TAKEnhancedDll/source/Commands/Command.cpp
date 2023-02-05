#include <TAKEnhancedDll/Commands/Command.hpp>

Command::Command() {}
Command::Command(CommandCode code, std::string name, std::function<void(Params)> action)
    : code(code), name(name), action(action) {}
Command::Command(CommandCode code, std::string name, Params params, std::function<void(Params)> action)
    : code(code), name(name), params(params), action(action) {}

bool Command::operator==(Command second) {
    return this->code == second.code;
}

void Command::execute() {
    this->action(this->params);
}

void Command::execute(Params params) {
    this->action(params);
}

Command Command::withParams(Params params) {
    this->params = params;
    return *this;
}
