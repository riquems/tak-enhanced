#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKCore/Models/Player.h"

namespace TAKEnhancedLibrary
{
    struct Unit;

    struct Player
    {
        const TAKCore::Player* raw;

        Player(const TAKCore::Player*);

        uint8_t color();
        uint16_t unitsCount();
        uint8_t id();
        std::optional<uint8_t> team();

        std::vector<std::shared_ptr<Unit>> units();

        bool operator ==(const Player& player);
    };
}
