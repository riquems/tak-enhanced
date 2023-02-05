#include "TAKEnhancedDll/Managers/GameInterfaceManager.h"

GameInterfaceManager::GameInterfaceManager(GameInterfaceHandler* uiHandler, uintptr_t baseAddress)
{
    this->baseAddress = baseAddress;
    _gameInterface = std::make_shared<GameInterface>(baseAddress);
    _windowManager = std::make_shared<WindowManager>(uiHandler, baseAddress);
}

std::shared_ptr<BuildMenu*> GameInterfaceManager::getBuildMenu()
{
    Window* InGameDesktop = _gameInterface->getWindow("InGameDesktop");

    if (InGameDesktop == nullptr)
        return nullptr;

    std::shared_ptr<Gadget*> gadget = _windowManager->getGadget(InGameDesktop, "BuildMenu");

    std::shared_ptr<BuildMenu*> buildMenu = std::reinterpret_pointer_cast<BuildMenu*>(gadget);

    return buildMenu;
}

bool GameInterfaceManager::isInWriteMode()
{
    Gadget* focusedGadget = _gameInterface->getFocusedGadget();

    if (focusedGadget == nullptr) {
        return false;
    }

    if (*(uintptr_t*) focusedGadget == (0x1F4B8C + this->baseAddress)) {
        return true;
    }

    return false;
}
