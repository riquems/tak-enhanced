#include "TAKEnhancedLibrary/Players/PlayerPool.hpp"
#include "Utils/Logger.h"

using namespace TAKEnhancedLibrary;

std::vector<std::shared_ptr<Player>> PlayerPool::Instance;

void PlayerPool::init(int poolSize) {
    for (int i = 0; i < poolSize; i++) {
        PlayerPool::Instance.push_back(std::make_shared<Player>((TAKCore::Player*) nullptr));
    }
}

std::shared_ptr<Player> PlayerPool::get_one() {
    auto maybePlayer = dky::find(PlayerPool::Instance, [](const std::shared_ptr<Player>& p) {
        return p.use_count() == 1;
    });

    if (!maybePlayer.has_value()) {
        /*logger->debug("[NewPlayer] Player with use count == 1 has not been found");
        logger->debug("Players: %s", dky::vector::to_string(
            dky::map(PlayerPool::Instance, [&](const std::shared_ptr<Player> p) {
                return std::to_string(p.use_count());
                })
        ).c_str());*/

        return nullptr;
    }

    return maybePlayer.value();
}
