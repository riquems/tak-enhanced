#include "TAKEnhancedDll/Changes/FriendlyFire.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKCore/Models/Unit.h"
#include "TAKEnhancedDll/GlobalState.hpp"

extern "C" __declspec(dllexport) bool __stdcall weaponShouldPassThrough()
{
    __asm {
        push ecx
        push edx
    }

    uint8_t weaponPlayerNumber = 0;
    Unit* unitHit = nullptr;

    __asm {
        mov al, byte ptr [ebx + 0x92]
        mov weaponPlayerNumber, al
        mov unitHit, esi
    }

    bool shouldPassThrough =
        weaponPlayerNumber == unitHit->player->playerId
     || (!currentGameConfig->friendlyFire.allyProjectileCollision && gameWrapper->areAllies(weaponPlayerNumber, unitHit->player->playerId));

    __asm {
        pop ecx
        pop edx
    }

    return shouldPassThrough;
}

struct DamageUnitArgs
{
    char padding1[0x08];
    uint8_t weaponType;
    char padding2[0x0B];
    Unit* subject;
    Unit* target;
};

extern "C" __declspec(dllexport) void __stdcall shouldDamageExt()
{
    DamageUnitArgs* args = nullptr;

    __asm {
        mov args, edi
    }

    uint8_t weaponType = args->weaponType;
    Unit* subject = args->subject;
    Unit* target = args->target;

    if (weaponType == 0x0C)
    {
        // default heal handling
        __asm {
            pop edi
            pop esi
            pop ecx

            mov	esp, ebp
            pop	ebp

            add esp, 0x4
            mov edx, baseAddress
            add edx, 0x11A2F8
            push edx

            ret
        }
    }
    // is not Ctrl + D and is not buildings fading away
    if (weaponType != 0x5 && weaponType != 0xB)
    {
        if (!currentGameConfig->friendlyFire.selfDamage
            && gameWrapper->isMe(subject->player)
            && target->player == subject->player)
        {
            // do nothing
            __asm {
                pop edi
                pop esi
                pop ecx

                mov	esp, ebp
                pop	ebp

                add esp, 0x4
                mov edx, baseAddress
                add edx, 0x11A648
                push edx

                ret
            }
        }

        if (!currentGameConfig->friendlyFire.allyDamage && gameWrapper->areAllies(subject->player, target->player))
        {
            // do nothing
            __asm {
                pop edi
                pop esi
                pop ecx

                mov	esp, ebp
                pop	ebp

                add esp, 0x4
                mov edx, baseAddress
                add edx, 0x11A648
                push edx

                ret
            }
        }
    }

    // default damage handling
    __asm {
        pop edi
        pop esi
        pop ecx

        mov	esp, ebp
        pop	ebp

        add esp, 0x4
        mov edx, baseAddress
        add edx, 0x11A329
        push edx

        ret
    }
}

void applyFriendlyFirePatch() {
    // patch for damage handling
    MemoryHandler::fillWithNOPs(Memory(0x11A2F2, 0x11A2F8));
    MemoryHandler::insertFunctionCall((DWORD)&shouldDamageExt, 0x11A2F2);

    // patch for weapon passing through
    MemoryHandler::fillWithNOPs(Memory(0x12A608, 0x12A618));

    MemoryHandler::insertFunctionCall((DWORD) &weaponShouldPassThrough, 0x12A608);

    auto testAlAl = ShellCode("84C0", 0x12A60D);
    MemoryHandler::writeShellCode(testAlAl);

    MemoryHandler::writeShortJNZ(0x12A60F, 0x12A64F);
}
