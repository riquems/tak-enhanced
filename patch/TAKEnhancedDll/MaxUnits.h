#pragma once
#include "MemoryHandler.h"

void applyMaxUnitsPatch(uint value)
{
	/* Edit Max Units to the wanted value */
	MemoryHandling::write(value, 0x1F0404);

	/* Edit Visual (GUI) Max Units to the wanted value */

	ShellCode shellCode;
	shellCode = ShellCode("A104045F00", Memory(0x0A385F, 0x0A386B));
	MemoryHandling::writeShellCode(shellCode);

	/* Multiplayer games doesn't set max unit reg value correctly after exiting fix */

	shellCode = ShellCode("FF770C", Memory(0x099799, 0x09979C));
	MemoryHandling::writeShellCode(shellCode);

	shellCode = ShellCode("83C70C", Memory(0x09979C, 0x09979F));
	MemoryHandling::writeShellCode(shellCode);

	shellCode = ShellCode("FF3504045F00", Memory(0x09979F, 0x0997A5));
	MemoryHandling::writeShellCode(shellCode);

	/* Multiplayer games always set 500 as max units fix */

	shellCode = ShellCode("FF710C", Memory(0x09FEB6, 0x09FEBB));
	MemoryHandling::writeShellCode(shellCode);

	/* Everyone should use 0C now, representing desiredMaxUnits (this is for Skirmish) */

	shellCode = ShellCode("8B510C", Memory(0x0A03FA, 0x0A03FD));
	MemoryHandling::writeShellCode(shellCode);

	logger.log("Unit limit applied.");
}