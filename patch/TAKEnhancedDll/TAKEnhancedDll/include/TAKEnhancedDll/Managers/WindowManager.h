#pragma once

#include "TAKCore/Models/UI/GameInterfaceHandler.h"
#include "TAKCore/Models/UI/Window.h"

#include "TAKCore/Functions/FunctionsOffsets.h"

#include <iostream>

class WindowManager
{
    GameInterfaceHandler* uiHandler;
    uintptr_t baseAddress;

public:
    WindowManager(GameInterfaceHandler* uiHandler, uintptr_t baseAddress);

    Window* getChildWindow(const Window* window, const char* name);
    Window* getCurrentWindow();
};
