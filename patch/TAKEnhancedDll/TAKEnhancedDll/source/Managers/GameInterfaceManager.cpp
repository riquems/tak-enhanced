#include "TAKEnhancedDll/Managers/GameInterfaceManager.h"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "TAKCore/Models/UI/Events/LButtonUpClickArgs.h"

GameInterfaceManager::GameInterfaceManager(GameInterfaceHandler* uiHandler, uintptr_t baseAddress)
{
    this->baseAddress = baseAddress;
    this->gameInterfaceHandler = uiHandler;
    _gameInterface = std::make_shared<GameInterface>(baseAddress);
    _windowManager = std::make_shared<WindowManager>(uiHandler, baseAddress);
}

void GameInterfaceManager::onClickRadioButton(Window* radioButton) {
    onClickRadioButton_t fcn = *(onClickRadioButton_t*) (((uintptr_t)radioButton->vTable) + 0x6C);

    this->gameInterfaceHandler->windowHandler->clickedWindow = radioButton;

    LButtonUpClickArgs args = {
        .x = radioButton->offsetX + 5,
        .y = radioButton->offsetY + 5
    };

    fcn((uintptr_t*) radioButton, &args);
}

Window* GameInterfaceManager::getButton(const Window* parent, const std::string& buttonName)
{
    Window** iterator = parent->children;

    while (*iterator != *parent->last) {
        Window* wnd = *iterator;

        if (strcmp(wnd->name, buttonName.c_str()) == 0) {
            break;
        }

        iterator++;
    }

    return *iterator;
}

Window* GameInterfaceManager::getUnitMenu()
{
    Window* InGameDesktop = _gameInterface->getChildWindow("InGameDesktop");

    if (InGameDesktop == nullptr)
        return nullptr;

    return _windowManager->getChildWindow(InGameDesktop, "UnitMenu");
}

BuildMenu* GameInterfaceManager::getBuildMenu()
{
    Window* InGameDesktop = _gameInterface->getChildWindow("InGameDesktop");

    if (InGameDesktop == nullptr)
        return nullptr;

    Window* window = _windowManager->getChildWindow(InGameDesktop, "BuildMenu");

    BuildMenu* buildMenu = reinterpret_cast<BuildMenu*>(window);

    return buildMenu;
}

bool GameInterfaceManager::isInWriteMode()
{
    Window* focusedGadget = _gameInterface->getFocusedWindow();

    if (focusedGadget == nullptr) {
        return false;
    }

    if (*(uintptr_t*) focusedGadget == (0x1F4B8C + this->baseAddress)) {
        return true;
    }

    return false;
}
