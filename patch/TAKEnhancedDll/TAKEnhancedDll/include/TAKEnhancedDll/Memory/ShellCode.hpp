#pragma once
#include <TAKEnhancedDll/common.hpp>
#include <TAKEnhancedDll/Memory/Memory.hpp>

class ShellCode
{
public:
    std::vector<BYTE> shellCode;
    Memory place;

    ShellCode();
    ShellCode(std::string shellCodeStr, DWORD startAddress);
    ShellCode(std::string shellCodeStr, Memory _place);

    static std::vector<BYTE> stringToShellCode(std::string shellCodeStr);

    BYTE* data();

    DWORD startAddress();

    DWORD endAddress();

    DWORD placeLength();

    unsigned int size();
};
