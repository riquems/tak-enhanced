#pragma once
#include "./Changes/HelperFeatures.h"
#include "./Changes/RandomRace.h"
#include "./Changes/OffscreenFix.h"
#include "./Changes/SearchBox.h"
#include "./Changes/BuildingsShortcuts.h"

/*********************************************************
 
	The TA:K Enhanced Service is a service which will 
	be running while the game is running, doing several
	different tasks.

**********************************************************/

#define VK_F 0x46
#define VK_K 0x4B
#define VK_O 0x4F
#define VK_R 0x52
#define VK_S 0x53

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

std::map<int, int> buildingKeys = { std::pair<int, int>(VK_0, 0),
									std::pair<int, int>(VK_1, 1),
									std::pair<int, int>(VK_2, 2),
									std::pair<int, int>(VK_3, 3),
									std::pair<int, int>(VK_4, 4),
									std::pair<int, int>(VK_5, 5),
									std::pair<int, int>(VK_6, 6),
									std::pair<int, int>(VK_7, 7),
									std::pair<int, int>(VK_8, 8),
									std::pair<int, int>(VK_9, 9) };

// Keys that should fire once only
std::vector<int> singleShotKeys = { VK_RETURN,
									VK_R,
									VK_S,
									VK_K,
									VK_0,
									VK_1,
									VK_2,
									VK_3,
									VK_4,
									VK_5,
									VK_6,
									VK_7,
									VK_8,
									VK_9 };

void startTakEnhancedService()
{
	while (true)
	{
		if (!players_wrappers.empty()) {
			if (players_wrappers[0]._player->unitsCount > 0) {
				match_has_started = true;
			}
		}

		if (settings.OffscreenFix && match_has_started)
		{
			startOffscreenMonitorThread();
		}

		for (std::pair<int, int> keyValue : buildingKeys)
		{
			if (isKeyDown(keyValue.first))
			{
				SelectBuilding(keyValue.second);
			}
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

		bool singleShotKeysStillBeingHold = [&]()->bool
		{
			for (int key : singleShotKeys)
			{
				if (isKeyDown(key))
				{
					return true;
				}
			}

			return false;
		}();

		while (singleShotKeysStillBeingHold)
		{
			Sleep(10);
		}

		Sleep(10);
	}
}