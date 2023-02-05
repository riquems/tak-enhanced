#pragma once

#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

#include "TAKCore/Models/UnitInfo.h"

typedef void (__stdcall *origShowHpFcn_t)(Unit*, unsigned int, unsigned int);

__declspec(dllexport) origShowHpFcn_t origShowHpFcn;

extern "C" __declspec(dllexport) void __stdcall newShowHpFcn(Unit* unit, unsigned int posX, unsigned int posY)
{
    if (gameWrapper->isMe(unit->player)) {
        logger->debug("%s is mine.", unit->unitInfo->name);

        if (currentGameConfig->customizableHpBars.mine.showMode == ShowMode::Never) {
            return;
        }
        else if (currentGameConfig->customizableHpBars.mine.showMode == ShowMode::OnlyIfDamaged) {
            if (unit->currentHealth > unit->unitInfo->maxDamage * 0.99) {
                logger->debug("%s => Unit is full hp, not going to show.", unit->unitInfo->name);
                return;
            }
        }

        gameWrapper->setHpBarColor(unit->player, currentGameConfig->customizableHpBars.mine);
    }

    if (gameWrapper->isAlly(unit->player)) {
        logger->debug("%s is ally.", unit->unitInfo->name);

        if (currentGameConfig->customizableHpBars.ally.showMode == ShowMode::Never) {
            return;
        }
        else if (currentGameConfig->customizableHpBars.ally.showMode == ShowMode::OnlyIfDamaged) {
            if (unit->currentHealth > unit->unitInfo->maxDamage * 0.99) {
                logger->debug("%s => Unit is full hp, not going to show.", unit->unitInfo->name);
                return;
            }
        }

        gameWrapper->setHpBarColor(unit->player, currentGameConfig->customizableHpBars.ally);
    }

    if (gameWrapper->isEnemy(unit->player)) {
        logger->debug("%s is enemy.", unit->unitInfo->name);

        if (currentGameConfig->customizableHpBars.enemy.showMode == ShowMode::Never) {
            return;
        }
        else if (currentGameConfig->customizableHpBars.enemy.showMode == ShowMode::OnlyIfDamaged) {
            if (unit->currentHealth > unit->unitInfo->maxDamage * 0.99) {
                logger->debug("%s => Unit is full hp, not going to show.", unit->unitInfo->name);
                return;
            }
        }

        gameWrapper->setHpBarColor(unit->player, currentGameConfig->customizableHpBars.enemy);
    }

    origShowHpFcn(unit, posX, posY);
}

void installShowHpHook()
{
    origShowHpFcn = (origShowHpFcn_t) (0x0FCF50 + baseAddress);

    MemoryHandler::insertFunctionCall((DWORD) &newShowHpFcn, 0x0FCD6C);
}
