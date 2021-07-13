#include <cstdint>
#include <iostream>
#include "Models/Player.h"
#include "Models/Side.h"
#include "Models/Options/GameOptions.h"

class Game
{
    uintptr_t _baseAddress;

public:
    Game();
    Game(uintptr_t baseAddress);

    GameOptions* getGameOptions();
    Unit* getSelectedUnit();
    Player* getPlayers();

    Side* getSides();
    int getNumberOfSides();

    uintptr_t getMouseHoveredUnitAddress();
};
