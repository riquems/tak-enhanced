#include "common.hpp"

namespace TAKEnhancedLibrary
{
    enum DamageType {
        Unknown = 0x00,
        Damage = 0x01,
        ExplodeAs = 0x03,
        Healing = 0x0C,
        Paralyze = 0x04,
        SelfDestruct = 0x05,
        FadeAway = 0x0B,
        TurnToStone = 0x0E,
        Freeze = 0x0F
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(DamageType, {
        { Unknown, "Unknown" },
        { Damage, "Damage"},
        { Healing, "Healing" },
        { Paralyze, "Paralyze" },
        { SelfDestruct, "SelfDestruct" },
        { FadeAway, "FadeAway" },
        { TurnToStone, "TurnToStone" },
        { Freeze, "Freeze" }
    });
}
