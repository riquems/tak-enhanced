#include "TAKEnhancedDll/Changes/MeleeStuckFix.hpp"

#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKCore/Functions/FunctionsOffsets.h"
#include "TAKCore/Functions/NewFunctions.h"
#include "TAKCore/Models/Mission.h"
#include "TAKCore/Models/NavGoal.h"
#include "TAKCore/Models/GameMath.h"
#include "TAKCore/Models/Weapon.h"
#include "TAKCore/Models/MovementHandler.h"
#include "TAKCore/Models/PathNavigator.h"

extern "C" __declspec(dllexport) void __stdcall createNavGoalRectAdjusted(DWORD mission, DWORD target)
{
    DWORD createNavGoalRectFunctionAddress = FunctionsOffsets::createNavGoalRect + baseAddress;

    __asm {
        mov ebx, target
        mov edx, [ebx + 0x78]
        mov ebx, [ebx + 0x74]
        add edx, 0x40004
        sub ebx, 0x30003
        push edx
        push ebx
        mov ecx, mission
        call createNavGoalRectFunctionAddress
    }
}

extern "C" __declspec(dllexport) void __stdcall createNavGoalRingAdjusted(TAKCore::Mission* mission)
{
    DWORD createNavGoalRingFunctionAddress = FunctionsOffsets::createNavGoalRing + baseAddress;

    TAKCore::Unit* unit = mission->unit;

    uint8_t selectedWeaponId = (unit->encodedSelectedWeaponId >> 6) % 3;

    uint8_t offset = 0x1C * selectedWeaponId;

    uint32_t weapon1Addr = (uint32_t) &(unit->weapon1);

    TAKCore::Weapon* weapon = *(TAKCore::Weapon**) (weapon1Addr + offset);

    uint32_t range = weapon->range;
    uint32_t minRange = currentGameConfig->meleeStuckFix.forcedMinRangeForMelees;
    TAKCore::MapPosition* xDestination = &(mission->targetUnit->xMapPosition);

    __asm {
        push minRange        // minRange
        push range           // range
        push xDestination    // mission.target.xDestination
        mov ecx, mission     // mission
        call createNavGoalRingFunctionAddress
    }
}

extern "C" __declspec(dllexport) void __stdcall createNavGoalRingWithIncreasingMinDistance(TAKCore::Mission* mission)
{
    DWORD canAttackFunctionAddress = FunctionsOffsets::canAttack + baseAddress;
    DWORD createNavGoalRingFunctionAddress = FunctionsOffsets::createNavGoalRing + baseAddress;

    TAKCore::Unit* unit = mission->unit;
    TAKCore::Unit* target = mission->targetUnit;

    uint8_t selectedWeaponId = (unit->encodedSelectedWeaponId >> 6) % 3;

    uint8_t offset = 0x1C * selectedWeaponId;

    uint32_t weapon1Addr = (uint32_t) & (unit->weapon1);

    TAKCore::Weapon* weapon = *(TAKCore::Weapon**) (weapon1Addr + offset);

    int cannotAttack = 0;
    __asm {
        push weapon
        push target
        push unit
        call canAttackFunctionAddress
        mov cannotAttack, eax   // 0 = can attack, 1 = cannot attack
    }

    TAKCore::NavGoal* lastNavGoal = unit->movementHandler->pathNavigator->navGoal;

    if (cannotAttack && lastNavGoal == nullptr)
    {
        uint32_t range = weapon->range + 30;
        uint32_t minRange = currentGameConfig->meleeStuckFix.forcedMinRangeForMelees + 30;
        TAKCore::MapPosition* xDestination = &(mission->targetUnit->xMapPosition);

        __asm {
            push minRange        // minRange
            push range           // range
            push xDestination    // mission.target.xDestination
            mov ecx, mission     // mission
            call createNavGoalRingFunctionAddress
        }
    }
}

extern "C" __declspec(dllexport) bool __stdcall new_MeleeCanAttack(TAKCore::Unit* unit, TAKCore::Unit* target, TAKCore::Weapon* weapon)
{
    Point unitPosition(unit->xMapPosition.mapPosition, unit->zMapPosition.mapPosition);
    Point targetPosition(target->xMapPosition.mapPosition, target->zMapPosition.mapPosition);

    uint16_t distance = distanceBetweenTwoPoints(unitPosition, targetPosition);
    uint32_t weaponRange = weapon->range;

    uint16_t real_target_xFootprintLength = target->xFootprintLength * 8;
    uint16_t real_target_zFootprintLength = target->zFootprintLength * 8;

    bool target_is_small = real_target_xFootprintLength <= 3 * 8 &&
                           real_target_zFootprintLength <= 3 * 8;

    if (target_is_small)
    {
        if ((distance - 15) > weaponRange)
        {
            __asm {
                xor eax, eax
            }

            return false;
        }
    }
    else
    {
        uint16_t real_unit_xFootprintLength = unit->xFootprintLength * 8;
        uint16_t real_unit_zFootprintLength = unit->zFootprintLength * 8;

        Point l1, r1;
        Point l2, r2;

        l1.x = unitPosition.x - real_unit_xFootprintLength / 2 - weaponRange;
        l1.z = unitPosition.z - real_unit_zFootprintLength / 2 - weaponRange;
        r1.x = unitPosition.x + real_unit_xFootprintLength / 2 + weaponRange;
        r1.z = unitPosition.z + real_unit_zFootprintLength / 2 + weaponRange;

        l2.x = targetPosition.x - real_target_xFootprintLength / 2 - 10;
        l2.z = targetPosition.z - real_target_zFootprintLength / 2 - 60;
        r2.x = targetPosition.x + real_target_xFootprintLength / 2 + 10;
        r2.z = targetPosition.z + real_target_zFootprintLength / 2 + 60;

        if (!doOverlap(l1, r1, l2, r2)) {
            __asm {
                xor eax, eax
            }

            return false;
        }
    }

    __asm {
        xor eax, eax
    }

    return true;
}

void applyMeleeStuckFix()
{
    // First time you click to attack
    MemoryHandler::writeShortJMP(Memory(0x004D12, 0x004D14), 0x004D1F);

    MemoryHandler::fillWithNOPs(0x004D29, 0x004D36);

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::PUSH_ESI, 0x4D29);

    MemoryHandler::insertFunctionCall((DWORD) &createNavGoalRingAdjusted, 0x004D2A);

    // Updates the path navigator regularly
    MemoryHandler::fillWithNOPs(0x004BA9, 0x004BB6);

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::PUSH_ESI, 0x4BA9);

    MemoryHandler::insertFunctionCall((DWORD) &createNavGoalRingAdjusted, 0x004BAA);

    // 3rd point
    MemoryHandler::writeJZ(0x04A5A, 0x04B46);

    MemoryHandler::fillWithNOPs(0x004B46, 0x004B4F);

    MemoryHandler::insertOpCode(MemoryHandler::OpCode::PUSH_ESI, 0x4B46);
    MemoryHandler::insertFunctionCall((DWORD) &createNavGoalRingWithIncreasingMinDistance, 0x004B47);

    // Replace melee can attack function
    MemoryHandler::write((DWORD) &new_MeleeCanAttack, 0x01F3B04);
}

