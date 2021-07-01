#pragma once
#include "Models/PlayerViewModel.h"
#include "ModelsExtensions/WindowExtensions.h"

void TryToChooseRandomRace()
{
    Window* currentWindow = GetWindowCurrentWindow();

    if (currentWindow == nullptr)
    {
        return;
    }

    int numberOfSides = GetNumberOfSides();
    Side* sides = GetSides();

    std::vector<int> playableRaces;

    for (int i = 0; i < numberOfSides; i++)
    {
        if (strcmp(sides[i].commander, "") != 0) // is a playable race
        {
            playableRaces.push_back(i);
        }
    }

    if (WindowExtensions::isBattleMenu(currentWindow, baseAddress))
    {
        DWORD* gamePtr = (DWORD*) (0x22D55C + baseAddress);
        Player* players = (Player*) (*gamePtr + 0x2404);

        srand(HelperFunctions::GetMilliseconds());

        int newSideId;
        do {
            newSideId = rand() % playableRaces.size();

        } while (newSideId == players->playerViewModel->sideId); // never the same race

        players->playerViewModel->sideId = playableRaces[newSideId];
    }
}