#include "TAKEnhancedLibrary/Commands/CommandJsonParser.hpp"
#include "TAKEnhancedLibrary/Commands/CommandStringParser.hpp"

void to_json(json& j, const std::shared_ptr<Command>& kc)
{
    j = commandStringParser.toString(*kc);
}

void from_json(const json& j, std::shared_ptr<Command>& kc)
{
    kc = commandStringParser.fromString(j.get<std::string>());
}
