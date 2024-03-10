#include "Game.hpp"
#include "TAKCore/Models/Options/GameOptions.h"
#include "TAKCore/Models/Options/DevelopmentOptions.h"
#include "TAKCore/GlobalPointers/GlobalPointers.h"
#include "TAKCore/Functions/FunctionsOffsets.h"
#include "TAKCore/Functions/FunctionsSignatures.h"
#include "TAKCore/Models/Unit.h"
#include "TAKCore/Players/Players.hpp"

Game::Game() {}
Game::Game(uintptr_t baseAddress)
{
    _baseAddress = baseAddress;
}

GameOptions* Game::getGameOptions()
{
    return *(GameOptions**) (GlobalPointers::GameOptions + _baseAddress);
}

Side* Game::getSides()
{
    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C_Offset + _baseAddress);
    Side* sides = (Side*) (*gamePtr + 0x3078);

    return sides;
}

int Game::getNumberOfSides()
{
    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C_Offset + _baseAddress);
    int* numberOfSidesPtr = (int*) (*gamePtr + 0x3074);

    return *numberOfSidesPtr;
}

