#pragma once
#include "MemoryHandler.h"
#include "../Changes/SearchBox.h"

extern "C" __declspec(dllexport) void __stdcall updateGuiExtension()
{
    updateSearchBox();
}

void applyUpdateGuiExtensionPatch()
{
    MemoryHandler::fillWithNOPs(Memory(0x170165, 0x17016F));

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::POP_ESI, 0x17016B);
    
    ShellCode shellCode(std::string("8BE5"), 0x17016C); // MOV ESP, EBP
    MemoryHandler::writeShellCode(shellCode);

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::POP_EBP, 0x17016E);
    MemoryHandler::insertOpCode(MemoryHandler::OpCode::RETN, 0x17016F);

    MemoryHandler::insertFunctionCall((DWORD) &updateGuiExtension, 0x170165);

    logger.log("Added Update GUI Extension.");
}