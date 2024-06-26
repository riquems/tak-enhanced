#include "TAKEnhancedLibrary/Keys/KeyCombinationJsonParser.hpp"
#include "TAKEnhancedLibrary/Keys/KeyCombinationStringParser.hpp"

void to_json(json& j, const KeyCombination& kc) {
    j = keyCombinationStringParser.toString(kc);
}

void from_json(const json& j, KeyCombination& kc) {
    kc = keyCombinationStringParser.fromString(j.get<std::string>());
}
