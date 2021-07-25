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

extern "C" __declspec(dllexport) const char* TAK_Enhanced_Label = "TA:K Enhanced v0.3.0";

void applyTakEnhancedVersion()
{
    MemoryHandler::write(TAK_Enhanced_Label, 0xA4E23);

    logger.log("TA:K Enhanced Label applied.");
}

void applyChanges()
{
    applyTakEnhancedVersion();

    uint maxUnits = settings.MaxUnits;
    applyMaxUnitsPatch(maxUnits);

    uint pathFindingCycles = settings.PathFindingCycles;
    applyPathfindingFix(pathFindingCycles);

    if (settings.EnableHpOptions) {
        showEveryoneHealthBars();
        installShowHpHook();
    }

    applyModLoader();

    if (settings.NoCD) {
        applyNoCD();
    }

    if (!settings.PauseWhenUnfocused) {
        applyNoPauseWhenUnfocused();
    }
    
    if (settings.MeleeStuckFix) {
        applyMeleeStuckFix();
    }
    
    // Extensions
    applyUpdateGuiHook();
    applyReadSideDataHooks();
    applyLoadingScreenHooks();
    // ProcessCodesExtension

    // Option to choose random race
    // Walls have hp 
    // Not able to ctrl d while in combat
    // How to draw on screen images etc
    // Units able to run
    // See what watcher says
    // Archers lob weapons
    // AutoGates in game for real
    // MakeAurasOnOffAble
    // Pick map positions
    // Humor Interactions
    // autodiplomacy
    // ReclaimFeaturesGiveMana();
    // Investigate why units go closer than they need to attack (can use kirenna wave to test)
    // Find out how get unknown unit value works
    // make discord bot show minimaps
    // unit hp = 0 consider dead
    // ResolutionFix();
    // MakePlayAnOpponentSearchForGamesSomewhereElse()
    // Why watching in multiplayer causes so much lag
    
    logger.log("\nEndded applying changes. Enjoy!");
}
