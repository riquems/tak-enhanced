#pragma once

namespace TAKCore
{
    struct PlayerViewModel;
    struct Unit;

    struct Player
    {
        bool initialized;                 // 0x00
        char padding[3];                  // 0x01
        uint32_t id;                      // 0x04
        char padding3[72];
        PlayerViewModel* playerViewModel; // 0x50
        char name[32];                    // 0x54
        Unit* firstUnit;                  // 0x74
        Unit* lastUnit;                   // 0x78
        char padding4[36];
        uint16_t kills;                   // 0xA0
        uint16_t losses;                  // 0xA2
        uint32_t score;                   // 0xA4
        char padding5[64];
        uint16_t unitsCount;              // 0xE8
        char padding6[1];                 // 0xEA
        uint8_t byte_004E4F7B;            // 0xEB
        char padding7[36];
    };
}
