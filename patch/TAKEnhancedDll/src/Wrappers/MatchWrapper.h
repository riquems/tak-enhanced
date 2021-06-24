#pragma once

#include "common.h"
#include "PlayerWrapper.h"
#include ""

class MatchWrapper
{
public:
	MatchWrapper() {}

	bool hasEnded() {
		

		return !anyPlayerHasAtLeastOneUnit();
	}

	bool anyPlayerHasAtLeastOneUnit() {
		std::vector<PlayerWrapper> players_wrappers = GameFunctionsExtensions::GetPlayersWrappers();

		std::vector<PlayerWrapper>::iterator player_iterator = players_wrappers.findif(players_wrappers.begin(),
			players_wrappers.end(),
			[&](PlayerWrapper player) {
				return player.getUnitsCount() > 0;
			});

		return player_iterator != players_wrappers.end();
	}
};