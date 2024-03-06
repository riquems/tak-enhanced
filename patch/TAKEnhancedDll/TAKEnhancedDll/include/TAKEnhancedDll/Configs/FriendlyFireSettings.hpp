#pragma once

#include "TAKEnhancedDll/common.hpp"

struct FriendlyFireSettings
{
    bool selfDamage = true;
    bool allyDamage = true;
    bool allyProjectileCollision = false;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    FriendlyFireSettings,
    selfDamage,
    allyDamage,
    allyProjectileCollision
)
