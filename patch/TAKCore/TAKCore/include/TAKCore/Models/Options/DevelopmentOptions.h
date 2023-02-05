#pragma once

#include "../../common.h"

class DevelopmentOptions
{
public:
    uintptr_t* vTable;
    bool activatable;
    bool activated;
    bool debugUnitProbe;
    bool tune;
};
