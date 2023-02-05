#pragma once
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

void applyNoPauseWhenUnfocused()
{
    ShellCode shellCode("9090", Memory(0x133431, 0x133433));
    MemoryHandler::writeShellCode(shellCode);
}
