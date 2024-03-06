#include "TAKEnhancedDll/Changes/ManaModifier.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

extern "C" __declspec(dllexport) void __stdcall manaStorageModifier()
{
    float mogriumStorage;

    __asm {
        mov ebx, dword ptr ds:[eax + 0x206]
        mov mogriumStorage, ebx
    }

    mogriumStorage *= currentGameConfig->modifiers.manaStorage;

    __asm {
        fadd mogriumStorage
    }
}

extern "C" __declspec(dllexport) void __stdcall manaIncomeModifier()
{
    float mogriumIncome;

    __asm {
        mov ebx, dword ptr ds:[eax + 0x20A]
        mov mogriumIncome, ebx
    }

    mogriumIncome *= currentGameConfig->modifiers.manaIncome;

    __asm {
        fadd mogriumIncome
    }
}

void applyManaModifier() {
    applyManaStorageModifier();
    applyManaIncomeModifier();
}


void applyManaStorageModifier() {
    MemoryHandler::fillWithNOPs(0x11D7D3, 0x11D7D9);

    MemoryHandler::insertFunctionCall((DWORD)&manaStorageModifier, 0x11D7D3);
}

void applyManaIncomeModifier() {
    MemoryHandler::fillWithNOPs(0x11D7BB, 0x11D7C1);

    MemoryHandler::insertFunctionCall((DWORD)&manaIncomeModifier, 0x11D7BB);
}
