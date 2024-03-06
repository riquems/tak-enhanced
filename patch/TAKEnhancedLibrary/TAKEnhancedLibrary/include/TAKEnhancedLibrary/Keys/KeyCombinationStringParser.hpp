#pragma once
#include <TAKEnhancedLibrary/Keys/Keys.hpp>
#include <TAKEnhancedLibrary/Keys/KeyCombination.hpp>

class KeyCombinationStringParser
{
public:
    KeyCombinationStringParser(Keys keys);

    std::string toString(KeyCombination keyCombination);
    KeyCombination fromString(std::string str);

private:
    Keys keys;
};

extern KeyCombinationStringParser keyCombinationStringParser;
