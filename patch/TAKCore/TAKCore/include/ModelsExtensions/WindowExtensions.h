#pragma once

#include "../Models/UI/Window.h"
#include "ChooseMapMenuExtensions.h"
#include "BattleMenuExtensions.h"
#include "InGameDesktopExtensions.h"

namespace WindowExtensions
{
    bool isChooseMapMenu(Window* window, uint32_t baseAddress)
    {
        return *(window->vTable) == (ChooseMapMenuExtensions::vTableFcnAddresses[0] + baseAddress);
    }

    bool isBattleMenu(Window* window, uint32_t baseAddress)
    {
        return *(window->vTable) == (BattleMenuExtensions::vTableFcnAddresses[0] + baseAddress);
    }

    bool isInGameDesktop(Window* window, uint32_t baseAddress)
    {
        return *(window->vTable) == (InGameDesktopExtensions::vTableFcnAddresses[0] + baseAddress);
    }
};

