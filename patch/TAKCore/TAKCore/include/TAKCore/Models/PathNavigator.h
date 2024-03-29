#pragma once
#include "TAKCore/common.h"

namespace TAKCore
{
    struct Unit;
    struct NavGoal;

    struct PathNavigator
    {
        char padding[4];
        NavGoal* navGoal;
        Unit* unit;
        uint16_t xUnitMapPosition;
        uint16_t zUnitMapPosition;
        uint16_t xDestinationMapPosition;
        uint16_t zDestinationMapPosition;
        uint16_t word_0x14;
        uint16_t word_0x16;
    };
}
