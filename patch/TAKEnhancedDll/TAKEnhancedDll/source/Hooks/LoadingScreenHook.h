#pragma once
#include "MemoryHandler.h"
#include "Models/Player.h"
#include "Models/PlayerViewModel.h"

extern "C" __declspec(dllexport) bool firstLoad = false;

// replaces the call to this empty function: 004FABC0
// loading start
extern "C" __declspec(dllexport) void __stdcall LoadingScreenHook()
{
    if (!firstLoad) {
        firstLoad = true;
    }
}

extern "C" __declspec(dllexport) void __stdcall LoadingScreenEndHook()
{
    if (settings.EnableDevMode) {
        std::cout << "Activating developer mode" << std::endl;
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

    logger.log("Added Loading Screen Extension.");
}