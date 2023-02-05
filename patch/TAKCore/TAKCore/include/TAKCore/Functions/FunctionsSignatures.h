#pragma once

#include "TAKCore/common.h"

typedef uintptr_t(__stdcall* createGraphicObjectFromJPG_t)(const char* filePath, int a1);

typedef bool(__thiscall *rendererVTable_offset_0x20_t)(uintptr_t* _this, int a1);
