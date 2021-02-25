#pragma once

#include "HelperFeatures.h"
#include "NoCD.h"
#include "NoPauseWhenUnfocused.h"
#include "PathFindingChanger.h"
#include "MeleeStuckFix.h"
#include "MaxUnits.h"
#include "RandomRace.h"
#include "UpdateGuiExtension.h"
#include "ReadSideDataExtension.h"
#include "LoadingScreenExtensions.h"

extern "C" __declspec(dllexport) const char* TAK_Enhanced_Label = "TA:K Enhanced v1.0";

void ApplyTAKEnhancedVersion()
{
	MemoryHandling::write(TAK_Enhanced_Label, 0xA4E23);

	logger.log("TA:K Enhanced Label applied.");
}

void applyChanges()
{
	ApplyTAKEnhancedVersion();

	uint maxUnits = settings.MaxUnits;
	MaxUnitsPatch(maxUnits);

	uint pathFindingCycles = settings.PathfindingCycles;
	PathfindingFix(pathFindingCycles);

	if (settings.NoCD) {
		NoCD();
	}

	if (!settings.PauseWhenUnfocused) {
		NoPauseWhenUnfocused();
	}
	
	if (settings.MeleeStuckFix) {
		MeleeStuckFix();
	}
	
	/* Extensions */
	// ProcessCodesExtension
	UpdateGuiExtensionPatch();
	ReadSideDataExtensionPatch();
	LoadingScreenExtensionsPatch();

	// Not able to ctrl d while in combat
	// How to draw on screen images etc
	// Units able to run
	// See what watcher says
	// Archers lob weapons
	// AutoGates in game for real
	// MakeAurasOnOffAble
	// Pick map positions
	// Option to choose random race
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
	logger.end();
}