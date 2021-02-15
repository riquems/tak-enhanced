#pragma once

#include "common.h"

#include "Weapon.h"
#include "Aura.h"

class UnitInfo
{
	char name[32];
	char shortName[32];

	char padding0[230];

	uint16_t footprintX;
	uint16_t footprintZ;

	char padding1[100];

	uint16_t turnrate;
	uint16_t turninplacerate;

	char padding2[24];

	Weapon* weapon1;
	Weapon* weapon2;
	Weapon* weapon3;

	char padding3[8];

	uint32_t maxDamage;
	uint16_t experiencePoints;

	char padding4[6];

	Aura armorAura;

	char padding5[7];

	Aura attackAura;

	char padding5[7];

	Aura joyAura;

	char padding6[52];

	float buildcost;
	float buildtime;

	char padding7[8];

	float healtime;

	char padding8[4];

	uint32_t sightdistance;

	char padding9[8];

	uint32_t maneuverleashlength;

	char padding[68];

	char bodytype[6];

	char padding[38];
};