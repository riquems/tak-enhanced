#pragma once
#include "TAKCore/Models/Unit.h"

extern "C" __declspec(dllexport) void __stdcall newShowHpFcn(Unit * unit, unsigned int posX, unsigned int posY);

void installShowHpHook();
