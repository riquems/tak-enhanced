#pragma once
#include "Common.hpp"
#include "TAKCore/Models/UI/Window.h"

class GameInterface
{
    uintptr_t _baseAddress;

public:
    GameInterface(uintptr_t baseAddress);

    Window* getChildWindow(const char* name);
    Window* getFocusedWindow();
};
