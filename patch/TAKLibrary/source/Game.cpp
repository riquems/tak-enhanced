#include "Game.hpp"
#include "Models/Options/GameOptions.h"
#include "Models/Options/DevelopmentOptions.h"
#include "GlobalPointers/GlobalPointers.h"
#include "Functions/FunctionsOffsets.h"

Game::Game() {}
Game::Game(uintptr_t baseAddress)
{
    _baseAddress = baseAddress;
}

GameOptions* Game::getGameOptions()
{
    return *(GameOptions**) (GlobalPointers::GameOptions + _baseAddress);
}

Player* Game::getPlayers()
{
    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + _baseAddress);

    Player* players = (Player*) (*gamePtr + 0x2404);

    return players;
}

Unit* Game::getSelectedUnit()
{

}

Side* Game::getSides()
{
    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + _baseAddress);
    Side* sides = (Side*) (*gamePtr + 0x3078);

    return sides;
}

int Game::getNumberOfSides()
{
    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + _baseAddress);
    int* numberOfSidesPtr = (int*) (*gamePtr + 0x3074);

    return *numberOfSidesPtr;
}

uintptr_t Game::getMouseHoveredUnitAddress()
{
    uintptr_t(*getMouseHoveredUnitAddress)() = (uintptr_t(*)()) (FunctionsOffsets::getMouseHoveredUnitAddress + _baseAddress);

    return getMouseHoveredUnitAddress();
}
