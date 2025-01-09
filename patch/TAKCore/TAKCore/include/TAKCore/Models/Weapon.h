#pragma once
#include "WeaponType.h"

namespace TAKCore
{
    struct Weapon
    {                             // offsets
        char name[0x40];          // 0x000
        WeaponType* type;         // 0x040
        char padding[0x44];       // 0x044
        uint16_t damage;          // 0x088
        uint16_t areaofeffect;    // 0x08A
        float edgeeffectiveness;  // 0x08C
        uint32_t range;           // 0x090
        uint32_t minrange;        // 0x094
        char padding2[0x30];      // 0x098
        uint8_t damageType;       // 0x0C8
    };
}
