#pragma once
#include "MemoryHandler.h"
#include "Functions/FunctionsOffsets.h"
#include "Functions/NewFunctions.h"
#include "Models/Mission.h"
#include "Models/NavGoal.h"
#include "Models/GameMath.h"
#include "Models/Weapon.h"
#include "Models/MovementHandler.h"

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

extern "C" __declspec(dllexport) void __stdcall createNavGoalRingAdjusted(Mission* mission)
{
	DWORD createNavGoalRingFunctionAddress = FunctionsOffsets::createNavGoalRing + baseAddress;

	Unit* unit = mission->unit;

	uint8_t selectedWeaponId = (unit->encodedSelectedWeaponId >> 6) % 3;

	uint8_t offset = 0x1C * selectedWeaponId;

	uint32_t weapon1Addr = (uint32_t) &(unit->weapon1);

	Weapon* weapon = *(Weapon**) (weapon1Addr + offset);

	uint32_t range = weapon->range;
	uint32_t minRange = settings.forced_minrange_for_melees;
	MapPosition* xDestination = &(mission->targetUnit->xMapPosition);

	__asm {
		push minRange        // minRange
		push range           // range
		push xDestination    // mission.target.xDestination
		mov ecx, mission     // mission
		call createNavGoalRingFunctionAddress
	}
}

extern "C" __declspec(dllexport) void __stdcall createNavGoalRingWithIncreasingMinDistance(Mission* mission)
{
	DWORD canAttackFunctionAddress = FunctionsOffsets::canAttack + baseAddress;
	DWORD createNavGoalRingFunctionAddress = FunctionsOffsets::createNavGoalRing + baseAddress;

	Unit* unit = mission->unit;
	Unit* target = mission->targetUnit;

	uint8_t selectedWeaponId = (unit->encodedSelectedWeaponId >> 6) % 3;

	uint8_t offset = 0x1C * selectedWeaponId;

	uint32_t weapon1Addr = (uint32_t) & (unit->weapon1);

	Weapon* weapon = *(Weapon**) (weapon1Addr + offset);

	int cannotAttack = 0;
	__asm {
		push weapon
		push target
		push unit
		call canAttackFunctionAddress
		mov cannotAttack, eax   // 0 = can attack, 1 = cannot attack
	}

	NavGoal* lastNavGoal = unit->movementHandler->pathNavigator->navGoal;

	if (cannotAttack && lastNavGoal == nullptr)
	{
		uint32_t range = weapon->range + 30;
		uint32_t minRange = settings.forced_minrange_for_melees + 30;
		MapPosition* xDestination = &(mission->targetUnit->xMapPosition);

		__asm {
			push minRange        // minRange
			push range           // range
			push xDestination    // mission.target.xDestination
			mov ecx, mission     // mission
			call createNavGoalRingFunctionAddress
		}
	}
}

extern "C" __declspec(dllexport) bool __stdcall new_MeleeCanAttack(Unit* unit, Unit* target, Weapon* weapon)
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
	MemoryHandling::writeShortJMP(Memory(0x004D12, 0x004D14), 0x004D1F);

	MemoryHandling::fillWithNOPs(0x004D29, 0x004D36);

	MemoryHandling::insertOpCode(MemoryHandling::OpCode::PUSH_ESI, 0x4D29);

	MemoryHandling::insertFunctionCall((DWORD) &createNavGoalRingAdjusted, 0x004D2A);

	// Updates the path navigator regularly
	MemoryHandling::fillWithNOPs(0x004BA9, 0x004BB6);

	MemoryHandling::insertOpCode(MemoryHandling::OpCode::PUSH_ESI, 0x4BA9);

	MemoryHandling::insertFunctionCall((DWORD) &createNavGoalRingAdjusted, 0x004BAA);

	// 3rd point
	MemoryHandling::writeJZ(Memory(0x04A5A, 0x04A60), 0x04B46);

	MemoryHandling::fillWithNOPs(0x004B46, 0x004B4F);

	MemoryHandling::insertOpCode(MemoryHandling::OpCode::PUSH_ESI, 0x4B46);
	MemoryHandling::insertFunctionCall((DWORD) &createNavGoalRingWithIncreasingMinDistance, 0x004B47);

	// Replace melee can attack function
	MemoryHandling::write((DWORD) &new_MeleeCanAttack, 0x01F3B04);

	logger.log("Melee Stuck fix applied.");
}

