#pragma once
#include "Unit.h"

uint8_t decodeWeaponId(uint8_t encodedWeaponId)
{
	return (encodedWeaponId >> 6) % 3;
}

Weapon* getSelectedWeapon(Unit* unit)
{
	uint8_t selectedWeaponId = decodeWeaponId(unit->encodedSelectedWeaponId);

	uint8_t offset = 0x1C * selectedWeaponId;

	Weapon* weaponAddr = (Weapon*) (((uint32_t) &(unit->weapon1)) + offset);

	return weaponAddr;
}