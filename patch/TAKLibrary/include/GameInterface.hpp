#include "GlobalPointers/GlobalPointers.h"
#include "Models/UI/GameInterfaceHandler.h"
#include "Models/UI/Window.h"

namespace GameInterface
{
    Window* GetWindow(const char* name, uintptr_t baseAddress);
}