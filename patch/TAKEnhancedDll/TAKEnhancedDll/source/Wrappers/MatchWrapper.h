#pragma once

#include "TAKEnhancedDll/common.hpp"
#include "../GameFunctions.h"
#include "GameWrapper.h"
#include "PlayerWrapper.h"

class MatchWrapper
{
public:
    GameWrapper* _game;

    MatchWrapper() {}
    MatchWrapper(GameWrapper* game) : _game(game) {}

    bool isRunning() {
        return anyPlayerHaveAtLeastOneUnit(); // At least one player has at least one unit
    }

    bool anyPlayerHaveAtLeastOneUnit() {
        std::vector<PlayerWrapper>* players_wrappers = &_game->players;

        std::vector<PlayerWrapper>::iterator player_iterator = std::find_if(players_wrappers->begin(),
            players_wrappers->end(),
            [&](PlayerWrapper player) {
                return player.getUnitsCount() > 0;
            });

        return player_iterator != players_wrappers->end();
    }
};