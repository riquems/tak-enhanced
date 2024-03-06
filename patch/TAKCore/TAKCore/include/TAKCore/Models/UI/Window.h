#pragma once
#include "../../common.h"

class Gadget;

class Window
{
public:                       // offset
    uintptr_t* vTable;        // 0x00
    uint32_t offsetX;         // 0x04
    uint32_t offsetY;         // 0x08
    uint32_t width;           // 0x0C
    uint32_t height;          // 0x10
    bool visible;             // 0x14
    char padding1[0x0F];      // 0x15
    const char* name;         // 0x24
    Window* parent;           // 0x28
    char padding3[0x04];      // 0x2C
    Window** children;         // 0x30
    Window** last;             // 0x34
};
