#include "TAKEnhancedDll/Hooks/ShowHpHook.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKEnhancedDll/Wrappers/GameWrapper.h"
#include "TAKEnhancedLibrary/Players/Players.hpp"
#include "TAKEnhancedLibrary/Units/Unit.hpp"
#include "TAKEnhancedLibrary/Graphics/Graphics.hpp"

#include "TAKCore/Models/UnitInfo.h"

using namespace TAKEnhancedLibrary;

typedef void (__stdcall *origShowHpFcn_t)(TAKCore::Unit*, unsigned int, unsigned int);

__declspec(dllexport) origShowHpFcn_t origShowHpFcn;

extern "C" __declspec(dllexport) void __stdcall newShowHpFcn(TAKCore::Unit* rawUnit, unsigned int posX, unsigned int posY)
{
    auto unit = std::make_shared<Unit>(rawUnit);

    std::string message;
    CustomizableHpBarSetting hpBarSetting;

    if (TAKEnhancedLibrary::IsMe(unit->player())) {
        message = "%s is mine.";
        hpBarSetting = currentGameConfig->customizableHpBars.mine;
    }
    else if (TAKEnhancedLibrary::IsAlly(unit->player())) {
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
        if (unit->hp() > unit->maxHp() * 0.99) {
            //logger->debug("%s => Unit is full hp, not going to show.");
            return;
        }
    }

    TAKEnhancedLibrary::hpBarRenderer->setNextHpBarColor(unit->player(), hpBarSetting);

    origShowHpFcn(unit->raw, posX, posY);
}

void installShowHpHook()
{
    origShowHpFcn = (origShowHpFcn_t) (0x0FCF50 + baseAddress);

    MemoryHandler::insertFunctionCall((DWORD) &newShowHpFcn, 0x0FCD6C);
}
