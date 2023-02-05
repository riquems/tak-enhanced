#include "TAKEnhancedDll/Hooks/UpdateGuiHook.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKEnhancedDll/Changes/SearchBox.hpp"

__declspec(dllexport) void __stdcall updateGuiHook()
{
    if (!TAKisInitialized)
    {
        TAKisInitialized = true;
    }

    updateSearchBox();
}

void applyUpdateGuiHook()
{
    MemoryHandler::fillWithNOPs(Memory(0x170165, 0x17016F));

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::POP_ESI, 0x17016B);
    
    ShellCode shellCode(std::string("8BE5"), 0x17016C); // MOV ESP, EBP
    MemoryHandler::writeShellCode(shellCode);

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::POP_EBP, 0x17016E);
    MemoryHandler::insertOpCode(MemoryHandler::OpCode::RETN, 0x17016F);

    MemoryHandler::insertFunctionCall((DWORD) &updateGuiHook, 0x170165);
}
