#pragma once
#include "TAKCore/Models/Unit.h"

extern "C" __declspec(dllexport) void __stdcall newShowHpFcn(TAKCore::Unit* unit, unsigned int posX, unsigned int posY);

void installShowHpHook();
