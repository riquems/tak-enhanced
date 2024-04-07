#include "TAKEnhancedLibrary/Match/Match.hpp"
#include "TAKEnhancedLibrary/Players/Players.hpp"

using namespace TAKEnhancedLibrary;

bool somePlayerHaveAtLeastOneUnit();

bool TAKEnhancedLibrary::MatchIsRunning() {
    return somePlayerHaveAtLeastOneUnit();
}

bool somePlayerHaveAtLeastOneUnit() {
    auto players = TAKEnhancedLibrary::GetPlayers();

    return dky::contains(players,
        [](const std::shared_ptr<Player>& player) {
            return player->unitsCount() > 0;
        }
    );
}
