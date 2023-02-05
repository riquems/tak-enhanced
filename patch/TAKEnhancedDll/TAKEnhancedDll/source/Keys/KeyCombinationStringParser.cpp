#include <TAKEnhancedDll/Keys/KeyCombinationStringParser.hpp>
#include <Utils/HelperFunctions.hpp>

KeyCombinationStringParser::KeyCombinationStringParser(Keys keys) : keys(keys) {}

std::string KeyCombinationStringParser::toString(KeyCombination keyCombination) {
    std::string keysStr;

    for (size_t i = 0; i < keyCombination.keys.size(); i++) {
        keysStr.append(keyCombination.keys.at(i).name);

        if (i < keyCombination.keys.size() - 1) {
            keysStr.append(" + ");
        }
    }

    return keysStr;
}

KeyCombination KeyCombinationStringParser::fromString(std::string str) {
    KeyCombination keyCombination;

    char* keyStrBuffer = _strdup(str.c_str());

    char* keyStr = strtok(keyStrBuffer, " + ");
    while (keyStr != NULL) {
        Key key = this->keys.find([&](const Key& key) {
            return str_equals_str(key.name, keyStr);
        }).value();

        keyCombination.keys.push_back(key);

        keyStr = strtok(NULL, " + ");
    }

    return keyCombination;
}
