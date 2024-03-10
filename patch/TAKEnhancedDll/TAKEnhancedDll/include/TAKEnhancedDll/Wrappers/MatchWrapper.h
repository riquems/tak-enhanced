#pragma once

#include "TAKEnhancedDll/common.hpp"

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
