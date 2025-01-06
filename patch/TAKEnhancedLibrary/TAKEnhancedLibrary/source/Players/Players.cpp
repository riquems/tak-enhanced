#include "TAKEnhancedLibrary/State.hpp"
#include "TAKEnhancedLibrary/Players/Players.hpp"
#include "TAKEnhancedLibrary/Players/PlayerPool.hpp"
#include "TAKCore/Players/Players.hpp"
#include "dky/containers.hpp"
#include "TAKCore/Models/PlayerViewModel.h"

using namespace TAKEnhancedLibrary;

std::shared_ptr<Player> TAKEnhancedLibrary::NewPlayer(const TAKCore::Player* rawPlayer) {
    auto maybePlayer = PlayerPool::get_one();

    if (!maybePlayer) {
        return nullptr;
    }

    auto player = maybePlayer;

    player->raw = rawPlayer;

    return player;
}

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

bool TAKEnhancedLibrary::IsMe(int playerIndex) {
    return playerIndex == GetCurrentPlayer()->raw->index;
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

bool TAKEnhancedLibrary::AreAllies(const std::shared_ptr<Player>& p1, const std::shared_ptr<Player>& p2) {
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

bool TAKEnhancedLibrary::AreAllies(int p1Id, int p2Id) {
    auto players = GetPlayers();

    auto p1 = dky::find(players,
        [&](const std::shared_ptr<Player>& player) {
            return player->id() == p1Id;
        }
    );

    if (!p1.has_value()) {
        logger->debug("[AreAllies] Player with id %d has not been found", p1Id);
        logger->debug("Players: %s", dky::vector::to_string(
            dky::map(players, [](const std::shared_ptr<Player> p) {
                return std::to_string(p->id());
            })
        ).c_str());

        return false;
    }

    auto p2 = dky::find(players,
        [&](const std::shared_ptr<Player>& player) {
            return player->id() == p2Id;
        }
    );

    if (!p2.has_value()) {
        logger->debug("[AreAllies] Player with id %d has not been found", p2Id);
        logger->debug("Players: %s", dky::vector::to_string(
            dky::map(players, [](const std::shared_ptr<Player> p) {
                return std::to_string(p->id());
            })
        ).c_str());

        return false;
    }

    return AreAllies(p1.value(), p2.value());
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

bool TAKEnhancedLibrary::AreEnemies(int p1Id, int p2Id) {
    auto players = GetPlayers();

    auto p1 = dky::find(players,
        [&](const std::shared_ptr<Player>& player) {
            return player->id() == p1Id;
        }
    );

    if (!p1.has_value()) {
        logger->debug("[AreEnemies] Player with id %d has not been found", p1Id);
        logger->debug("Players: %s", dky::vector::to_string(
            dky::map(players, [](const std::shared_ptr<Player> p) {
                return std::to_string(p->id());
            })
        ).c_str());

        return true;
    }

    auto p2 = dky::find(players,
        [&](const std::shared_ptr<Player>& player) {
            return player->id() == p2Id;
        }
    );

    if (!p2.has_value()) {
        logger->debug("[AreEnemies] Player with id %d has not been found", p2Id);
        logger->debug("Players: %s", dky::vector::to_string(
            dky::map(players, [](const std::shared_ptr<Player> p) {
                return std::to_string(p->id());
            })
        ).c_str());

        return true;
    }

    return AreEnemies(p1.value(), p2.value());
}
