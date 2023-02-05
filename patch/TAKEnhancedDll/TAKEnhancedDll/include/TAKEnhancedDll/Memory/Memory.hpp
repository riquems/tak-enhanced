#pragma once
#pragma pack(push, 8)
#include <Windows.h>
#pragma pack(pop)

class Memory
{
public:
    DWORD startAddress = 0;
    DWORD endAddress = 0;
    DWORD length = 0;

    Memory();
    Memory(DWORD _startAddress, DWORD _endAddress);
};
