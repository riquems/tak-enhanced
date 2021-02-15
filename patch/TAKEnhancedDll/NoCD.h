#pragma once
#include "MemoryHandler.h"

void NoCD()
{
	MemoryHandling::writeShortJMP(Memory(0x0A5146, 0x0A5148), 0x0A515A);

	MemoryHandling::writeJMP(Memory(0x0A7DDA, 0x0A7DE0), 0x0A7EF0);

	MemoryHandling::writeShortJMP(Memory(0x0A7E7A, 0x0A7E7C), 0x0A7EF0);
	MemoryHandling::writeShortJMP(Memory(0x09BA35, 0x09BA37), 0x09BA49);

	logger.log("No-CD applied.");
}