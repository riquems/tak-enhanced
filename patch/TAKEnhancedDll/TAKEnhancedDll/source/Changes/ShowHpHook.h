#pragma once

#include "../Context.h"
#include "../MemoryHandler.h"

#include "Models/UnitInfo.h"

typedef void (__stdcall *origShowHpFcn_t)(Unit*, unsigned int, unsigned int);

__declspec(dllexport) origShowHpFcn_t origShowHpFcn;

extern "C" __declspec(dllexport) void __stdcall newShowHpFcn(Unit* unit, unsigned int posX, unsigned int posY)
{
    if (settings.showHpOptions & SHOW_ONLY_IF_DAMAGED) {
        if (unit->currentHealth > unit->unitInfo->maxDamage * 0.99) {
            // std::cout << unit->unitInfo->name << " => Unit is full hp, not going to show." << std::endl;
            return;
        }
    }

    if (!(settings.showHpOptions & SHOW_PLAYER)) {
        if (unit->player->playerId == 0) {
            // std::cout << unit->unitInfo->name << " => Player unit, not going to show." << std::endl;
            return;
        }
    }

    if (!(settings.showHpOptions & SHOW_ALLIES)) {
        bool isAlly = false;

        uint8_t myTeamId = gameWrapper->players[0].getTeamId();
        uint8_t unitPlayerTeamId = unit->player->playerViewModel->teamId;

        if (unit->player->playerId != 0 && myTeamId == unitPlayerTeamId && unitPlayerTeamId != 4) { // 4 = No team
            isAlly = true;
        }

        if (isAlly) {
            // std::cout << unit->unitInfo->name << " => Ally unit, not going to show." << std::endl;
            return;
        }
    }

    if (!(settings.showHpOptions & SHOW_ENEMIES)) {
        bool isEnemy = false;

        uint8_t myTeamId = gameWrapper->players[0].getTeamId();
        uint8_t unitPlayerTeamId = unit->player->playerViewModel->teamId;

        if (myTeamId != unitPlayerTeamId || unit->player->playerId != 0 && unitPlayerTeamId == 4) {
            isEnemy = true;
        }

        if (isEnemy) {
            // std::cout << unit->unitInfo->name << " => Enemy unit, not going to show." << std::endl;
            return;
        }
    }

    origShowHpFcn(unit, posX, posY);
}

void installShowHpHook()
{
    origShowHpFcn = (origShowHpFcn_t) (0x0FCF50 + baseAddress);

    MemoryHandler::insertFunctionCall((DWORD) &newShowHpFcn, 0x0FCD6C);
}
