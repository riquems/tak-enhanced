#include "TAKEnhancedDll/Changes/FriendlyFire.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKCore/Models/Unit.h"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedLibrary/Units/Unit.hpp"
#include "TAKEnhancedLibrary/Players/Players.hpp"

using namespace TAKEnhancedLibrary;

extern "C" __declspec(dllexport) bool __stdcall weaponShouldPassThrough()
{
    __asm {
        push ecx
        push edx
    }

    TAKCore::Unit* rawSubject = nullptr;
    TAKCore::Unit* rawUnitInTheWay = nullptr;

    __asm {
        mov eax, dword ptr[ebx + 0x7C]
        mov rawSubject, eax
        mov rawUnitInTheWay, edx
    }

    Unit subject(rawSubject);
    Unit unitInTheWay(rawUnitInTheWay);

    bool playersAreTheSame = *subject.player() == *unitInTheWay.player();
    bool allyProjectileCollisionEnabled = currentGameConfig->friendlyFire.allyProjectileCollision;
    bool playersAreAllies = TAKEnhancedLibrary::AreAllies(subject.player(), unitInTheWay.player());

    bool shouldPassThrough = playersAreTheSame || (!allyProjectileCollisionEnabled && playersAreAllies);

    __asm {
        pop edx
        pop ecx
    }

    return shouldPassThrough;
}

struct DamageUnitArgs
{
    char padding1[0x08];
    uint8_t weaponType;
    char padding2[0x0B];
    TAKCore::Unit* subject;
    TAKCore::Unit* target;
};

extern "C" __declspec(dllexport) void __stdcall shouldDamageExt()
{
    DamageUnitArgs* args = nullptr;

    __asm {
        push eax
        push ecx
        push edx
        mov args, edi
    }

    uint8_t weaponType = args->weaponType;
    auto subject = std::make_shared<Unit>(args->subject);
    auto target = std::make_shared<Unit>(args->target);

    if (weaponType == 0x0C)
    {
        // default heal handling
        __asm {
            mov eax, baseAddress
            mov dword ptr[ebp + 0x4], eax
            add dword ptr[ebp + 0x4], 0x11A2F8

            pop edx
            pop ecx
            pop eax

            pop edi
            pop esi
            pop ebx

            mov esp, ebp
            pop ebp

            ret
        }
    }

    // is not Ctrl + D and is not buildings fading away
    if (weaponType != 0x5 && weaponType != 0xB)
    {
        if (!currentGameConfig->friendlyFire.selfDamage
            && TAKEnhancedLibrary::IsMe(subject->player())
            && *target->player() == *subject->player())
        {
            // do nothing
            __asm {
                mov eax, baseAddress
                mov dword ptr[ebp + 0x4], eax
                add dword ptr[ebp + 0x4], 0x11A648

                pop edx
                pop ecx
                pop eax

                pop edi
                pop esi
                pop ebx

                mov esp, ebp
                pop ebp

                ret
            }
        }

        if (!currentGameConfig->friendlyFire.allyDamage && TAKEnhancedLibrary::AreAllies(subject->player(), target->player()))
        {
            // do nothing
            __asm {
                mov eax, baseAddress
                mov dword ptr[ebp + 0x4], eax
                add dword ptr[ebp + 0x4], 0x11A648

                pop edx
                pop ecx
                pop eax

                pop edi
                pop esi
                pop ebx

                mov esp, ebp
                pop ebp

                ret
            }
        }
    }

    // default damage handling
    __asm {
        mov eax, baseAddress
        mov dword ptr[ebp + 0x4], eax
        add dword ptr[ebp + 0x4], 0x11A329

        pop edx
        pop ecx
        pop eax

        pop edi
        pop esi
        pop ebx

        mov esp, ebp
        pop ebp

        ret
    }
}

void applyFriendlyFirePatch() {
    // patch for damage handling
    MemoryHandler::fillWithNOPs(Memory(0x11A2F2, 0x11A2F8));
    MemoryHandler::insertFunctionCall((DWORD)&shouldDamageExt, 0x11A2F2);

    // patch for weapon passing through
    // ground units
    MemoryHandler::fillWithNOPs(Memory(0x12A608, 0x12A618));

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::PUSH_EAX, 0x12A608);
    auto movEdxEsi = ShellCode("89F2", 0x12A609);
    MemoryHandler::writeShellCode(movEdxEsi);

    MemoryHandler::insertFunctionCall((DWORD) &weaponShouldPassThrough, 0x12A60B);

    auto testAlAl = ShellCode("84C0", 0x12A610);
    MemoryHandler::writeShellCode(testAlAl);

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::POP_EAX, 0x12A612);

    MemoryHandler::writeShortJNZ(0x12A613, 0x12A64F);

    // for flying units
    MemoryHandler::fillWithNOPs(Memory(0x12A6A1, 0x12A6AF));

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::PUSH_EAX, 0x12A6A1);

    auto movEdxEax = ShellCode("89C2", 0x12A6A2);
    MemoryHandler::writeShellCode(movEdxEax);

    MemoryHandler::insertFunctionCall((DWORD) &weaponShouldPassThrough, 0x12A6A4);

    auto testAlAl2 = ShellCode("84C0", 0x12A6A9);
    MemoryHandler::writeShellCode(testAlAl2);

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::POP_EAX, 0x12A6AB);

    MemoryHandler::writeShortJNZ(0x12A6AC, 0x12A6F3);
}
