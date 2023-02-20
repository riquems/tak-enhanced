#pragma once
#include <vector>
#include <string>

namespace TAKCore
{
    namespace Commands
    {
        constexpr const char* DoNothing = "DoNothing";
        constexpr const char* PasteUnitFromClipboard = "PasteUnitFromClipboard";
        constexpr const char* CutUnitToClipboard = "CutUnitToClipboard";
        constexpr const char* CopyUnitToClipboard = "CopyUnitToClipboard";
        constexpr const char* DebugResetSearchProfile = "DebugResetSearchProfile";
        constexpr const char* DebugDestroyUnit = "DebugDestroyUnit";
        constexpr const char* DebugCycleMode = "DebugCycleMode";
        constexpr const char* DebugToggleInfo = "DebugToggleInfo";
        constexpr const char* DebugToggleDebug = "DebugToggleDebug";
        constexpr const char* DebugBuilderProbe = "DebugBuilderProbe";
        constexpr const char* DebugUnitProbeDebug = "DebugUnitProbeDebug";
        constexpr const char* ToggleMovie = "ToggleMovie";
        constexpr const char* FacingQueue = "FacingQueue";
        constexpr const char* FullScreenRadar = "FullScreenRadar";
        constexpr const char* DecreaseSpeed = "DecreaseSpeed";
        constexpr const char* IncreaseSpeed = "IncreaseSpeed";
        constexpr const char* ClearChat = "ClearChat";
        constexpr const char* NetScorecard = "NetScorecard";
        constexpr const char* LoadGame = "LoadGame";
        constexpr const char* SaveGame = "SaveGame";
        constexpr const char* DiplomacyMenu = "DiplomacyMenu";
        constexpr const char* F2Menu = "F2Menu";
        constexpr const char* UnitInfo = "UnitInfo";
        constexpr const char* ToggleDamageBars = "ToggleDamageBars";
        constexpr const char* MoveToNextUnit = "MoveToNextUnit";
        constexpr const char* MoveToLastReport = "MoveToLastReport";
        constexpr const char* MapBookmarkRetrieve = "MapBookmarkRetrieve";
        constexpr const char* MapBookmarkStore = "MapBookmarkStore";
        constexpr const char* TrackUnitReverse = "TrackUnitReverse";
        constexpr const char* TrackUnit = "TrackUnit";
        constexpr const char* SelectUnitsOnScreenSelectedType = "SelectUnitsOnScreenSelectedType";
        constexpr const char* SelectUnitsOnScreenAdd = "SelectUnitsOnScreenAdd";
        constexpr const char* SelectUnitsOnScreen = "SelectUnitsOnScreen";
        constexpr const char* SelectAllUnitsSelectedType = "SelectAllUnitsSelectedType";
        constexpr const char* SelectAllUnits = "SelectAllUnits";
        constexpr const char* SelectUnitsAdd = "SelectUnitsAdd";
        constexpr const char* SelectUnits = "SelectUnits";
        constexpr const char* RetrieveSquadAdd = "RetrieveSquadAdd";
        constexpr const char* RetrieveSquadCreateSquad = "RetrieveSquadCreateSquad";
        constexpr const char* TogglePause = "TogglePause";
        constexpr const char* UnitCommand = "UnitCommand";
        constexpr const char* SelectSquad = "SelectSquad";

        extern std::vector<std::string> commands;

        extern std::vector<std::string> targetCommands;
    }
}

