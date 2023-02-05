#pragma once
#include "TAKEnhancedDll/common.hpp"
#include <TAKEnhancedDll/Commands/Param.hpp>

class Params
{
    std::unordered_map<std::string, std::string> params;

public:
    Params();
    Params(std::initializer_list<Param> params);

    std::optional<std::string> get(std::string key);
    void add(Param param);
    void add(std::string key, std::string value);
    uint count();
    std::unordered_map<std::string, std::string> asUnorderedMap();
};
