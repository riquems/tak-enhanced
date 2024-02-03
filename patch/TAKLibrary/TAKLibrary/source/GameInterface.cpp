#include "GameInterface.hpp"
#include "TAKCore/GlobalPointers/GlobalPointers.h"
#include "TAKCore/Models/UI/GameInterfaceHandler.h"

GameInterface::GameInterface(uintptr_t baseAddress)
{
    _baseAddress = baseAddress;
}

Window* GameInterface::getChildWindow(const char* name)
{
    GameInterfaceHandler* gameInterfaceHandler = (GameInterfaceHandler*) (GlobalPointers::GameInterfaceHandler + _baseAddress);
        
    if (gameInterfaceHandler == nullptr)
        return nullptr;

    WindowHandler* windowHandler = gameInterfaceHandler->windowHandler;
    
    if (windowHandler == nullptr)
        return nullptr;

    Window** nextWindow = windowHandler->firstWindow;
    
    Window* window = nullptr;
    while (nextWindow != windowHandler->lastWindow)
    {
        if (strcmp((*nextWindow)->name, name) == 0) {
            window = *nextWindow;
            break;
        }

        nextWindow++;
    }

    return window;
}

Window* GameInterface::getFocusedWindow()
{
    GameInterfaceHandler* gameInterfaceHandler = (GameInterfaceHandler*) (GlobalPointers::GameInterfaceHandler + _baseAddress);

    if (gameInterfaceHandler == nullptr)
        return nullptr;

    WindowHandler* windowHandler = gameInterfaceHandler->windowHandler;

    if (windowHandler == nullptr)
        return nullptr;

    return windowHandler->focusedWindow;
}
