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
    GameInterfaceHandler* gameInterfaceHandler;
    std::shared_ptr<GameInterface> _gameInterface;
    std::shared_ptr<WindowManager> _windowManager;

public:
    GameInterfaceManager(GameInterfaceHandler* uiHandler, uintptr_t baseAddress);

    void onClickRadioButton(Window* radioButton);
    Window* getButton(const Window* parent, const std::string& button);
    Window* getUnitMenu();
    BuildMenu* getBuildMenu();
    bool isInWriteMode();
};
