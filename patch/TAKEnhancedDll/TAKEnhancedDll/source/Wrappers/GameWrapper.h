#pragma once

#include "Game.hpp"

#include "../Managers/WindowManager.h"
#include "../Managers/GameInterfaceManager.h"

#include "Models/Options/GameOptions.h"
#include "Models/Options/DevelopmentOptions.h"

#include "PlayerWrapper.h"
#include "BuildMenuWrapper.h"
#include "BuildButtonWrapper.h"
#include "Functions/FunctionsSignatures.h"
#include "TAKEnhancedDll/Settings.hpp"
#include "RendererDevice.hpp"

class MatchWrapper;

createGraphicObjectFromJPG_t oldCreateGraphicObjectFromJPG;

extern "C" __declspec(dllexport) uintptr_t __stdcall newCreateGraphicObjectFromJPG(const char* filePath, int a1)
{
    return oldCreateGraphicObjectFromJPG(filePath, a1);
}

class GameWrapper
{
    std::shared_ptr<Game> _game;
    uintptr_t _baseAddress;

public:
    std::shared_ptr<GameInterfaceManager> _gameInterfaceManager;
    std::vector<PlayerWrapper> players;
    std::shared_ptr<MatchWrapper> match;

    uintptr_t originalHpBarGraphicObjAddr;
    std::unordered_map<int, uintptr_t> colorIdToGraphicObjAddr;

    std::vector<std::string> hpBarsFileNames = {
        "lightblue.jpg",
        "red.jpg",
        "white.jpg",
        "green.jpg",
        "darkblue.jpg",
        "purple.jpg",
        "yellow.jpg",
        "black.jpg",
        "orange.jpg",
        "brown.jpg"
    };

    GameWrapper() {}
    GameWrapper(uintptr_t baseAddress) 
    {
        _game = std::make_shared<Game>(baseAddress);
        _gameInterfaceManager = std::make_shared<GameInterfaceManager>(baseAddress);

        _baseAddress = baseAddress;

        match = std::make_shared<MatchWrapper>(this);
    }

    void onInitialize();
    void onFirstGameLoading();

    void initializePlayersWrappers();
    void refreshPlayersWrappers();

    bool isInWriteMode();
    bool isBuildMenuOpen();

    void selectBuilding(int pos);
    void setHpBarColor(Player* player, HpColorOptions hpColorOptions);

    void activateDeveloperMode();

    void switchSelectedUnitHumor(int humorId);
    uintptr_t getMouseHoveredUnitAddress();

    bool isMe(Player* player);
    bool isEnemy(Player* player);
    bool isAlly(Player* player);

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

void GameWrapper::onInitialize()
{
    std::cout << "[Event] OnInitialize" << std::endl;
}

void GameWrapper::onFirstGameLoading()
{
    std::cout << "[Event] OnFirstGameLoading" << std::endl;

    oldCreateGraphicObjectFromJPG = (createGraphicObjectFromJPG_t) (baseAddress + FunctionsOffsets::createGraphicObjectFromJPG);

    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + baseAddress);
    uintptr_t* hpBarPtr = (uintptr_t*) (*gamePtr + 0x17454);

    originalHpBarGraphicObjAddr = *hpBarPtr;

    RendererDevice rendererDevice(_baseAddress);
    TextureDisplayMode renderer = rendererDevice.getTextureDisplayMode();

    switch (renderer)
    {
    case TextureDisplayMode::ORIGINAL_SIZE:

        for (int i = 0; i < hpBarsFileNames.size(); i++) {
            std::string hpBarFullPath = "anims\\hpbars_original_size\\" + hpBarsFileNames[i];

            uintptr_t hpBarAddr = newCreateGraphicObjectFromJPG(hpBarFullPath.c_str(), 0);

            colorIdToGraphicObjAddr.insert(std::pair(i, hpBarAddr));
        }

        break;

    case TextureDisplayMode::INCREASED_SIZE:
        for (int i = 0; i < hpBarsFileNames.size(); i++) {
            std::string hpBarFullPath = "anims\\hpbars_increased_size\\" + hpBarsFileNames[i];

            uintptr_t hpBarAddr = newCreateGraphicObjectFromJPG(hpBarFullPath.c_str(), 0);

            colorIdToGraphicObjAddr.insert(std::pair(i, hpBarAddr));
        }

        break;
    }
}

bool GameWrapper::isBuildMenuOpen()
{
    std::shared_ptr<BuildMenu*> build_menu = _gameInterfaceManager->getBuildMenu();

    if (build_menu == nullptr || build_menu.get() == nullptr) {
        return false;
    }

    return (*build_menu.get())->visible;
}

bool GameWrapper::isInWriteMode()
{
    return _gameInterfaceManager->isInWriteMode();
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

void GameWrapper::setHpBarColor(Player* player, HpColorOptions hpColorOptions)
{
    uintptr_t graphicObjAddr = 0;
    
    switch (hpColorOptions.mode)
    {
        case ORIGINAL: {
            graphicObjAddr = originalHpBarGraphicObjAddr;
            break;
        }
        case MATCH_PLAYER_COLOR: {
            int colorId = player->playerViewModel->colorId;
            graphicObjAddr = colorIdToGraphicObjAddr[colorId];
            break;
        }
        case FIXED_COLOR: {
            int colorId = (int) hpColorOptions.color;
            graphicObjAddr = colorIdToGraphicObjAddr[colorId];
            break;
        }
    }

    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + baseAddress);
    uintptr_t* hpBarPtr = (uintptr_t*) (*gamePtr + 0x17454);

    *hpBarPtr = graphicObjAddr;
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

bool GameWrapper::isMe(Player* player)
{
    return player->playerId == 0;
}

bool GameWrapper::isEnemy(Player* player)
{
    uint8_t myTeamId = players[0].getTeamId();
    uint8_t unitPlayerTeamId = player->playerViewModel->teamId;

    if (myTeamId != unitPlayerTeamId || player->playerId != 0 && unitPlayerTeamId == 4) {
        return true;
    }

    return false;
}

bool GameWrapper::isAlly(Player* player)
{
    uint8_t myTeamId = players[0].getTeamId();
    uint8_t unitPlayerTeamId = player->playerViewModel->teamId;

    if (player->playerId != 0 && myTeamId == unitPlayerTeamId && unitPlayerTeamId != 4) { // 4 = No team
        return true;
    }

    return false;
}
