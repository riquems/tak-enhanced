#pragma once
#include "TAKEnhancedDll/Configs/GameConfig.hpp"

#include <iostream>
#include <queue>
#include "ddraw.h"

#pragma comment(lib,"ddraw.lib") 

/*********************************************************
 
    The TA:K Enhanced Service is a service which will 
    be running while the game is running, doing several
    different tasks.

**********************************************************/

void processInputSequence(std::queue<int>& sequence);

void guaranteeFocus();

void startTAKEnhancedService(std::shared_ptr<GameConfig> gameConfig);
