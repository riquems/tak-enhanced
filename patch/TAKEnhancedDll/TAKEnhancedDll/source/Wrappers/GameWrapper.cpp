#include "TAKEnhancedDll/Wrappers/GameWrapper.h"
#include "TAKEnhancedDll/Wrappers/MatchWrapper.h"
#include <TAKEnhancedDll/GlobalState.hpp>

std::shared_ptr<GameWrapper> gameWrapper;

createGraphicObjectFromJPG_t oldCreateGraphicObjectFromJPG;

extern "C" __declspec(dllexport) uintptr_t __stdcall newCreateGraphicObjectFromJPG(const char* filePath, int a1)
{
    return oldCreateGraphicObjectFromJPG(filePath, a1);
}

GameWrapper::GameWrapper(GameInterfaceHandler* uiHandler, uintptr_t baseAddress)
{
    _game = std::make_shared<Game>(baseAddress);
    gameInterfaceManager = std::make_shared<GameInterfaceManager>(uiHandler, baseAddress);

    _baseAddress = baseAddress;

    match = std::make_shared<MatchWrapper>(this);
}

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
    logger->info("[Event] OnInitialize");
}

void GameWrapper::onFirstGameLoading()
{
    logger->info("[Event] OnFirstGameLoading");

    oldCreateGraphicObjectFromJPG = (createGraphicObjectFromJPG_t)(this->_baseAddress + FunctionsOffsets::createGraphicObjectFromJPG);

    uintptr_t* gamePtr = (uintptr_t*)(GlobalPointers::ptr_22D55C + this->_baseAddress);
    uintptr_t* hpBarPtr = (uintptr_t*)(*gamePtr + 0x17454);

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

    BuildMenuWrapper build_menu_wrapper(build_menu, this->_baseAddress);
    build_menu_wrapper.reinitializeButtonsWrappers();

    if (pos > build_menu_wrapper.buttons.size())
        return;

    BuildButtonWrapper build_button = build_menu_wrapper.buttons[pos - 1];

    build_button.click();
}

void GameWrapper::setHpBarColor(Player* player, CustomizableHpBarSetting hpColorOptions)
{
    uintptr_t graphicObjAddr = 0;
    
    switch (hpColorOptions.colorMode)
    {
        case ColorMode::Original: {
            graphicObjAddr = originalHpBarGraphicObjAddr;
            break;
        }
        case ColorMode::MatchPlayerColor: {
            int colorId = player->playerViewModel->colorId;
            graphicObjAddr = colorIdToGraphicObjAddr[colorId];
            break;
        }
        case ColorMode::Custom: {
            int colorId = (int) hpColorOptions.color;
            graphicObjAddr = colorIdToGraphicObjAddr[colorId];
            break;
        }
    }

    uintptr_t* gamePtr = (uintptr_t*) (GlobalPointers::ptr_22D55C + this->_baseAddress);
    uintptr_t* hpBarPtr = (uintptr_t*) (*gamePtr + 0x17454);

    *hpBarPtr = graphicObjAddr;
}

uintptr_t GameWrapper::getMouseHoveredUnitAddress()
{
    return _game->getMouseHoveredUnitAddress();
}

std::shared_ptr<UnitWrapper> GameWrapper::getMouseHoveredUnit()
{
    Unit* unit = (Unit*) this->getMouseHoveredUnitAddress();

    if (unit == nullptr)
        return nullptr;

    return std::make_shared<UnitWrapper>(unit);
}

std::vector<std::shared_ptr<UnitWrapper>> GameWrapper::getSelectedUnits()
{
    std::vector<Unit*> selectedUnits = _game->getSelectedUnits();

    std::vector<std::shared_ptr<UnitWrapper>> selectedUnitsResult;

    std::transform(
        selectedUnits.begin(),
        selectedUnits.end(),
        std::back_inserter(selectedUnitsResult),
        [&](Unit* unit) {
            return std::make_shared<UnitWrapper>(unit);
        }
    );

    return selectedUnitsResult;
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
    return player == players[0]._player;
}

bool GameWrapper::isEnemy(Player* player)
{
    uint8_t myTeamId = players[0].getTeamId();
    uint8_t unitPlayerTeamId = player->playerViewModel->teamId;

    if (myTeamId != unitPlayerTeamId || !isMe(player) && unitPlayerTeamId == 4) {
        return true;
    }

    return false;
}

bool GameWrapper::isAlly(Player* player)
{
    uint8_t myTeamId = players[0].getTeamId();
    uint8_t unitPlayerTeamId = player->playerViewModel->teamId;

    if (!isMe(player) && myTeamId == unitPlayerTeamId && unitPlayerTeamId != 4) { // 4 = No team
        return true;
    }

    return false;
}

bool GameWrapper::areAllies(Player* p1, Player* p2)
{
    if (p1 == p2)
        return false;

    uint8_t p1TeamId = p1->playerViewModel->teamId;
    uint8_t p2TeamId = p2->playerViewModel->teamId;

    bool p1HasTeam = p1TeamId != 4;
    bool p2HasTeam = p2TeamId != 4;

    if (p1HasTeam && p2HasTeam && p1TeamId == p2TeamId) {
        return true;
    }

    return false;
}

bool GameWrapper::areAllies(int p1, int p2)
{
    if (p1 == p2)
        return false;

    uint8_t p1TeamId = players[p1].getTeamId();
    uint8_t p2TeamId = players[p2].getTeamId();

    bool p1HasTeam = p1TeamId != 4;
    bool p2HasTeam = p2TeamId != 4;

    if (p1HasTeam && p2HasTeam && p1TeamId == p2TeamId) {
        return true;
    }

    return false;
}
