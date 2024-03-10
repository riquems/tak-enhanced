#pragma once
#include "TAKCore/common.h"

namespace TAKCore
{
    struct Aura
    {
        float adjustment;
        uint16_t radius;
        char padding[2];
        float edgeeffectiveness;
        bool affectsenemies;
    };
}
