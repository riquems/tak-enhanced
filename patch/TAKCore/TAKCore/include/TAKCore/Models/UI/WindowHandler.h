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
    Window* focusedWindow;           // 0x10
    Window* clickedWindow;           // 0x14
    Window* mouseHoveredWindow;      // 0x18
    char padding2[4];                // 0x1C
    Window** firstWindow;            // 0x20
    Window** lastWindow;             // 0x24
};

// <baseAddress> + 001756D0 -> gets clickedWindow
// <baseAddress> + 001756B0 -> sets clickedWindow to 0
