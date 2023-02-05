#include "TAKEnhancedDll/Wrappers/MatchWrapper.h"
#include "TAKEnhancedDll/Wrappers/GameWrapper.h"

MatchWrapper::MatchWrapper() {}
MatchWrapper::MatchWrapper(GameWrapper* game) : _game(game) {}

bool MatchWrapper::isRunning() {
    return anyPlayerHaveAtLeastOneUnit(); // At least one player have at least one unit
}

bool MatchWrapper::anyPlayerHaveAtLeastOneUnit() {
    std::vector<PlayerWrapper>* players_wrappers = &_game->players;

    std::vector<PlayerWrapper>::iterator player_iterator = std::find_if(players_wrappers->begin(),
        players_wrappers->end(),
        [&](PlayerWrapper player) {
            return player.getUnitsCount() > 0;
        });

    return player_iterator != players_wrappers->end();
}
