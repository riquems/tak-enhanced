#pragma once

#include "../Context.h"
#include "../MemoryHandler.h"

#include "Models/UnitInfo.h"

typedef void (__stdcall *origShowHpFcn_t)(Unit*, unsigned int, unsigned int);

__declspec(dllexport) origShowHpFcn_t origShowHpFcn;

extern "C" __declspec(dllexport) void __stdcall newShowHpFcn(Unit* unit, unsigned int posX, unsigned int posY)
{
    if (gameWrapper->isMe(unit->player)) {
        logger.debug("%s is mine.", unit->unitInfo->name);

        if (settings.myHpOptions.showHpOption == NEVER_SHOW) {
            return;
        }
        else if (settings.myHpOptions.showHpOption == SHOW_ONLY_IF_DAMAGED) {
            if (unit->currentHealth > unit->unitInfo->maxDamage * 0.99) {
                logger.debug("%s => Unit is full hp, not going to show.", unit->unitInfo->name);
                return;
            }
        }

        gameWrapper->setHpBarColor(unit->player, settings.myHpOptions.hpColorOption);
    }

    if (gameWrapper->isAlly(unit->player)) {
        logger.debug("%s is ally.", unit->unitInfo->name);

        if (settings.allyHpOptions.showHpOption == NEVER_SHOW) {
            return;
        }
        else if (settings.allyHpOptions.showHpOption == SHOW_ONLY_IF_DAMAGED) {
            if (unit->currentHealth > unit->unitInfo->maxDamage * 0.99) {
                logger.debug("%s => Unit is full hp, not going to show.", unit->unitInfo->name);
                return;
            }
        }

        gameWrapper->setHpBarColor(unit->player, settings.allyHpOptions.hpColorOption);
    }

    if (gameWrapper->isEnemy(unit->player)) {
        logger.debug("%s is enemy.", unit->unitInfo->name);

        if (settings.enemyHpOptions.showHpOption == NEVER_SHOW) {
            return;
        }
        else if (settings.enemyHpOptions.showHpOption == SHOW_ONLY_IF_DAMAGED) {
            if (unit->currentHealth > unit->unitInfo->maxDamage * 0.99) {
                logger.debug("%s => Unit is full hp, not going to show.", unit->unitInfo->name);
                return;
            }
        }

        gameWrapper->setHpBarColor(unit->player, settings.enemyHpOptions.hpColorOption);
    }

    origShowHpFcn(unit, posX, posY);
}

void installShowHpHook()
{
    origShowHpFcn = (origShowHpFcn_t) (0x0FCF50 + baseAddress);

    MemoryHandler::insertFunctionCall((DWORD) &newShowHpFcn, 0x0FCD6C);
}
