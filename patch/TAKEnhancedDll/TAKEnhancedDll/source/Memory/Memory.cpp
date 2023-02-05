#include "TAKEnhancedDll/Memory/Memory.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

Memory::Memory() {}
Memory::Memory(DWORD _startAddress, DWORD _endAddress)
{
    startAddress = baseAddress + _startAddress;
    endAddress = baseAddress + _endAddress;

    length = endAddress - startAddress;
}
