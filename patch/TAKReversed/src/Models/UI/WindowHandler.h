#pragma once
#include "../../common.h"

class Gadget;
class Window;

class WindowHandler
{
public:                              // offset
    char padding1[8];                // 0x00
    uint32_t width;                  // 0x08
    uint32_t height;                 // 0x0C
    Gadget* focusedGadget;           // 0x10
    Gadget* pressedGadget;           // 0x14
    Gadget* mouseHoveredGadget;      // 0x18
    char padding2[4];                // 0x1C
    Window** firstWindow;            // 0x20
    Window** lastWindow;             // 0x24
};