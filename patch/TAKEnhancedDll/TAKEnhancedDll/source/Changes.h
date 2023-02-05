#pragma once

#include "./Changes/HelperFeatures.h"
#include "./Changes/NoCD.h"
#include "./Changes/NoPauseWhenUnfocused.h"
#include "./Changes/PathFindingChanger.h"
#include "./Changes/MeleeStuckFix.h"
#include "./Changes/MaxUnits.h"
#include "./Changes/RandomRace.h"
#include "./Changes/ModLoader.h"
#include "./Changes/ShowEveryoneHealthBars.h"
#include "Hooks/UpdateGuiHook.h"
#include "Hooks/ReadSideDataHook.h"
#include "Hooks/LoadingScreenHook.h"
#include "Hooks/ShowHpHook.h"
#include "TAKEnhancedDll/Hooks/KeyboardInputHook.hpp"
#include <TAKEnhancedDll/Configs/GameConfig.hpp>
#include <Utils/Logger.h>

extern "C" __declspec(dllexport) const char* TAK_Enhanced_Label = "TA:K Enhanced v1.0.0";

void applyTakEnhancedVersion()
{
    MemoryHandler::write(TAK_Enhanced_Label, 0xA4E23);
}

void applyChanges(std::shared_ptr<GameConfig> config, std::shared_ptr<Logger> logger)
{
    applyTakEnhancedVersion();
    logger->info("TA:K Enhanced Label applied.");

    uint maxUnits = config->maxUnits;
    applyMaxUnitsPatch(maxUnits);
    logger->info("Unit limit applied.");

    uint pathFindingCycles = config->pathfindingCycles;
    applyPathfindingFix(pathFindingCycles);

    if (config->customizableHpBars.enabled) {
        showEveryoneHealthBars();
        installShowHpHook();
    }

    applyModLoader();

    if (config->noCD.enabled) {
        applyNoCD();
        logger->info("No-CD applied.");
    }

    if (!config->pauseWhenUnfocused.enabled) {
        applyNoPauseWhenUnfocused();
        logger->info("No pause when unfocused applied.");
    }
    
    if (config->meleeStuckFix.enabled) {
        applyMeleeStuckFix();
        logger->info("Melee Stuck fix applied.");
    }
    
    // Hooks
    /*applyUpdateGuiHook();
    logger->info("Added Hook when updating GUI.");
    *
    applyReadSideDataHooks();
    logger->info("Added Hook on reading SideData.tdf.");
    */
    applyLoadingScreenHooks();
    logger->info("Added Loading Screen Extension.");
    // ProcessCodesExtension

    // Pick map positions
    // autodiplomacy
    // Know pause state in loading screen
    // Double click => select units of the same type on the screen
    // Track unit in watching mode
    // Option to choose random race
    // Walls have hp 
    // Not able to ctrl d while in combat
    // How to draw on screen images etc
    // Units able to run
    // See what watcher says
    // Archers lob weapons
    // AutoGates in game for real
    // MakeAurasOnOffAble
    // Humor Interactions
    // ReclaimFeaturesGiveMana();
    // Investigate why units go closer than they need to attack (can use kirenna wave to test)
    // Find out how get unknown unit value works
    // make discord bot show minimaps
    // unit hp = 0 consider dead
    // ResolutionFix();
    // MakePlayAnOpponentSearchForGamesSomewhereElse()
    // Why watching in multiplayer causes so much lag
    
    logger->info("Endded applying changes. Enjoy!");
}
