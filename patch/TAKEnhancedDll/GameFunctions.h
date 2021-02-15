#pragma once
#include "HelperFeatures.h"

#include "Windows.h"
#include "GlobalPointers.h"
#include "Player.h"

DWORD GetAbsoluteAddress(DWORD);

namespace Game
{
	Player* players;
}

namespace GameFunctions
{
	DWORD (*GetMouseHoveredUnitAddress)();
}

namespace GameFunctionsExtensions
{
	Player* GetPlayers();
}

Player* GameFunctionsExtensions::GetPlayers()
{
	DWORD* gamePtr = (DWORD*) GetAbsoluteAddress(GlobalPointers::ptr_22D55C);

	Player* players = (Player*) (*gamePtr + 0x2404);

	return players;
}