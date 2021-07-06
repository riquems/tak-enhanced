#pragma once

#include "Game.hpp"

#include "../Managers/WindowManager.h"
#include "../Managers/GameInterfaceManager.h"

#include "Models/Options/GameOptions.h"
#include "Models/Options/DevelopmentOptions.h"

#include "PlayerWrapper.h"
#include "BuildMenuWrapper.h"
#include "BuildButtonWrapper.h"

class MatchWrapper;

class GameWrapper
{
    std::shared_ptr<Game> _game;

public:
    std::shared_ptr<GameInterfaceManager> _gameInterfaceManager;
    std::vector<PlayerWrapper> players;
    std::shared_ptr<MatchWrapper> match;

    GameWrapper() {}
    GameWrapper(uintptr_t baseAddress) 
    {
        _game = std::make_shared<Game>(baseAddress);
        _gameInterfaceManager = std::make_shared<GameInterfaceManager>(baseAddress);

        match = std::make_shared<MatchWrapper>(this);
    }

    void initializePlayersWrappers();
    void refreshPlayersWrappers();
    bool isBuildMenuOpen();

    void selectBuilding(int pos);

    void activateDeveloperMode();

    void switchSelectedUnitHumor(int humorId);
    uintptr_t getMouseHoveredUnitAddress();

    std::shared_ptr<Game> getGame();
};

void GameWrapper::initializePlayersWrappers()
{
    Player* players_models = _game->getPlayers();

    Player* next_player = players_models;
    while (next_player->initialized)
    {
        PlayerWrapper player_wrapper(next_player);

        players.push_back(player_wrapper);
        next_player++;
    }
}

void GameWrapper::refreshPlayersWrappers()
{
    players.clear();
    initializePlayersWrappers();
}

bool GameWrapper::isBuildMenuOpen()
{
    std::shared_ptr<BuildMenu*> build_menu = _gameInterfaceManager->getBuildMenu();

    if (build_menu == nullptr || build_menu.get() == nullptr) {
        return false;
    }

    return (*build_menu.get())->visible;
}

void GameWrapper::selectBuilding(int pos)
{
    std::shared_ptr<BuildMenu*> build_menu = _gameInterfaceManager->getBuildMenu();

    if (build_menu == nullptr || build_menu.get() == nullptr)
        return;

    BuildMenuWrapper build_menu_wrapper(build_menu);
    build_menu_wrapper.reinitializeButtonsWrappers();

    if (pos > build_menu_wrapper.buttons.size())
        return;

    BuildButtonWrapper* build_button = &build_menu_wrapper.buttons[pos - 1];

    build_button->click();
}

void GameWrapper::switchSelectedUnitHumor(int humorId)
{
    
}

uintptr_t GameWrapper::getMouseHoveredUnitAddress()
{
    return _game->getMouseHoveredUnitAddress();
}

void GameWrapper::activateDeveloperMode()
{
    GameOptions* gameOptions = _game->getGameOptions();

    gameOptions->developmentOptions->activatable = true;
    gameOptions->developmentOptions->activated = true;
}

std::shared_ptr<Game> GameWrapper::getGame()
{
    return _game;
}
