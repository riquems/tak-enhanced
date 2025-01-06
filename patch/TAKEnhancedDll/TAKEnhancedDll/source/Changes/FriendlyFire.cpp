#include "TAKEnhancedDll/Changes/FriendlyFire.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKEnhancedLibrary/Units/Unit.hpp"
#include "TAKEnhancedLibrary/Players/Players.hpp"
#include "TAKEnhancedLibrary/DamageTypes.hpp"

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

struct DamageUnitArgs2
{
    TAKCore::Weapon* weapon;    // 0x00
    char padding1[0x8E];        // 0x04
    uint8_t subjectPlayerIndex; // 0x92
};

// Obsolete
struct DamageUnitArgs
{
    char padding1[0x01];        // 0x00
    uint16_t targetUnitId;      // 0x01
    uint16_t subjectUnitId;     // 0x03
    char padding2[0x03];        // 0x05
    uint8_t damageType;         // 0x08
    char padding3[0x0B];        // 0x09
    TAKCore::Unit* subject;     // 0x14
    TAKCore::Unit* target;      // 0x18
    char padding4[0x0C];        // 0x1C
    DamageUnitArgs2* otherArgs; // 0x28
};

extern "C" __declspec(dllexport) bool __stdcall shouldDamageExt(DamageUnitArgs2* args, TAKCore::Unit* target) {
    logger->debug("[FriendlyFire] Friendly Fire Handler Started!");

    logger->debug("[FriendlyFire] Weapon: %s (damageType: %d)", args->weapon->name, args->weapon->damageType);

    if (args->weapon->damageType == DamageType::ExplodeAs) {
        logger->debug("[FriendlyFire] Damage type not eligible, skipping.");
        return true;
    }

    logger->debug("[FriendlyFire] Subject Player Index: %d", args->subjectPlayerIndex);
    logger->debug("[FriendlyFire] Target Player Index: %d", target->playerIndex);

    auto players = TAKEnhancedLibrary::GetPlayers();

    auto maybeSubjectPlayer = dky::find(players, [&](const std::shared_ptr<Player>& player) -> bool {
        return player->raw->index == args->subjectPlayerIndex;
    });

    if (!maybeSubjectPlayer.has_value()) {
        logger->debug("[FriendlyFire] Couldn't find the player responsible for causing the damage when looking for player with index %d.", args->subjectPlayerIndex);
        return false;
    }

    auto maybeTargetPlayer = dky::find(players, [&](const std::shared_ptr<Player>& player) -> bool {
        return player->raw->index == target->playerIndex;
    });

    if (!maybeTargetPlayer.has_value()) {
        logger->debug("[FriendlyFire] Couldn't find the player that took the damage when looking for player with index %d.", target->playerIndex);
        return false;
    }

    auto subjectPlayer = maybeSubjectPlayer.value();
    auto targetPlayer = maybeTargetPlayer.value();

    logger->debug("[FriendlyFire] Subject Player: %s", subjectPlayer->raw->name);
    logger->debug("[FriendlyFire] Target Player: %s", targetPlayer->raw->name);

    if (!currentGameConfig->friendlyFire.selfDamage
        && TAKEnhancedLibrary::IsMe(subjectPlayer)
        && targetPlayer->id() == subjectPlayer->id())
    {
        logger->debug("[FriendlyFire] Not dealing damage because self damage is off and the unit is attacking your own units!");
        return false;
    }

    if (!currentGameConfig->friendlyFire.allyDamage
        && TAKEnhancedLibrary::AreAllies(subjectPlayer, targetPlayer))
    {
        logger->debug("[FriendlyFire] Not dealing damage because ally damage is off and the units are allies.");
        return false;
    }

    logger->debug("[FriendlyFire] Friendly Fire Handler Finished!");
    return true;
}

namespace shouldDamageSingleTrampolineNs {
    extern DWORD skip = 0;
    extern DWORD goBack = 0;
}

extern "C" __declspec(naked, dllexport) void __stdcall shouldDamageSingleTrampoline() {
    __asm {
        pushad

        push edi
        push esi

        call shouldDamageExt
        test eax, eax

        popad

        jnz goBack
        jmp shouldDamageSingleTrampolineNs::skip

     goBack:
        push 0x3F800000

        jmp shouldDamageSingleTrampolineNs::goBack
    }
}

namespace shouldDamageAoeTrampolineNs {
    extern DWORD skip = 0;
    extern DWORD goBack = 0;
}

extern "C" __declspec(naked, dllexport) void __stdcall shouldDamageAoeTrampoline() {
    __asm {
        pushad

        push esi
        push edi

        call shouldDamageExt
        test eax, eax

        popad

        jnz goBack
        jmp shouldDamageAoeTrampolineNs::skip

    goBack:
        mov eax, dword ptr[ebp + 0x0C]
        test eax, eax

        jmp shouldDamageAoeTrampolineNs::goBack
    }
}

void applyFriendlyFirePatch() {
    // patch for single damage handling
    MemoryHandler::writeJMP(0x12A46E, (DWORD)&shouldDamageSingleTrampoline - baseAddress);
    shouldDamageSingleTrampolineNs::goBack = baseAddress + 0x12A473;
    shouldDamageSingleTrampolineNs::skip = baseAddress + 0x12A4C9;

    // patch for aoe damage handling
    MemoryHandler::writeJMP(0x12A0B0, (DWORD)&shouldDamageAoeTrampoline - baseAddress);
    shouldDamageAoeTrampolineNs::goBack = baseAddress + 0x12A0B5;
    shouldDamageAoeTrampolineNs::skip = baseAddress + 0x12A0CC;

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
