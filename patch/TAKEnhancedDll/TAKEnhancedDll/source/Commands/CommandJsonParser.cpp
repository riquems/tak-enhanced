#include "TAKEnhancedDll/Commands/CommandJsonParser.hpp"

void to_json(json& j, const Command& c) {
    j = commandStringParser.toString(c);
}

void from_json(const json& j, Command& c) {
    c = commandStringParser.fromString(j.get<std::string>());
}
