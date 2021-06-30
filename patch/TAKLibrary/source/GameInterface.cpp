#include "GameInterface.hpp"

Window* GameInterface::GetWindow(const char* name, uintptr_t baseAddress)
{
    GameInterfaceHandler* gameInterfaceHandler = (GameInterfaceHandler*) (GlobalPointers::GameInterfaceHandler + baseAddress);
        
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
