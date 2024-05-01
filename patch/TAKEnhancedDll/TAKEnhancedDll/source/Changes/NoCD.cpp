#include "TAKEnhancedDll/Changes/NoCD.hpp"

#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

void applyNoCD()
{
    // Play the Adventure
    MemoryHandler::writeShortJMP(Memory(0x0A5146, 0x0A5148), 0x0A515A);

    // Choose Campaign
    MemoryHandler::writeJMP(Memory(0x0A7DDA, 0x0A7DE0), 0x0A7EF0);
    MemoryHandler::writeShortJMP(Memory(0x0A7E7A, 0x0A7E7C), 0x0A7EF0);

    // Load Campaign

    // TBOD
    MemoryHandler::writeJMP(0x0BB817, 0x0BB92F);

    // IP
    MemoryHandler::writeShortJMP(0x0BB8B5, 0x0BB92F);

    // Host Game
    MemoryHandler::writeShortJMP(Memory(0x09BA35, 0x09BA37), 0x09BA49);
}
