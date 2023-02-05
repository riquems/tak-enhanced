#pragma once
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

void applyPathfindingFix(uint value)
{
    MemoryHandler::write(value, 0x1617C);

    logger->info("Pathfinding applied.");
}