#pragma once
#include "Common.hpp"

#include "TAKCore/Models/Player.h"
#include "TAKCore/Models/Side.h"
#include "TAKCore/Models/Options/GameOptions.h"

class Game
{
    uintptr_t _baseAddress;

public:
    Game();
    Game(uintptr_t baseAddress);

    GameOptions* getGameOptions();

    Side* getSides();
    int getNumberOfSides();
};
