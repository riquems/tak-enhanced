#include "TAKEnhancedDll/Managers/WindowManager.h"

WindowManager::WindowManager(GameInterfaceHandler* uiHandler, uintptr_t baseAddress)
    : uiHandler(uiHandler), baseAddress(baseAddress) {}

Window* WindowManager::getChildWindow(const Window* window, const char* name)
{
    uintptr_t windowAddr = (uintptr_t) window;

    __asm {
        PUSH ECX
        MOV  ECX, windowAddr
    }

    uintptr_t (__stdcall *getChildWindow)(const char*, int) = (uintptr_t (__stdcall *)(const char*, int)) (FunctionsOffsets::getChildWindow + this->baseAddress);
    uintptr_t childWindowAddr = getChildWindow(name, 0);

    __asm {
        POP ECX
    }

    if (childWindowAddr == 0)
        return nullptr;

    return (Window*) childWindowAddr;
}

Window* WindowManager::getCurrentWindow()
{
    WindowHandler* windowHandler = this->uiHandler->windowHandler;

    if (windowHandler == nullptr) {
        return nullptr;
    }

    Window* focusedWindow = windowHandler->focusedWindow;

    if (focusedWindow == nullptr) {
        return nullptr;
    }

    return focusedWindow->parent;
}