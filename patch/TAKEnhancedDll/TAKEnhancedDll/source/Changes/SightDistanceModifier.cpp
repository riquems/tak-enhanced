#include "TAKEnhancedDll/Changes/SightDistanceModifier.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

extern "C" __declspec(dllexport) void __stdcall sightDistanceModifier()
{
    uint16_t sight;

    __asm {
        push eax
        mov dx, word ptr ds:[edx + 0x226]
        mov sight, dx
    }

    sight *= currentGameConfig->modifiers.unitSight;

    __asm {
        mov dx, sight
        mov word ptr ds:[ecx + 0x1C], dx
        pop eax
    }
}

void applySightDistanceModifier() {
    MemoryHandler::fillWithNOPs(0x0C66EB, 0x0C66F6);

    MemoryHandler::insertFunctionCall((DWORD) &sightDistanceModifier, 0x0C66EB);
}
