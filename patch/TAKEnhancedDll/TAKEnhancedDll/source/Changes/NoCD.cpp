#include "TAKEnhancedDll/Changes/NoCD.hpp"

#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

void applyNoCD()
{
    MemoryHandler::writeShortJMP(Memory(0x0A5146, 0x0A5148), 0x0A515A);

    MemoryHandler::writeJMP(Memory(0x0A7DDA, 0x0A7DE0), 0x0A7EF0);

    MemoryHandler::writeShortJMP(Memory(0x0A7E7A, 0x0A7E7C), 0x0A7EF0);
    MemoryHandler::writeShortJMP(Memory(0x09BA35, 0x09BA37), 0x09BA49);
}
