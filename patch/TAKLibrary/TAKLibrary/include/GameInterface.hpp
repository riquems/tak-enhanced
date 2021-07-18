#pragma once
#include "Common.hpp"

#include "GlobalPointers/GlobalPointers.h"
#include "Models/UI/GameInterfaceHandler.h"
#include "Models/UI/Window.h"

class GameInterface
{
    uintptr_t _baseAddress;

public:
    GameInterface(uintptr_t baseAddress);

    Window* getWindow(const char* name);
    Gadget* getFocusedGadget();
};
