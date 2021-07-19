#pragma once
#include "../common.h"

#include "MapPosition.h"

class MovementHandler;
class UnitRenderer;
class TAobjectScript;
class UnitInfo;
class Weapon;
class Player;
class Mission;
class MovementHandler;

class Unit
{
public:                                  // offset
    char padding[8];
    MovementHandler* movementHandler;    // 0x008
    Weapon* weapon1;                     // 0x00C
    char padding2[24];                   // 0x010
    Weapon* weapon2;                     // 0x028
    char padding3[24];                   // 0x02C
    Weapon* weapon3;                     // 0x044
    char padding4[24];                   // 0x048
    Mission* mission;                    // 0x060
    char padding5[4];                    // 0x064
    MapPosition xMapPosition;            // 0x068
    MapPosition yMapPosition;            // 0x06C
    MapPosition zMapPosition;            // 0x070
    uint16_t xFootprintPos;              // 0x064
    uint16_t zFootprintPos;              // 0x068
    uint16_t xFootprintLength;           // 0x06C
    uint16_t zFootprintLength;           // 0x070
    char padding7[2];                    // 0x07C
    uint16_t direction;                  // 0x07E
    char padding8[4];                    // 0x080
    Player* player;                      // 0x084
    char padding9[4];                    // 0x088
    MapPosition xMapPosition2;           // 0x08C
    char padding10[4];                   // 0x090
    MapPosition zMapPosition2;           // 0x094
    char padding11[28];                  // 0x09B
    UnitInfo* unitInfo;                  // 0x0B4
    Player* player2;                     // 0x0B8
    TAobjectScript* cobScript;           // 0x0BC
    UnitRenderer* renderer;              // 0x0C0
    char padding12[20];                  // 0x0C4
    float currentMana;                   // 0x0D8
    float maxMana;                       // 0x0DC
    char padding13[44];                  // 0x0E0
    uint16_t currentHealth;              // 0x10C
    uint8_t healthRegeneration;          // 0x10E
    char padding14[1];                   // 0x10F
    uint8_t currentHealthPercentage;     // 0x110
    uint8_t currentHealthPercentage2;    // 0x111
    char padding15[24];                  // 0x112
    uint32_t maxSpeed;                   // 0x12A
    char padding16[2];                   // 0x12E
    uint8_t walking;                     // 0x130
    char padding17[1];                   // 0x131
    uint8_t humor;                       // 0x132
    uint8_t encodedSelectedWeaponId;     // 0x133
    char padding18[4];                   // 0x134
};
