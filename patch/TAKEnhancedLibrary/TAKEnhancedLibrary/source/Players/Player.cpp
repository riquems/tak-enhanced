#include "TAKEnhancedLibrary/Players/Player.hpp"
#include "TAKEnhancedLibrary/Units/Unit.hpp"

#include "TAKCore/Models/Unit.h"
#include "TAKCore/Models/PlayerViewModel.h"

using namespace TAKEnhancedLibrary;

Player::Player(TAKCore::Player* raw) : raw(raw) { }

std::vector<std::shared_ptr<Unit>> Player::units() {
    std::vector<std::shared_ptr<Unit>> units;

    TAKCore::Unit* nextUnit = this->raw->firstUnit;

    while (nextUnit != this->raw->lastUnit)
    {
        units.push_back(std::make_shared<Unit>(nextUnit));
        nextUnit++;
    }

    return units;
}

uint8_t Player::color() {
    return this->raw->playerViewModel->colorId;
}

uint16_t Player::unitsCount() {
    return this->raw->unitsCount;
}

uint8_t Player::id() {
    return this->raw->id;
}

std::optional<uint8_t> Player::team() {
    if (this->raw->playerViewModel->teamId == 4) {
        return std::optional<uint8_t>();
    }

    return this->raw->playerViewModel->teamId;
}

bool Player::operator ==(const Player& player) {
    return this->raw == player.raw;
}
