#pragma once
#include "WeaponType.h"

class Weapon
{
	// members              // offsets
public:
	char name[64];			// 0x000
	WeaponType* type;		// 0x040
	char padding[68];		// 0x044
	uint16_t damage;		// 0x088
	uint16_t areaofeffect;	// 0x08A
	float edgeeffectiveness;// 0x08C
	uint32_t range;			// 0x090
	uint32_t minrange;		// 0x094
};