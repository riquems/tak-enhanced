#pragma once

#include "TAKCore/Models/UI/Window.h"
#include "ChooseMapMenuExtensions.h"
#include "BattleMenuExtensions.h"
#include "InGameDesktopExtensions.h"

namespace WindowExtensions
{
    bool isChooseMapMenu(Window* window, uint32_t baseAddress);

    bool isBattleMenu(Window* window, uint32_t baseAddress);

    bool isInGameDesktop(Window* window, uint32_t baseAddress);
};
