#include "TAKEnhancedDll/Wrappers/GameWrapper.h"
#include "TAKEnhancedDll/Wrappers/MatchWrapper.h"
#include <TAKEnhancedDll/GlobalState.hpp>

using namespace TAKEnhancedLibrary;

std::shared_ptr<GameWrapper> gameWrapper;

GameWrapper::GameWrapper(GameInterfaceHandler* uiHandler, uintptr_t baseAddress)
{
    this->game = std::make_shared<Game>(baseAddress);
    gameInterfaceManager = std::make_shared<GameInterfaceManager>(uiHandler, baseAddress);

    this->baseAddress = baseAddress;

    match = std::make_shared<MatchWrapper>(this);
}

void GameWrapper::onInitialize()
{
    logger->info("[Event] OnInitialize");
}

bool GameWrapper::isBuildMenuOpen()
{
    BuildMenu* build_menu = gameInterfaceManager->getBuildMenu();

    if (build_menu == nullptr) {
        return false;
    }

    return build_menu->visible;
}

bool GameWrapper::isInWriteMode()
{
    return gameInterfaceManager->isInWriteMode();
}

void GameWrapper::selectBuilding(int pos)
{
    BuildMenu* build_menu = gameInterfaceManager->getBuildMenu();

    if (build_menu == nullptr)
        return;

    BuildMenuWrapper build_menu_wrapper(build_menu, this->baseAddress);
    build_menu_wrapper.reinitializeButtonsWrappers();

    if (pos > build_menu_wrapper.buttons.size())
        return;

    BuildButtonWrapper build_button = build_menu_wrapper.buttons[pos - 1];

    build_button.click();
}

void GameWrapper::setUnitStance(const UnitStance& stance) {
    Window* unitMenu = this->gameInterfaceManager->getUnitMenu();

    if (unitMenu == nullptr)
        return;

    Window* button = this->gameInterfaceManager->getButton(unitMenu, stance.name);

    if (button == nullptr)
        return;

    this->gameInterfaceManager->onClickRadioButton(button);
}

void GameWrapper::activateDeveloperMode()
{
    GameOptions* gameOptions = this->game->getGameOptions();

    gameOptions->developmentOptions->activatable = true;
    gameOptions->developmentOptions->activated = true;
}

std::shared_ptr<Game> GameWrapper::getGame()
{
    return this->game;
}
