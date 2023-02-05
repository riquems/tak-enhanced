#include "TAKEnhancedDll/Changes/RandomRace.hpp"

#include "TAKEnhancedDll/Managers/WindowManager.h"
#include "TAKCore/Models/PlayerViewModel.h"
#include "TAKCore/ModelsExtensions/WindowExtensions.h"
#include "TAKEnhancedDll/GlobalState.hpp"

void TryToChooseRandomRace()
{
    std::shared_ptr<WindowManager> windowManager = std::make_shared<WindowManager>(uiHandler, baseAddress);

    Window* currentWindow = windowManager->getCurrentWindow();

    if (currentWindow == nullptr)
    {
        return;
    }

    int numberOfSides = gameWrapper->getGame()->getNumberOfSides();
    Side* sides = gameWrapper->getGame()->getSides();

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