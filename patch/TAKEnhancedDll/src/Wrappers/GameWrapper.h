#pragma once

#include "../GameFunctions.h"

#include "../Managers/GafManager.h"
#include "../Managers/PlayerInterfaceManager.h"

#include "PlayerWrapper.h"
#include "BuildMenuWrapper.h"
#include "BuildButtonWrapper.h"

class MatchWrapper;

class GameWrapper
{
public:
	PlayerInterfaceManager player_interface_manager;
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
};

void GameWrapper::initializePlayersWrappers()
{
	Player* players_models = GameFunctionsExtensions::GetPlayers();

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

	BuildMenuWrapper build_menu_wrapper(build_menu);

	return build_menu_wrapper.isOpen();
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