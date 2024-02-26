#pragma once

#include "TAKEnhancedDll/common.hpp"

struct FriendlyFireSettings
{
    bool selfDamage = true;
    bool allyDamage = true;
    bool allyProjectileCollision = false;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    FriendlyFireSettings,
    selfDamage,
    allyDamage,
    allyProjectileCollision
)
