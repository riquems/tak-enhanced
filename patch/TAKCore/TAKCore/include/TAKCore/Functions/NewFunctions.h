#pragma once
#include "TAKCore/Models/Unit.h"

namespace TAKCore
{
    uint8_t decodeWeaponId(uint8_t encodedWeaponId);

    Weapon* getSelectedWeapon(Unit* unit);
}
