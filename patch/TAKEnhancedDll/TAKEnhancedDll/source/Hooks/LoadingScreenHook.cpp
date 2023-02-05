#include "TAKEnhancedDll/Hooks/LoadingScreenHook.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"

__declspec(dllexport) bool firstLoad = false;

// replaces the call to this empty function: 004FABC0
// loading start
__declspec(dllexport) void __stdcall LoadingScreenHook()
{
    if (!firstLoad) {
        firstLoad = true;
    }
}

__declspec(dllexport) void __stdcall LoadingScreenEndHook()
{
    if (currentGameConfig->developerMode.enabled) {
        logger->info("Activating developer mode");
        gameWrapper->activateDeveloperMode();
    }

    gameWrapper->initializePlayersWrappers();
}

void applyLoadingScreenHooks()
{
    MemoryHandler::insertFunctionCall((DWORD) &LoadingScreenHook, 0x1258E0);

    MemoryHandler::fillWithNOPs(Memory(0x125AC1, 0x125AC2));

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::RETN, 0x125AC6);
    MemoryHandler::insertFunctionCall((DWORD) &LoadingScreenEndHook, 0x125AC1);
}
