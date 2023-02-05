#include "TAKEnhancedDll/Wrappers/PlayerWrapper.h"

PlayerWrapper::PlayerWrapper(Player* player)
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

uint16_t PlayerWrapper::getUnitsCount() {
    return _player->unitsCount;
}

uint8_t PlayerWrapper::getPlayerId() {
    return _player->playerId;
}

uint8_t PlayerWrapper::getTeamId() {
    return _player->playerViewModel->teamId;
}