#include "TAKEnhancedDll/Changes.hpp"
#include "TAKEnhancedDll/Changes/NoCD.hpp"
#include "TAKEnhancedDll/Changes/NoPauseWhenUnfocused.hpp"
#include "TAKEnhancedDll/Changes/PathFindingChanger.hpp"
#include "TAKEnhancedDll/Changes/MeleeStuckFix.hpp"
#include "TAKEnhancedDll/Changes/MaxUnits.hpp"
#include "TAKEnhancedDll/Changes/ModLoader.hpp"
#include "TAKEnhancedDll/Changes/ShowEveryoneHealthBars.hpp"
#include "TAKEnhancedDll/Changes/SightDistanceModifier.hpp"
#include "TAKEnhancedDll/Changes/WorkerTimeModifier.hpp"
#include "TAKEnhancedDll/Changes/ManaModifier.hpp"
#include "TAKEnhancedDll/Hooks/UpdateGuiHook.hpp"
#include "TAKEnhancedDll/Hooks/ReadSideDataHook.hpp"
#include "TAKEnhancedDll/Hooks/LoadingScreenHook.hpp"
#include "TAKEnhancedDll/Hooks/ShowHpHook.hpp"
#include "TAKEnhancedDll/Hooks/KeyboardInputHook.hpp"
#include "TAKCore/Config.h"
#include <TAKEnhancedDll/Changes/FriendlyFire.hpp>

__declspec(dllexport) const char* TAK_Enhanced_Label = "TA:K Enhanced v1.3.0";

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

    if (config->testMultiScript.enabled) {
        *TAK::Config::testMultiScript = true;
        *TAK::Config::noSideCulling = false;
    }
    
    if (config->skipLogo.enabled) {
        *TAK::Config::skipLogo = true;
    }
    if (config->showNetworkStats.enabled) {
        *TAK::Config::showNetworkStats = true;
    }
    if (config->disableCavedogVerification.enabled) {
        *TAK::Config::disableCavedogVerification = true;
    }
    if (config->pretendNoExpansion.enabled) {
        *TAK::Config::pretendNoExpansion = true;
    }
    if (config->fixCursor.enabled) {
        *TAK::Config::fixCursor = true;
    }
    if (config->disableUiPreload.enabled) {
        *TAK::Config::disableUiPreload = true;
    }
    if (config->noSideCulling.enabled) {
        *TAK::Config::noSideCulling = true;
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

    applyFriendlyFirePatch();

    applySightDistanceModifier();
    applyWorkerTimeModifier();
    applyManaModifier();

    applyUpdateGuiHook();
    logger->info("Added Hook when updating GUI.");

    // Hooks
    
    applyReadSideDataHooks();
    logger->info("Added Hook on reading SideData.tdf.");

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
