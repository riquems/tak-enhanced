#include "TAKEnhancedDll/Changes/WorkerTimeModifier.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"

extern "C" __declspec(dllexport) void __stdcall workerTimeModifierEdx()
{
    float workerTime;

    __asm {
        push eax
        mov ebx, dword ptr ds:[edx + 0x21A]
        mov workerTime, ebx
    }

    workerTime *= currentGameConfig->modifiers.workerTime;

    __asm {
        fld workerTime
        pop eax
    }
}

extern "C" __declspec(dllexport) void __stdcall workerTimeModifierEcx()
{
    float workerTime;

    __asm {
        push eax
        mov ebx, dword ptr ds : [ecx + 0x21A]
        mov workerTime, ebx
    }

    workerTime *= currentGameConfig->modifiers.workerTime;

    __asm {
        fld workerTime
        pop eax
    }
}

void applyWorkerTimeModifier() {
    // Ground moving units
    MemoryHandler::fillWithNOPs(0x005B70, 0x005B76);

    MemoryHandler::insertFunctionCall((DWORD)&workerTimeModifierEdx, 0x005B70);

    // Flying units
    MemoryHandler::fillWithNOPs(0x01F68C, 0x01F692);

    MemoryHandler::insertFunctionCall((DWORD)&workerTimeModifierEcx, 0x01F68C);

    // Building units
    MemoryHandler::fillWithNOPs(0x002016, 0x00201C);

    MemoryHandler::insertFunctionCall((DWORD)&workerTimeModifierEdx, 0x002016);
}
