#pragma once

#include "../GameFunctions.h"
#include "PlayerWrapper.h"

class MatchWrapper;

class GameWrapper
{
public:
	std::vector<PlayerWrapper> players;
	std::shared_ptr<MatchWrapper> match;

	GameWrapper() 
	{
		match = std::make_shared<MatchWrapper>(this);
	}

	void initializePlayersWrappers();
	void refreshPlayersWrappers();
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