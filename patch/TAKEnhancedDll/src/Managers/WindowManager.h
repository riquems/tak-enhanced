#pragma once

#include "../Context.h"

#include "Models/UI/Window.h"
#include "Models/UI/Gadget.h"

#include "Functions/FunctionsOffsets.h"

#include <iostream>

class WindowManager
{
public:
    WindowManager() {}

    std::shared_ptr<Gadget*> getGadget(Window* window, const char* name);
    Window* getCurrentWindow();
};

std::shared_ptr<Gadget*> WindowManager::getGadget(Window* window, const char* name)
{
    uintptr_t windowAddr = (uintptr_t) window;

    __asm {
        PUSH ECX
        MOV  ECX, windowAddr
    }

    uintptr_t (__stdcall *getGadget)(const char*, int) = (uintptr_t (__stdcall *)(const char*, int)) (FunctionsOffsets::getGadget + baseAddress);
    uintptr_t gadgetAddr = getGadget(name, 0);

    __asm {
        POP ECX
    }

    if (gadgetAddr == 0)
        return nullptr;

    Gadget* gadgetPtr = (Gadget*) gadgetAddr;
    std::shared_ptr<Gadget*> gadget = std::make_shared<Gadget*>(gadgetPtr);
    return gadget;
}

Window* WindowManager::getCurrentWindow()
{
    WindowHandler* windowHandler = uiHandler->windowHandler;

    if (windowHandler == nullptr) {
        return nullptr;
    }

    Gadget* focusedGadget = windowHandler->focusedGadget;

    if (focusedGadget == nullptr) {
        return nullptr;
    }

    return focusedGadget->parent;
}