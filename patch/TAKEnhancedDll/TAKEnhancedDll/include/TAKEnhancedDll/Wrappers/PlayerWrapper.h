#pragma once
#include "TAKEnhancedDll/common.hpp"

#include "UnitWrapper.h"
#include "TAKCore/Models/Player.h"
#include "TAKCore/Models/PlayerViewModel.h"

class PlayerWrapper
{
public:
    Player* _player;
    std::vector<UnitWrapper> units;

    PlayerWrapper(Player* player);

    uint16_t getUnitsCount();
    uint8_t getPlayerId();
    uint8_t getTeamId();
};
