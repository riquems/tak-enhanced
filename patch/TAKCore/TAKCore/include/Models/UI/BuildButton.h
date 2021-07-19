#pragma once

#include "../../common.h"

class Window;

class BuildButton
{
public:
    uintptr_t* vTable;
    char padding[0x24];
    Window* parent;
    char padding2[0x04];
    uintptr_t* children;
};