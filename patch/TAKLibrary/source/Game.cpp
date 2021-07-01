#include "Game.hpp"
#include "Models/Options/GameOptions.h"
#include "Models/Options/DevelopmentOptions.h"
#include "GlobalPointers/GlobalPointers.h"

void Game::ActivateDeveloperMode(uintptr_t baseAddress)
{
    GameOptions* gameOptions = *(GameOptions**) (GlobalPointers::GameOptions + baseAddress);

    gameOptions->developmentOptions->activatable = true;
    gameOptions->developmentOptions->activated = true;
}

Player* Game::GetPlayers(uintptr_t baseAddress)
{
    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + baseAddress);

    Player* players = (Player*) (*gamePtr + 0x2404);

    return players;
}