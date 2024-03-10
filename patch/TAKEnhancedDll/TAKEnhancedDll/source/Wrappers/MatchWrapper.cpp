#include "TAKEnhancedDll/Wrappers/MatchWrapper.h"
#include "TAKEnhancedDll/Wrappers/GameWrapper.h"
#include "TAKEnhancedLibrary/Players/Players.hpp"

using namespace TAKEnhancedLibrary;

MatchWrapper::MatchWrapper() {}
MatchWrapper::MatchWrapper(GameWrapper* game) : _game(game) {}

bool MatchWrapper::isRunning() {
    return anyPlayerHaveAtLeastOneUnit(); // At least one player have at least one unit
}

bool MatchWrapper::anyPlayerHaveAtLeastOneUnit() {
    auto players = TAKEnhancedLibrary::GetPlayers();

    return dky::contains(players,
        [](const std::shared_ptr<Player>& player) {
            return player->unitsCount() > 0;
        }
    );
}
