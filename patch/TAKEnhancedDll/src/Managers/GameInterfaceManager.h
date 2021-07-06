#pragma once

#include <iostream>
#include "Models/UI/BuildMenu.h"
#include "WindowManager.h"
#include "Models/UI/GameInterfaceHandler.h"
#include "ModelsExtensions/WindowExtensions.h"
#include "GameInterface.hpp"

class GameInterfaceManager
{
    std::shared_ptr<GameInterface> _gameInterface;
    std::shared_ptr<WindowManager> _windowManager;

public:
    GameInterfaceManager() {}
    GameInterfaceManager(uintptr_t baseAddress)
    {
        _gameInterface = std::make_shared<GameInterface>(baseAddress);
        _windowManager = std::make_shared<WindowManager>();
    }

    std::shared_ptr<BuildMenu*> getBuildMenu();
};

std::shared_ptr<BuildMenu*> GameInterfaceManager::getBuildMenu()
{
    Window* InGameDesktop = _gameInterface->getWindow("InGameDesktop");

    if (InGameDesktop == nullptr)
        return nullptr;

    std::shared_ptr<Gadget*> gadget = _windowManager->getGadget(InGameDesktop, "BuildMenu");

    std::shared_ptr<BuildMenu*> buildMenu = std::reinterpret_pointer_cast<BuildMenu*>(gadget);

    return buildMenu;
}