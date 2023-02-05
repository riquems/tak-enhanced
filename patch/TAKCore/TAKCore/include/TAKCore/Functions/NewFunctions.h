#pragma once
#include "TAKCore/Models/Unit.h"

uint8_t decodeWeaponId(uint8_t encodedWeaponId);

Weapon* getSelectedWeapon(Unit* unit);