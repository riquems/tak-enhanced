#pragma once

#include "TAKCore/common.h"
#include "TAKCore/Models/UI/Events/LButtonUpClickArgs.h"

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

typedef uintptr_t(__stdcall* createGraphicObjectFromJPG_t)(const char* filePath, int a1);

typedef bool(__thiscall *rendererVTable_offset_0x20_t)(uintptr_t* _this, int a1);

typedef void(__stdcall* executeCommand_t)(const char* command, bool console);
