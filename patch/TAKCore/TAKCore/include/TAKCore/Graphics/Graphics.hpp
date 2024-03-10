#pragma once
#include "TAKCore/common.h"

namespace TAKCore
{
    typedef uintptr_t(__stdcall* CreateGraphicObjectFromJPG_t)(const char* filePath, int a1);
    extern const uintptr_t CreateGraphicObjectFromJPG_Offset;

    extern CreateGraphicObjectFromJPG_t CreateGraphicObjectFromJPG;

    extern const uintptr_t HpBarGraphicObj_Offset;
    extern uintptr_t* HpBarGraphicObj;

    typedef bool(__thiscall* rendererVTable_offset_0x20_t)(uintptr_t* _this, int a1);
    extern uintptr_t* RendererDevice;
}
