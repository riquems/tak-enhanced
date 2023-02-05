#pragma once
#include <TAKEnhancedDll/Keys/Keys.hpp>
#include <TAKEnhancedDll/Keys/KeyCombination.hpp>

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
