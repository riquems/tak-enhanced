#pragma once
#include "MemoryHandler.h"

void applyNoPauseWhenUnfocused()
{
    ShellCode shellCode("9090", Memory(0x133431, 0x133433));
    MemoryHandler::writeShellCode(shellCode);

    logger.log("No pause when unfocused applied.");
}