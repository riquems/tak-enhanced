#pragma once
#include "MemoryHandler.h"
#include "../Changes/SearchBox.h"

extern "C" __declspec(dllexport) void __stdcall updateGuiExtension()
{
    updateSearchBox();
}

void applyUpdateGuiExtensionPatch()
{
    MemoryHandling::fillWithNOPs(Memory(0x170165, 0x17016F));

    MemoryHandling::insertOpCode(MemoryHandling::OpCode::POP_ESI, 0x17016B);
    
    ShellCode shellCode(std::string("8BE5"), 0x17016C); // MOV ESP, EBP
    MemoryHandling::writeShellCode(shellCode);

    MemoryHandling::insertOpCode(MemoryHandling::OpCode::POP_EBP, 0x17016E);
    MemoryHandling::insertOpCode(MemoryHandling::OpCode::RETN, 0x17016F);

    MemoryHandling::insertFunctionCall((DWORD) &updateGuiExtension, 0x170165);

    logger.log("Added Update GUI Extension.");
}