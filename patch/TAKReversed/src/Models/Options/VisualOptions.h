#pragma once

#include "../../common.h"

class VisualOptions
{
public:
    uintptr_t* vTable;
    uint32_t width;
    uint32_t height;
    bool hardwareCursor;
    bool showHealthBars;
    bool antiAliasing;
    bool shadows;
    bool shading;
    bool showBlood;
    bool unknown1;
    bool bilinearFiltering;
};