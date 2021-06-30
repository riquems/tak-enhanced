#pragma once

#include "Game.hpp"

#include "../Managers/WindowManager.h"
#include "../Managers/PlayerInterfaceManager.h"

#include "PlayerWrapper.h"
#include "BuildMenuWrapper.h"
#include "BuildButtonWrapper.h"

class MatchWrapper;

class GameWrapper
{
public:
	GameInterfaceManager player_interface_manager;
	std::vector<PlayerWrapper> players;
	std::shared_ptr<MatchWrapper> match;

	GameWrapper() 
	{
		match = std::make_shared<MatchWrapper>(this);
	}

	void initializePlayersWrappers();
	void refreshPlayersWrappers();
	bool isBuildMenuOpen();

	void selectBuilding(int pos);

	void switchSelectedUnitHumor(int humorId);
	uintptr_t getSelectedUnitAddress();
};

void GameWrapper::initializePlayersWrappers()
{
	Player* players_models = Game::GetPlayers(baseAddress);

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
	std::shared_ptr<BuildMenu*> build_menu = player_interface_manager.getBuildMenu();

	if (build_menu == nullptr || build_menu.get() == nullptr) {
		return false;
	}

	return (*build_menu.get())->visible;
}

void GameWrapper::selectBuilding(int pos)
{
	std::shared_ptr<BuildMenu*> build_menu = player_interface_manager.getBuildMenu();

	if (build_menu == nullptr || build_menu.get() == nullptr) {
		return;
	}

	BuildMenuWrapper build_menu_wrapper(build_menu);
	build_menu_wrapper.reinitializeButtonsWrappers();

	BuildButtonWrapper* build_button = &build_menu_wrapper.buttons[pos - 1];

	build_button->click();
}

void GameWrapper::switchSelectedUnitHumor(int humorId)
{
	
}

uintptr_t GameWrapper::getSelectedUnitAddress()
{
	uintptr_t(*getMouseHoveredUnitAddress)() = (uintptr_t(*)()) (FunctionsOffsets::getMouseHoveredUnitAddress + baseAddress);

	return getMouseHoveredUnitAddress();
}