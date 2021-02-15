#pragma once
#include "HelperFeatures.h"
#include "RandomRace.h"
#include "OffscreenFix.h"
#include "SearchBox.h"

#define VK_F 0x46
#define VK_K 0x4B
#define VK_O 0x4F
#define VK_R 0x52
#define VK_S 0x53

void initializeHelper()
{
	while (true)
	{
		if (settings.OffscreenFix && gameHasLoaded)
		{
			OffscreenFix();
		}

		if (isKeyDown(VK_MENU))
		{
			if (isKeyDown(VK_RETURN))
			{
				ToggleFullscreen();
			}
		}

		if (isKeyDown(VK_CONTROL))
		{
			if (isKeyDown(VK_S))
			{
				PrintMouseHoveredUnitAddress();
			}
			else if (isKeyDown(VK_F))
			{
				TryToInitializeSearchBox();
			}
			else if (isKeyDown(VK_R))
			{
				TryToChooseRandomRace();
			}
			else if (isKeyDown(VK_K))
			{
				// ToggleSelectedUnitAura();
			}
		}

		while (isKeyDown(VK_RETURN) || isKeyDown(VK_R) || isKeyDown(VK_S) || isKeyDown(VK_K))
		{
			Sleep(10);
		}

		Sleep(10);
	}
}