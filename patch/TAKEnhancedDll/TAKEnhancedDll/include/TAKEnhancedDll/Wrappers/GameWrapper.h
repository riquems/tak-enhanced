#pragma once

#include "Game.hpp"
#include "TAKCore/Models/Options/GameOptions.h"
#include "TAKCore/Models/Options/DevelopmentOptions.h"

#include "TAKEnhancedDll/Configs/CustomizableHpBarsSettings.hpp"

#include "PlayerWrapper.h"
#include "BuildMenuWrapper.h"
#include "BuildButtonWrapper.h"
#include "TAKCore/Functions/FunctionsSignatures.h"
#include "RendererDevice.hpp"
#include <TAKEnhancedDll/Managers/GameInterfaceManager.h>

class MatchWrapper;

extern createGraphicObjectFromJPG_t oldCreateGraphicObjectFromJPG;

extern "C" __declspec(dllexport) uintptr_t __stdcall newCreateGraphicObjectFromJPG(const char* filePath, int a1);

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

    GameWrapper(GameInterfaceHandler* uiHandler, uintptr_t baseAddress);

    void onInitialize();
    void onFirstGameLoading();

    void initializePlayersWrappers();
    void refreshPlayersWrappers();

    bool isInWriteMode();
    bool isBuildMenuOpen();

    void selectBuilding(int pos);
    void setHpBarColor(Player* player, CustomizableHpBarSetting hpColorOptions);

    void activateDeveloperMode();

    void switchSelectedUnitHumor(int humorId);
    uintptr_t getMouseHoveredUnitAddress();

    bool isMe(Player* player);
    bool isEnemy(Player* player);
    bool isAlly(Player* player);

    std::shared_ptr<Game> getGame();
};

extern std::shared_ptr<GameWrapper> gameWrapper;