#include "TAKEnhancedDll/Hooks/ShowHpHook.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

#include "TAKCore/Models/UnitInfo.h"

typedef void (__stdcall *origShowHpFcn_t)(Unit*, unsigned int, unsigned int);

__declspec(dllexport) origShowHpFcn_t origShowHpFcn;

extern "C" __declspec(dllexport) void __stdcall newShowHpFcn(Unit * unit, unsigned int posX, unsigned int posY)
{
    std::string message;
    CustomizableHpBarSetting hpBarSetting;

    if (gameWrapper->isMe(unit->player)) {
        message = "%s is mine.";
        hpBarSetting = currentGameConfig->customizableHpBars.mine;
    }
    else if (gameWrapper->isAlly(unit->player)) {
        message = "%s is ally.";
        hpBarSetting = currentGameConfig->customizableHpBars.ally;
    }
    else {
        message = "%s is enemy.";
        hpBarSetting = currentGameConfig->customizableHpBars.enemy;
    }

    //logger->debug(message.c_str(), unit->unitInfo->name);

    if (hpBarSetting.showMode == ShowMode::Never) {
        return;
    }
    
    if (hpBarSetting.showMode == ShowMode::OnlyIfDamaged) {
        if (unit->currentHealth > unit->unitInfo->maxDamage * 0.99) {
            //logger->debug("%s => Unit is full hp, not going to show.");
            return;
        }
    }

    gameWrapper->setHpBarColor(unit->player, hpBarSetting);

    origShowHpFcn(unit, posX, posY);
}

void installShowHpHook()
{
    origShowHpFcn = (origShowHpFcn_t) (0x0FCF50 + baseAddress);

    MemoryHandler::insertFunctionCall((DWORD) &newShowHpFcn, 0x0FCD6C);
}
