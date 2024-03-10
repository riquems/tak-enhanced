#pragma once

#include "Game.hpp"
#include "TAKCore/Models/Options/GameOptions.h"
#include "TAKCore/Models/Options/DevelopmentOptions.h"

#include "TAKEnhancedLibrary/Players/Player.hpp"
#include "BuildMenuWrapper.h"
#include "BuildButtonWrapper.h"
#include "TAKCore/Functions/FunctionsSignatures.h"
#include <TAKEnhancedDll/Managers/GameInterfaceManager.h>
#include <TAKEnhancedLibrary/Commands/SetUnitStance/SetUnitStanceCommand.hpp>

class MatchWrapper;

class GameWrapper
{
    std::shared_ptr<Game> game;
    uintptr_t baseAddress;

public:
    std::shared_ptr<GameInterfaceManager> gameInterfaceManager;
    std::shared_ptr<MatchWrapper> match;

    GameWrapper(GameInterfaceHandler* uiHandler, uintptr_t baseAddress);

    void onInitialize();

    bool isInWriteMode();
    bool isBuildMenuOpen();

    void selectBuilding(int pos);

    void activateDeveloperMode();

    void setUnitStance(const UnitStance& stance);

    std::shared_ptr<Game> getGame();
};

extern std::shared_ptr<GameWrapper> gameWrapper;
