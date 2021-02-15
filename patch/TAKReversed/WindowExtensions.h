#pragma once

#include "Window.h"
#include "ChooseMapMenuExtensions.h"
#include "BattleMenuExtensions.h"

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
};

