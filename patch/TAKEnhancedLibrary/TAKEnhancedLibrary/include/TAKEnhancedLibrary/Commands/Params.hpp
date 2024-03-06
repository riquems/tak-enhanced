#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Commands/Param.hpp"

struct Params
{
    std::unordered_map<std::string, std::string> params;

    Params();
    Params(std::initializer_list<Param> params);

    std::optional<std::string> get(std::string key);
    void add(Param param);
    void add(std::string key, std::string value);
    uint count();
    std::unordered_map<std::string, std::string> asUnorderedMap();
};
