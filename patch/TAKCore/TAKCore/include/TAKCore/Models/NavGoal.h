#pragma once

namespace TAKCore
{
    struct Mission;

    struct NavGoal
    {
        char padding[4];
        Mission* mission;
        uint16_t xDestinationMapPosition;
        uint16_t zDestinationMapPosition;
        uint32_t minrange;
        uint16_t range;
    };
}
