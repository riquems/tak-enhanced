#pragma once
#include "TAKCore/common.h"
#include "TAKCore/Models/Unit.h"

namespace TAKCore
{
    constexpr unsigned int UnitsOffset = 0x14E84;
    Unit* GetUnits();
}
