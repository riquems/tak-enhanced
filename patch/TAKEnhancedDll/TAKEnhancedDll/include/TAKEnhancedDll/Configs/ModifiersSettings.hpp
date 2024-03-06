#pragma once
#include "TAKEnhancedDll/common.hpp"

struct ModifiersSettings
{
    float manaStorage = 1.0f;
    float manaIncome = 1.0f;
    float unitSight = 1.0f;
    float workerTime = 1.0f;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    ModifiersSettings,
    manaStorage,
    manaIncome,
    unitSight,
    workerTime
)
