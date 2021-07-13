#include "TAKEnhancedDll/ConfigFile.hpp"

ConfigFile::ConfigFile(const std::string& path)
{
    outputFileStream.open(path);
}

bool ConfigFile::is_open()
{
    return outputFileStream.is_open();
}

void ConfigFile::close()
{
    outputFileStream.close();
}

void ConfigFile::writeSection(std::string sectionName)
{
    outputFileStream << "[" << sectionName << "]" << std::endl;
}

void ConfigFile::writeProperty(std::string propName, uint value)
{
    outputFileStream << propName << " = " << value << std::endl;
}

void ConfigFile::writeProperty(std::string propName, bool value)
{
    outputFileStream << propName << " = " << boolean_to_str(value) << std::endl;
}

void ConfigFile::writeProperty(std::string propName, std::string value)
{
    outputFileStream << propName << " = " << value << std::endl;
}

void ConfigFile::writeList(std::string propName, std::vector<std::string> values)
{
    outputFileStream << propName << " = ";

    for (std::string& value : values) {
        if (!str_equals_str(value.c_str(), values.at(values.size() - 1).c_str())) {
            outputFileStream << value << ", ";
        }
        else {
            outputFileStream << value;
        }
    }
}

std::ostream& ConfigFile::operator<<(std::ostream& (__cdecl* _Pfn)(std::ostream&))
{
    return outputFileStream << *_Pfn;
}
