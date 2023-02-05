#pragma once

#include "TAKEnhancedDll/common.hpp"
#include "PlayerWrapper.h"

class GameWrapper;

class MatchWrapper
{
public:
    GameWrapper* _game;

    MatchWrapper();
    MatchWrapper(GameWrapper* game);

    bool isRunning();

    bool anyPlayerHaveAtLeastOneUnit();
};
