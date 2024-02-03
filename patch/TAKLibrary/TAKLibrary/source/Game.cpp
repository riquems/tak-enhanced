#include "Game.hpp"
#include "TAKCore/Models/Options/GameOptions.h"
#include "TAKCore/Models/Options/DevelopmentOptions.h"
#include "TAKCore/GlobalPointers/GlobalPointers.h"
#include "TAKCore/Functions/FunctionsOffsets.h"
#include "TAKCore/Functions/FunctionsSignatures.h"
#include "TAKCore/Models/Unit.h"

Game::Game() {}
Game::Game(uintptr_t baseAddress)
{
    _baseAddress = baseAddress;
}

GameOptions* Game::getGameOptions()
{
    return *(GameOptions**) (GlobalPointers::GameOptions + _baseAddress);
}

Player* Game::getCurrentPlayer()
{
    Player* players = this->getPlayers();

    return &players[0];
}

Player* Game::getPlayers()
{
    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + _baseAddress);

    Player* players = (Player*) (*gamePtr + 0x2404);

    return players;
}

std::vector<Unit*> Game::getSelectedUnits()
{
    Player* currentPlayer = this->getCurrentPlayer();

    std::vector<Unit*> selectedUnits;

    Unit* firstUnit = currentPlayer->firstUnit;

    Unit* nextUnit = firstUnit;
    while (nextUnit != currentPlayer->lastUnit)
    {
        if (nextUnit->walking & 0b00010000) {
            selectedUnits.push_back(nextUnit);
        }

        nextUnit++;
    }

    return selectedUnits;
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
