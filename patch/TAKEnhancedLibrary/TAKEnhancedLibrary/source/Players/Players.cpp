#include "TAKEnhancedLibrary/Players/Players.hpp"
#include "TAKCore/Players/Players.hpp"

using namespace TAKEnhancedLibrary;

std::vector<std::shared_ptr<Player>> TAKEnhancedLibrary::GetPlayers() {
    std::vector<std::shared_ptr<Player>> players;

    for (int i = 0; i < TAKCore::MaxPlayersSupported; i++) {
        auto player = &TAKCore::Players[i];

        if (!player->initialized)
            continue;

        players.push_back(std::make_shared<Player>(player));
    }

    return players;
}

std::shared_ptr<Player> TAKEnhancedLibrary::GetCurrentPlayer() {
    return GetPlayers()[0];
}

bool TAKEnhancedLibrary::IsMe(std::shared_ptr<Player> player) {
    return *player == *GetCurrentPlayer();
}

bool TAKEnhancedLibrary::IsEnemy(std::shared_ptr<Player> player) {
    return AreEnemies(GetCurrentPlayer(), player);
}

bool TAKEnhancedLibrary::IsAlly(std::shared_ptr<Player> player) {
    return AreAllies(GetCurrentPlayer(), player);
}

bool TAKEnhancedLibrary::AreAllies(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
    if (*p1 == *p2)
        return false;

    auto p1Team = p1->team();

    if (!p1Team.has_value())
        return false;

    auto p2Team = p2->team();

    if (!p2Team.has_value())
        return false;

    if (p1Team != p2Team)
        return false;

    return true;
}

bool TAKEnhancedLibrary::AreAllies(int p1, int p2) {
    auto players = GetPlayers();

    return AreAllies(players[p1], players[p2]);
}

bool TAKEnhancedLibrary::AreEnemies(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
    if (*p1 == *p2)
        return false;

    auto p1Team = p1->team();

    if (!p1Team.has_value())
        return false;

    auto p2Team = p2->team();

    if (!p2Team.has_value())
        return false;

    if (p1Team == p2Team)
        return false;

    return true;
}

bool TAKEnhancedLibrary::AreEnemies(int p1, int p2) {
    auto players = GetPlayers();

    return AreAllies(players[p1], players[p2]);
}
