#pragma once
#include "MemoryHandler.h"

void PathfindingFix(uint value)
{
	MemoryHandling::write(value, 0x1617C);

	logger.log("Pathfinding enhancement applied.");
}