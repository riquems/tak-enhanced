#pragma once

#include <iostream>
#include "TAKCore/Models/UI/BuildMenu.h"
#include "WindowManager.h"
#include "TAKCore/Models/UI/GameInterfaceHandler.h"
#include "TAKCore/ModelsExtensions/WindowExtensions.h"
#include "GameInterface.hpp"

class GameInterfaceManager
{
    uintptr_t baseAddress;
    std::shared_ptr<GameInterface> _gameInterface;
    std::shared_ptr<WindowManager> _windowManager;

public:
    GameInterfaceManager(GameInterfaceHandler* uiHandler, uintptr_t baseAddress);

    std::shared_ptr<BuildMenu*> getBuildMenu();
    bool isInWriteMode();
};
