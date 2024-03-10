#pragma once
#include "TAKCore/common.h"
#include "TAKCore/Models/Player.h"

namespace TAKCore
{
    extern unsigned int MaxPlayersSupported;

    constexpr unsigned int PlayersOffset = 0x2404;
    extern Player* Players;
}
