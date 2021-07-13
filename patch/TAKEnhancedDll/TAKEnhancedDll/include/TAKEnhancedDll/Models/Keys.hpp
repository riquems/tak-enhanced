#pragma once
#include "Utils/common.h"

extern std::unordered_map<int, std::string> keyToStr;

extern std::unordered_map<std::string, int> strToKey;

void initializeKeys();

struct Keys
{
    std::vector<int> values;

    Keys();
    Keys(std::initializer_list<int> init_list);

    std::string to_string() const;

    bool operator==(const Keys& keys) const;
};

struct KeysHashFunction
{
    std::size_t operator()(const Keys& keys) const;
};

Keys strToKeys(std::string str);
