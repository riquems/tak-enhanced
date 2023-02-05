#pragma once

#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

void showEveryoneHealthBars()
{
    MemoryHandler::fillWithNOPs(Memory(0x0FCD42, 0x0FCD50));

    MemoryHandler::writeShortJMP(Memory(0x0FCD42, 0x0FCD46), 0x0FCD66);
}
