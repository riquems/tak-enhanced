#include "Game.hpp"
#include "GlobalPointers/GlobalPointers.h"

Player* Game::GetPlayers(uintptr_t baseAddress)
{
	uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + baseAddress);

	Player* players = (Player*) (*gamePtr + 0x2404);

	return players;
}