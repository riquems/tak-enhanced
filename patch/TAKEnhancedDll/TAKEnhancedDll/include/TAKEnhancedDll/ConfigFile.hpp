#pragma once

#include "TAKEnhancedDll/common.hpp"
#include "Utils/HelperFunctions.hpp"

#include <fstream>
#include <vector>

class ConfigFile
{
    std::ofstream outputFileStream;

public:
    ConfigFile(const std::string& path);

    bool is_open();
    void close();

    void writeSection(std::string sectionName);
    void writeProperty(std::string propName, uint value);
    void writeProperty(std::string propName, bool value);
    void writeProperty(std::string propName, std::string value);

    void writeList(std::string propName, std::vector<std::string> values);

    std::ostream& operator<<(std::ostream& (__cdecl* _Pfn)(std::ostream&));
};
