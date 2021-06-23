#pragma once
#include "MemoryHandler.h"

void applyPathfindingFix(uint value)
{
	MemoryHandling::write(value, 0x1617C);

	logger.log("Pathfinding applied.");
}