#pragma once
#include "Utils/common.h"
#include "Utils/json.hpp"
#include <TAKEnhancedLibrary/Keys/Key.hpp>

struct KeyCombination
{
    std::vector<Key> keys;

    KeyCombination();
    KeyCombination(std::initializer_list<Key> init_list);

    bool operator==(const KeyCombination& keyCombination) const;
};

struct KeyCombinationHashFunction
{
    std::size_t operator()(const KeyCombination& keyCombination) const;
};
