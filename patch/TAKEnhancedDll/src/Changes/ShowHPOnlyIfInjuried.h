#pragma once

#include "../Context.h"
#include "../MemoryHandler.h"

#include "Models/UnitInfo.h"

typedef void (__stdcall *origShowHpFcn_t)(Unit*, unsigned int, unsigned int);

__declspec(dllexport) origShowHpFcn_t origShowHpFcn;

extern "C" __declspec(dllexport) void __stdcall newShowHpFcn(Unit* unit, unsigned int posX, unsigned int posY)
{
    if (unit->currentHealth > unit->unitInfo->maxDamage * 0.95)
        return;

    origShowHpFcn(unit, posX, posY);
}

void applyShowHpOnlyIfInjuried()
{
    origShowHpFcn = (origShowHpFcn_t) (0x0FCF50 + baseAddress);

    MemoryHandler::insertFunctionCall((DWORD) &newShowHpFcn, 0x0FCD6C);
}
