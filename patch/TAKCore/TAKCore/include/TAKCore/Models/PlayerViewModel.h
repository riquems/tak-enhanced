#pragma once
#include "TAKCore/common.h"

namespace TAKCore
{
    struct PlayerViewModel
    {
        char padding[133];
        uint8_t sideId;
        uint8_t colorId;
        char padding2[3];
        uint8_t teamId;
        char padding3[5];
    };
}
