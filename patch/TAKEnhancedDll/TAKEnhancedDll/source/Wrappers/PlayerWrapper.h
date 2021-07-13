#pragma once
#include "TAKEnhancedDll/common.hpp"

#include "UnitWrapper.h"
#include "Models/Player.h"
#include "Models/PlayerViewModel.h"

class PlayerWrapper
{
public:
    Player* _player;
    std::vector<UnitWrapper> units;

    PlayerWrapper(Player* player)
    {
        _player = player;

        Unit* first_unit = _player->firstUnit;

        Unit* next_unit = first_unit;
        while (next_unit != _player->lastUnit)
        {
            units.push_back(UnitWrapper(next_unit));
            next_unit++;
        }
    }

    uint16_t getUnitsCount() {
        return _player->unitsCount;
    }

    uint8_t getPlayerId() {
        return _player->playerId;
    }

    uint8_t getTeamId() {
        return _player->playerViewModel->teamId;
    }
};
