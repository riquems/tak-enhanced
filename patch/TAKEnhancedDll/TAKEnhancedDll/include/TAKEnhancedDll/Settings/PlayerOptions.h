#pragma once

#include "GameDefs.h"

enum ShowHpOption {
    ALWAYS_SHOW          = 0,
    NEVER_SHOW           = 1,
    SHOW_ONLY_IF_DAMAGED = 2
};

enum HpColorMode {
    ORIGINAL           = 0,
    MATCH_PLAYER_COLOR = 1,
    FIXED_COLOR        = 2
};

struct HpColorOptions
{
    HpColorMode mode;
    Color color;
};

struct HpOptions
{
    ShowHpOption showHpOption;
    HpColorOptions hpColorOption;
};
