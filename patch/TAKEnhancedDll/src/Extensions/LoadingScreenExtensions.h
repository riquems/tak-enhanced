#pragma once
#include "MemoryHandler.h"
#include "Models/Player.h"
#include "Models/PlayerViewModel.h"

// replaces the call to this empty function: 004FABC0
// loading start
extern "C" __declspec(dllexport) void __stdcall LoadingScreenStartExtension()
{
	/* DWORD* gamePtr = (DWORD*) (0x22D55C + baseAddress);
	Player* players = (Player*) (*gamePtr + 0x2404);

	srand(time(NULL));
	players->playerViewModel->sideId = rand() % 4; */
}

extern "C" __declspec(dllexport) void __stdcall LoadingScreenEndExtension()
{
	game.initializePlayersWrappers();
}

void applyLoadingScreenExtensionsPatch()
{
	MemoryHandling::insertFunctionCall((DWORD) &LoadingScreenStartExtension, 0x1258E0);

	MemoryHandling::fillWithNOPs(Memory(0x125AC1, 0x125AC2));

	MemoryHandling::insertOpCode(MemoryHandling::OpCode::RETN, 0x125AC6);
	MemoryHandling::insertFunctionCall((DWORD) &LoadingScreenEndExtension, 0x125AC1);

	logger.log("Added Loading Screen Extension.");
}