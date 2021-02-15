#pragma once

#include "GameFunctions.h"
#include "PlayerWrapper.h"

bool offscreenFixThreadRunning = false;

bool playersInitialized = false;
std::vector<PlayerWrapper> playersWrappers;

void InitializePlayersWrappers()
{
	Player* players = GameFunctionsExtensions::GetPlayers();

	Player* nextPlayer = players;
	while (nextPlayer->initialized)
	{
		PlayerWrapper playerWrapper(nextPlayer);

		playersWrappers.push_back(playerWrapper);
		nextPlayer++;
	}
}

void OffscreenFixThread()
{
	while (true)
	{
		if (!playersInitialized)
		{
			InitializePlayersWrappers();
			playersInitialized = true;
		}

		for (int i = 0; i < playersWrappers.size(); i++)
		{
			for (int j = 0; j < playersWrappers[i].units.size(); j++)
			{
				Unit* unit = playersWrappers[i].units[j];

				if (unit != nullptr)
				{
					bool isFlying = unit->walking & 0b10;
					if (isFlying && unit->zMapPosition.mapPosition < unit->yMapPosition.mapPosition * 0.55)
					{
						unit->zMapPosition.mapPosition = 50 + unit->yMapPosition.mapPosition * 0.55;
					}
				}
			}
		}

		Sleep(10);
	}
}

void OffscreenFix()
{
	if (!offscreenFixThreadRunning)
	{
		std::thread offscreenFixThread(OffscreenFixThread);
		offscreenFixThread.detach();

		offscreenFixThreadRunning = true;
	}
}