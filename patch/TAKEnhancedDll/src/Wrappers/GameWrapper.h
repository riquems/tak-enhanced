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
	BuildMenu* build_menu = player_interface_manager.getBuildMenu();

	if (build_menu == nullptr) {
		return false;
	}

	BuildMenuWrapper build_menu_wrapper(build_menu);

	return build_menu_wrapper.isOpen();
}

void GameWrapper::selectBuilding(int pos)
{
	std::cout << "Selecting building #" << pos << std::endl;

	BuildMenuWrapper build_menu = player_interface_manager.getBuildMenu();
	BuildButtonWrapper build_button = build_menu.buttons[pos - 1];

	build_button.click();
}