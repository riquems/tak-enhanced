#include "TAKEnhancedDll/Hooks/LoadingScreenHook.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

__declspec(dllexport) bool inLoadingScreen = false;

// replaces the call to this empty function: 004FABC0
// loading start
__declspec(dllexport) void __stdcall LoadingScreenStartHook()
{
    inLoadingScreen = true;
}

__declspec(dllexport) void __stdcall LoadingScreenEndHook()
{
    inLoadingScreen = false;
}

void applyLoadingScreenHooks()
{
    MemoryHandler::insertFunctionCall((DWORD) &LoadingScreenStartHook, 0x1258E0);

    MemoryHandler::fillWithNOPs(Memory(0x125AC1, 0x125AC2));

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::RETN, 0x125AC6);
    MemoryHandler::insertFunctionCall((DWORD) &LoadingScreenEndHook, 0x125AC1);
}
