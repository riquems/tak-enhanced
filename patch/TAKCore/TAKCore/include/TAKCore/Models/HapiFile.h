#pragma once
#include "TAKCore/common.h"

class HapiFile
{
    // member                            // offset
public:
    DWORD vTable;                        // 0x000
    char padding[0x30];                  // 0x004
    bool allowed;                        // 0x034
    char padding5[3];                    // 0x034
    bool allowed2;                       // 0x034
    char padding2[0x0B];                 // 0x035
    char filename[240];                  // 0x044
    char padding3[0x20];                 // 0x134
};                                       

// size: 0x14C