#pragma once

#include "TAKCore/common.h"
#include "TAKCore/Models/UI/Events/LButtonUpClickArgs.h"
#include "TAKCore/Models/Unit.h"

typedef void(__stdcall* addMission_t)(
    uintptr_t arg1,
    uintptr_t arg2,
    uintptr_t arg3,
    uintptr_t arg4,
    uintptr_t arg5,
    uintptr_t arg6,
    uintptr_t arg7
);

typedef void(__thiscall* onClickRadioButton_t)(uintptr_t* instance, const LButtonUpClickArgs* args);

typedef void(__stdcall* executeCommand_t)(const char* command, bool console);

typedef TAKCore::Unit*(__stdcall* GetMouseHoveredUnit_t)();
