#pragma once

#include "TAKCore/common.h"

#include "Weapon.h"
#include "Aura.h"

class UnitInfo
{
public:
    char name[32];
    char shortName[32];

    char padding1[230];

    uint16_t footprintX;
    uint16_t footprintZ;

    char padding2[100];

    uint16_t turnrate;
    uint16_t turninplacerate;

    char padding3[24];

    Weapon* weapon1;
    Weapon* weapon2;
    Weapon* weapon3;

    char padding4[8];

    uint32_t maxDamage;
    uint16_t experiencePoints;

    char padding5[6];

    Aura armorAura;

    char padding6[7];

    Aura attackAura;

    char padding7[7];

    Aura joyAura;

    char padding8[52];

    float buildcost;
    float buildtime;

    char padding9[8];

    float healtime;

    char padding10[4];

    uint32_t sightdistance;

    char padding11[8];

    uint32_t maneuverleashlength;

    char padding12[68];

    char bodytype[6];

    char padding13[38];
};