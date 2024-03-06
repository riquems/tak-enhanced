#pragma once
#include "TAKEnhancedDll/Configs/GameConfig.hpp"

#include <iostream>
#include <deque>
#include "ddraw.h"
#include "Utils/Keyboard.hpp"

#pragma comment(lib,"ddraw.lib") 

/*********************************************************
 
    The TA:K Enhanced Service is a service which will 
    be running while the game is running, doing several
    different tasks.

**********************************************************/

void handleInputs(KeyboardState& keyboardState);

void guaranteeFocus();

void startTAKEnhancedService(std::shared_ptr<GameConfig> gameConfig);
