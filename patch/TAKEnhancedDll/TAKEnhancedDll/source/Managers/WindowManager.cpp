#include "TAKEnhancedDll/Managers/WindowManager.h"

WindowManager::WindowManager(GameInterfaceHandler* uiHandler, uintptr_t baseAddress)
    : uiHandler(uiHandler), baseAddress(baseAddress) {}

std::shared_ptr<Gadget*> WindowManager::getGadget(Window* window, const char* name)
{
    uintptr_t windowAddr = (uintptr_t) window;

    __asm {
        PUSH ECX
        MOV  ECX, windowAddr
    }

    uintptr_t (__stdcall *getGadget)(const char*, int) = (uintptr_t (__stdcall *)(const char*, int)) (FunctionsOffsets::getGadget + this->baseAddress);
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
    WindowHandler* windowHandler = this->uiHandler->windowHandler;

    if (windowHandler == nullptr) {
        return nullptr;
    }

    Gadget* focusedGadget = windowHandler->focusedGadget;

    if (focusedGadget == nullptr) {
        return nullptr;
    }

    return focusedGadget->parent;
}