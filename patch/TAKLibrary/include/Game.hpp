#include <cstdint>
#include <iostream>
#include "Models/Player.h"

namespace Game
{
    void ActivateDeveloperMode(uintptr_t baseAddress);
    Player* GetPlayers(uintptr_t baseAddress);
}