#pragma once
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include "TAKCore/Models/Mission.h"
#include "TAKCore/Models/Weapon.h"

extern "C" __declspec(dllexport) void __stdcall createNavGoalRectAdjusted(DWORD mission, DWORD target);

extern "C" __declspec(dllexport) void __stdcall createNavGoalRingAdjusted(Mission * mission);

extern "C" __declspec(dllexport) void __stdcall createNavGoalRingWithIncreasingMinDistance(Mission * mission);

extern "C" __declspec(dllexport) bool __stdcall new_MeleeCanAttack(Unit * unit, Unit * target, Weapon * weapon);

void applyMeleeStuckFix();
