#pragma once

#include "../../common.h"

class Window;

class BuildMenu
{
public:
    uintptr_t* vTable;        // 0x00
    char padding1[0x04];      // 0x04
    char padding2[0x04];      // 0x08
    char padding3[0x04];      // 0x0C
    char padding4[0x04];      // 0x10
    bool visible;             // 0x14
    char padding5[0x13];      // 0x15
    Window* parent;           // 0x28
    char padding6[0x04];
    uintptr_t* children;
    uintptr_t* last;
};